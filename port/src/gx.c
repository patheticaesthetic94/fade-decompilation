// GAPI (gx.dll), IMGDECMP DecompressImageIndirect and the GDI bitmap calls LoadImage uses.
#include "port.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_BMP
#define STBI_ONLY_GIF
#define STBI_ONLY_PNG
#define STBI_NO_STDIO
#include "stb_image.h"

uint16_t *port_fb;

int GXOpenDisplay(HWND hwnd, DWORD flags) { return 1; }
int GXCloseDisplay(void) { return 1; }
int GXOpenInput(void) { return 1; }
int GXCloseInput(void) { return 1; }
int GXSuspend(void) { return 1; }
int GXResume(void) { port_present(1); return 1; }
void *GXBeginDraw(void) { return port_fb; }
int GXEndDraw(void) { port_present(0); return 1; }

GXDisplayProperties *GXGetDisplayProperties(void)
{
    static GXDisplayProperties *p;
    if (!p) p = arena_calloc(sizeof *p);
    p->cxWidth = SCREEN_W; p->cyHeight = SCREEN_H;
    p->cbxPitch = 2; p->cbyPitch = SCREEN_W * 2;   // portrait, row-major
    p->cBPP = 16;
    p->ffFormat = 0x20 | 0x80;                      // kfDirect | kfDirect565
    return p;
}

// VK codes the port's input layer sends for the d-pad and the four hardware buttons
GXKeyList *GXGetDefaultKeys(int opt)
{
    static GXKeyList *k;
    if (!k) k = arena_calloc(sizeof *k);
    k->vkUp = 0x26; k->vkDown = 0x28; k->vkLeft = 0x25; k->vkRight = 0x27;
    k->vkA = 0xc1; k->vkB = 0xc2; k->vkC = 0xc3; k->vkStart = 0x86;
    return k;
}

// ---- images ---------------------------------------------------------------------------------------
// HBITMAP = arena block: BITMAP header (the 0x18 bytes GetObjectW returns) followed by a bottom-up,
// 4-byte-row-aligned 24-bit BGR DIB, which is what Bitmap_ConvertTo565 & co. expect.
typedef struct { int32_t type, w, h, stride; uint16_t planes, bpp; uint32_t bits; } Bitmap;

int DecompressImageIndirect()
{
    DecompressImageInfo *di = &g_imgDecompInfo;
    HANDLE hf = (HANDLE)(uintptr_t)(uint32_t)di->lParam;
    // whole file into an arena buffer (ReadFile takes 32-bit pointers)
    DWORD size = SetFilePointer(hf, 0, NULL, 2), got = 0;
    uint8_t *buf = arena_alloc(size + 1);
    static DWORD *pgot;
    if (!pgot) pgot = arena_alloc(sizeof *pgot);
    SetFilePointer(hf, 0, NULL, 0);
    ReadFile(hf, buf, size, pgot, NULL);
    size_t len = *pgot;
    int w, h, n;
    uint8_t *rgb = stbi_load_from_memory(buf, (int)len, &w, &h, &n, 3);
    arena_free(buf);
    if (!rgb) { port_log("DecompressImageIndirect: %s", stbi_failure_reason()); return 0x80004005; }
    int stride = (w * 3 + 3) & ~3;
    Bitmap *bm = arena_alloc(sizeof(Bitmap) + (size_t)stride * h);
    uint8_t *bits = (uint8_t *)(bm + 1);
    bm->type = 0; bm->w = w; bm->h = h; bm->stride = stride; bm->planes = 1; bm->bpp = 24;
    bm->bits = (uint32_t)(uintptr_t)bits;
    for (int y = 0; y < h; y++) {
        const uint8_t *s = rgb + (size_t)(h - 1 - y) * w * 3;
        uint8_t *d = bits + (size_t)y * stride;
        for (int x = 0; x < w; x++, s += 3, d += 3) { d[0] = s[2]; d[1] = s[1]; d[2] = s[0]; }
    }
    stbi_image_free(rgb);
    *(uint32_t *)(uintptr_t)(uint32_t)(uintptr_t)di->phBM = (uint32_t)(uintptr_t)bm;
    return 0;
}

int GetObjectW(HANDLE h, int n, LPVOID out)
{
    Bitmap *bm = (Bitmap *)(uintptr_t)(uint32_t)(uintptr_t)h;
    if (!bm || n < (int)sizeof(Bitmap)) return 0;
    memcpy(out, bm, sizeof(Bitmap));
    return sizeof(Bitmap);
}

BOOL DeleteObject(HGDIOBJ h)
{
    uint32_t v = (uint32_t)(uintptr_t)h;
    if (v > 0x10000) arena_free((void *)(uintptr_t)v);   // stock objects are small ints
    return 1;
}
