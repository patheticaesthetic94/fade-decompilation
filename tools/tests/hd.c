// Exercise the actual Android renderer without a window, using a tiny PNG fixture.
#include "../../port/src/hd.h"
#include <assert.h>
#include <stdio.h>
#undef main

// Standalone tests have no Java asset manager. Interpose file loading with stdio.
void *SDL_LoadFile(const char *file,size_t *size)
{
    FILE *fp=fopen(file,"rb");if(!fp)return NULL;
    fseek(fp,0,SEEK_END);long n=ftell(fp);rewind(fp);
    void *data=SDL_malloc(n+1);assert(fread(data,1,n,fp)==(size_t)n);
    ((char *)data)[n]=0;fclose(fp);if(size)*size=n;return data;
}

static uint32_t at(int x,int y) { return hd_frame()[y*SCREEN_W*4+x] & 0xffffff; }
int main(void)
{
    SDL_Init(0);
    arena_init();
    size_t n;uint8_t *exe=SDL_LoadFile("Fade.exe",&n);assert(exe);
    arena_load_image(exe,n);SDL_free(exe);
    g_colorKey=0;
    port_fb=arena_calloc(SCREEN_W*SCREEN_H*2);
    hd_init();assert(hd_enabled());
    Screen *s=arena_calloc(sizeof *s);Screen_Init(s,240,320);
    uint16_t *p=arena_alloc(8);
    p[0]=0;p[1]=0xf800;p[2]=0x07e0;p[3]=0x001f;
    hd_register(p,2,2,"fixture.bmp");
    // Use the recovered filename encoder: credits pass .ifj, scripts use CP1252.
    const char *names[]={"\\Program Files\\fade\\Menu\\Credits1.ifj",
                         "\\Program Files\\fade\\Menu\\Credits2.ifj",
                         "\\Program Files\\fade\\Zoom\\zoom r\xe9veil.jpg"};
    const char *keys[]={"menu/cvihmxw1.ifj","menu/cvihmxw2.ifj","zoom/zssq v1zimp.ifj"};
    CString *input=arena_calloc(sizeof *input),*encoded=arena_calloc(sizeof *encoded);
    char *name=arena_alloc(200);
    for(int i=0;i<3;i++) {
        strcpy(name,names[i]);CString_CtorA(input,name);
        MangleAssetPath(encoded,*input);
        char *rel=files_game_rel(encoded->str);
        assert(!strcmp(rel,keys[i]));
        hd_register(p,2,2,rel);
        SDL_free(rel);CString_Dtor(encoded);
    }
    arena_free(input);arena_free(encoded);arena_free(name);
    Screen_FillAll(s,0);
    Screen_FillLayer(s,0x001f,3);
    Screen_BlitToLayer(s,10,10,2,2,p,1);
    Screen_Present(s);
    assert(port_fb[10*240+10]==0x001f); // key is transparent in composition
    assert(port_fb[10*240+11]==0xf800);
    assert(at(40,40)==0x0000ff);
    assert(at(44,40)!=at(45,40)); // Native subpixel detail survived composition
    uint32_t detail=at(45,40);
    uint16_t *saved=arena_alloc(8);
    Screen_ReadLayer(s,10,10,2,2,saved,0);
    Screen_FillAll(s,0);
    Screen_BlitToLayer(s,20,20,2,2,saved,3);
    Screen_Present(s);
    assert(at(85,80)==detail); // Saved backgrounds retain native detail
    Screen_DrawDirectRows(s,30,30,2,1,1,(int)(uintptr_t)p);
    assert(port_fb[30*240+30]==0x07e0);
    assert(at(120,120)==0x00ff00);
    Screen_DrawDirectStride(s,40,40,2,2,1,p);
    assert(port_fb[41*240+40]==0x07e0); // Original source stride is retained
    Screen_DrawDirect(s,-1,0,2,2,p);
    assert(port_fb[0]==0xf800); // Negative destination clips source as well
    uint16_t *mask=arena_alloc(8);mask[0]=0;mask[1]=1;mask[2]=1;mask[3]=0;
    Screen_FillLayer(s,0x001f,3);
    Screen_BlitMaskedToLayer(s,10,10,2,2,(short *_P32)p,(short *_P32)mask,3);
    Screen_PresentLayer(s,3);
    assert(port_fb[10*240+10]==0x001f);
    assert(port_fb[10*240+11]==0xf800);
    assert(port_fb[11*240+10]==0x07e0);
    assert(port_fb[11*240+11]==0x001f);
    uint16_t *patch=arena_alloc(8*8*2);
    for(int i=0;i<64;i++)patch[i]=0xf800;
    hd_register(patch,8,8,"sprites/patch.ifj");
    Screen_FillAll(s,0);Screen_FillLayer(s,0x001f,3);
    Screen_BlitToLayer(s,100,100,8,8,patch,3);
    Screen_PresentLayer(s,3);
    assert(port_fb[100*240+100]==0xf800); // Preserve original logical writes
    assert(at(400,416)==0x0000ff); // Rectangle boundary matches existing room
    assert(at(401,416)!=0x0000ff && at(401,416)!=0xff0000);
    assert(at(407,416)!=0xff0000);
    assert(at(408,416)==0xff0000); // Centre retains full native artwork
    assert(at(431,416)==0x0000ff);
    uint32_t seam=at(404,416);
    uint16_t *patch_saved=arena_alloc(8*8*2);
    Screen_ReadLayer(s,100,100,8,8,patch_saved,3);
    Screen_BlitToLayer(s,110,100,8,8,patch_saved,3);
    Screen_PresentLayer(s,3);
    assert(at(444,416)==seam); // Saved composite must not be feathered twice
    Screen_FillLayer(s,0x001f,3);Screen_PresentLayer(s,3);
    Screen_DrawDirect(s,-1,100,8,8,patch);
    assert(at(0,416)==seam); // Feather uses source coordinates when clipped
    hd_register(patch,8,8,"sprites/cutout.ifb");
    Screen_BlitToLayer(s,100,100,8,8,patch,3);Screen_PresentLayer(s,3);
    assert(at(400,416)==0xff0000); // BMP cutouts retain their original coverage
    arena_free(patch_saved);arena_free(patch);
    arena_free(saved);arena_free(mask);arena_free(p);
    p=arena_calloc(8);hd_buffer(p,2,2);
    Screen_DrawDirect(s,10,10,2,2,p);
    assert(at(45,40)==0); // Freed/reused pointers cannot retain stale artwork
    FontGlyphs *font=arena_calloc(sizeof *font);
    Glyph *gl=&font->glyphs['A'];gl->w=2;gl->h=2;
    gl->pixels=arena_calloc(8);gl->loaded=1;gl->keyed=1;gl->screen=s;
    ((uint16_t *)(uintptr_t)gl->pixels)[0]=0xffff; // Logical ink has a different footprint
    hd_font(font,"fonts/font popups blanche.bmp",1);
    Screen_FillAll(s,0);Screen_FillLayer(s,0x001f,3);
    Glyph_BlitToLayer(gl,1,60,60);Screen_Present(s);
    assert(port_fb[60*240+60]==0xffff);
    assert(at(240,240)==0x0000ff); // Logical font ink must not be drawn a second time
    assert(at(241,241)!=0x0000ff); // Antialias coverage survives a keyed layer copy
    assert(at(242,241)==0x0000ff);
    Screen_FillLayer(s,0,0);Glyph_BlitToLayer(gl,0,60,60);
    Screen_PresentRect(s,60,60,2,2,0);
    assert(at(241,241)==0x808080); // Fractional popup ink is flattened, not opaque white
    assert(at(240,240)==0);
    hd_effect(s->layer[0],s->layer[0],0);
    s->layer[0][60*240+60]=0xf7de;
    hd_sync(s->layer[0]);hd_effect(NULL,NULL,0);
    Screen_PresentRect(s,60,60,2,2,0);
    assert((at(241,241)&255)<128); // In-place shadows preserve coverage and darken it
    puts("HD renderer: composition, native detail, sprite seams, saved backgrounds, rows, stride, clipping, masks, pointer reuse and antialiased text passed");
    return 0;
}
