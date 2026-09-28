// Entry point: maps the arena and the original data image, then runs the game's WinMain on a thread
// whose stack lives in the low arena (game code keeps addresses of locals in 32-bit slots).
// Presents the GAPI framebuffer with SDL and turns SDL input into WM_* messages.
#include "port.h"
#include "text.h"
#include <pthread.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#ifdef __ANDROID__
#include <sys/system_properties.h>
#endif

#define GAME_STACK (16u << 20)

static SDL_Window *win;
static SDL_Renderer *ren;
static SDL_Texture *tex;
static Uint32 last_present;
static int fb_dirty;
int port_trace;

void port_fatal(const char *fmt, ...)
{
    char buf[512];
    va_list ap;
    va_start(ap, fmt);
    SDL_vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "fatal: %s", buf);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fade", buf, win);
    exit(1);
}

// Present at most every 15 ms: the game calls GXEndDraw for every small blit.
void port_present(int force)
{
    if (!ren) return;
    fb_dirty = 1;
    Uint32 now = SDL_GetTicks();
    if (!force && now - last_present < 15) return;
    last_present = now;
    fb_dirty = 0;
    if (hd_enabled()) SDL_UpdateTexture(tex, NULL, hd_frame(), SCREEN_W * HD_SCALE * 4);
    else SDL_UpdateTexture(tex, NULL, port_fb, SCREEN_W * 2);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
}

static uint32_t vk_of(SDL_Keycode k)
{
    switch (k) {
    case SDLK_UP: return 0x26;
    case SDLK_DOWN: return 0x28;
    case SDLK_LEFT: return 0x25;
    case SDLK_RIGHT: return 0x27;
    case SDLK_z: case SDLK_RETURN: return 0xc1;   // hardware button A
    case SDLK_x: return 0xc2;
    case SDLK_c: return 0xc3;
    case SDLK_AC_BACK: case SDLK_ESCAPE: return 0x86;
    default: return 0;
    }
}

static uint32_t lparam_xy(int x, int y)
{
    x = SDL_clamp(x, 0, SCREEN_W - 1);
    y = SDL_clamp(y, 0, SCREEN_H - 1);
    return (uint32_t)x | (uint32_t)y << 16;
}

void port_delay(uint32_t ms)
{
#ifdef __EMSCRIPTEN__
    emscripten_sleep(ms);
#else
    SDL_Delay(ms);
#endif
}

void port_pump(int wait_ms)
{
#ifdef __EMSCRIPTEN__
    // Yield even for PeekMessage polling so animations and browser input run.
    emscripten_sleep(wait_ms > 0 ? wait_ms : 1);
    wait_ms = 0;
#endif
    SDL_Event e;
    int got = wait_ms > 0 ? SDL_WaitEventTimeout(&e, wait_ms) : SDL_PollEvent(&e);
    while (got) {
        switch (e.type) {
        case SDL_QUIT: msg_post(2 /* WM_DESTROY */, 0, 0); break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT) msg_post(0x201, 1, lparam_xy(e.button.x, e.button.y));
            break;
        case SDL_MOUSEBUTTONUP:
            if (e.button.button == SDL_BUTTON_LEFT) msg_post(0x202, 0, lparam_xy(e.button.x, e.button.y));
            break;
        case SDL_MOUSEMOTION:
            if (e.motion.state & SDL_BUTTON_LMASK) msg_post(0x200, 1, lparam_xy(e.motion.x, e.motion.y));
            break;
        case SDL_KEYDOWN: { uint32_t vk = vk_of(e.key.keysym.sym); if (vk) msg_post(0x100, vk, 1); break; }
        case SDL_KEYUP: { uint32_t vk = vk_of(e.key.keysym.sym); if (vk) msg_post(0x101, vk, 0xc0000001u); break; }
        case SDL_APP_WILLENTERBACKGROUND: msg_post(8 /* WM_KILLFOCUS */, 0, 0); break;
        case SDL_APP_DIDENTERFOREGROUND: msg_post(7 /* WM_SETFOCUS */, 0, 0); port_present(1); break;
        case SDL_WINDOWEVENT:
            if (e.window.event == SDL_WINDOWEVENT_EXPOSED || e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) port_present(1);
            break;
        }
        got = SDL_PollEvent(&e);
    }
    if (fb_dirty) port_present(0);
}

void (*game_func_at(uint32_t addr))(void)
{
    int lo = 0, hi = game_nfuncs - 1;
    while (lo <= hi) {
        int m = (lo + hi) / 2;
        if (game_funcs[m].addr == addr) return game_funcs[m].fn;
        if (game_funcs[m].addr < addr) lo = m + 1; else hi = m - 1;
    }
    return NULL;
}

// C++ dynamic initialisers, as the CE CRT runs them (_initterm over __xc_a..__xc_z) before WinMain.
// Game entries are stubs `push {lr}; bl ctor; pop {lr}; b atexit_reg`: call ctor natively. Entries in the
// statically linked MFC/CRT are skipped (that code is native in the port). Destructors never run.
#define XC_TABLE 0x43374u
#define GAME_CODE_END 0x29d40u
static void static_init(void)
{
    for (uint32_t *p = (uint32_t *)(uintptr_t)XC_TABLE; *p; p++) {
        if (*p >= GAME_CODE_END) continue;
        uint32_t bl = *(uint32_t *)(uintptr_t)(*p + 4);
        if ((bl & 0x0f000000) != 0x0b000000) port_fatal("static init %#x: not a bl stub", *p);
        uint32_t target = *p + 4 + 8 + ((uint32_t)((int32_t)(bl << 8) >> 6));
        void (*fn)(void) = game_func_at(target);
        if (!fn) port_fatal("static init %#x: no function at %#x", *p, target);
        if (port_trace) port_log("static init %#x -> %#x", *p, target);
        fn();
    }
}

static void *game_thread(void *arg)
{
#ifdef __ANDROID__
    SDL_AndroidGetJNIEnv();   // attaches this thread to the JVM
#endif
    win = SDL_CreateWindow("Fade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W * 3, SCREEN_H * 3,
                           SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
#ifdef __ANDROID__
                           | SDL_WINDOW_FULLSCREEN
#endif
    );
    if (!win) port_fatal("SDL_CreateWindow: %s", SDL_GetError());
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) ren = SDL_CreateRenderer(win, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(ren, SCREEN_W, SCREEN_H);   // letterbox + maps touch/mouse to 240x320
    int scale = hd_enabled() ? HD_SCALE : 1;
    tex = SDL_CreateTexture(ren, hd_enabled() ? SDL_PIXELFORMAT_ARGB8888 : SDL_PIXELFORMAT_RGB565,
                            SDL_TEXTUREACCESS_STREAMING, SCREEN_W * scale, SCREEN_H * scale);
    if (!tex) port_fatal("SDL_CreateTexture: %s", SDL_GetError());
    port_present(1);

    static_init();
    int rc = (int)WinMain((HINSTANCE)(uintptr_t)0x10000, 0, 0, 1 /* SW_SHOWNORMAL */);
    port_log("WinMain returned %d", rc);
    return NULL;
}

int main(int argc, char **argv)
{
    port_trace = SDL_getenv("FADE_TRACE") != NULL;
#ifdef __ANDROID__
    char prop[PROP_VALUE_MAX] = "";
    __system_property_get("debug.fade.trace", prop);
    port_trace |= prop[0] == '1';
#endif
    SDL_SetHint(SDL_HINT_ORIENTATIONS, "Portrait");
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "1");
    SDL_SetHint(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, "1");
#ifdef __EMSCRIPTEN__
    // Yield at the port's explicit waits. SDL's implicit yields in rendering
    // and event polling otherwise suspend in the middle of each tiny blit.
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_ASYNCIFY, "0");
#endif
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) port_fatal("SDL_Init: %s", SDL_GetError());

    arena_init();
    size_t len;
    uint8_t *exe = SDL_LoadFile("fade/Fade.exe", &len);
    if (!exe) port_fatal("missing game data (fade/Fade.exe): %s", SDL_GetError());
    arena_load_image(exe, len);
    SDL_free(exe);
    files_init();
    port_fb = arena_calloc(SCREEN_W * SCREEN_H * 2);
    hd_init();
    text_init();

#ifdef __EMSCRIPTEN__
    // Asyncify preserves the recovered WinMain call stack across browser turns.
    // wasm32's normal stack already has 32-bit addresses; no pthread is needed.
    game_thread(NULL);
#else
    pthread_attr_t at;
    int err = pthread_attr_init(&at);
    if (err) port_fatal("cannot initialize game thread: %s", strerror(err));
    err = pthread_attr_setstack(&at, arena_stack(GAME_STACK), GAME_STACK);
    if (err) port_fatal("cannot set game thread stack: %s", strerror(err));
    pthread_t th;
    err = pthread_create(&th, &at, game_thread, NULL);
    if (err) port_fatal("cannot start game thread: %s", strerror(err));
    pthread_attr_destroy(&at);
    pthread_join(th, NULL);
#endif
    SDL_Quit();
    return 0;
}
