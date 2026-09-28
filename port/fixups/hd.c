// Durable rendering replacements. The logical RGB565 buffers still receive every
// write for scripts, masks and saves; native 4x stores follow the same operations.
#include "../src/text.h"

// 0001821c LoadImage
// HD_WRAP LoadImage
int LoadImage(CString path,int *_P32 h,int *_P32 w,ushort *_P32 *_P32 pixels,byte keyed)
{
    CString copy, encoded;
    CString_CopyCtor(&copy,&path);
    MangleAssetPath(&encoded,copy); // Consumes copy, as in LoadImageFile.
    char *rel=files_game_rel(encoded.str);
    CString_Dtor(&encoded);
    int ok=legacy_LoadImage(path,h,w,pixels,keyed);
    if(ok)hd_register(*pixels,*w,*h,rel);
    SDL_free(rel);return ok;
}

// 0001d958 Font_Load
// HD_WRAP Font_Load
void Font_Load(FontGlyphs *_P32 font,CString path,Screen *_P32 screen,byte keyed)
{
    char *rel=files_game_rel(path.str);
    if(text_enabled()) {text_load(font,rel);CString_Dtor(&path);SDL_free(rel);return;}
    legacy_Font_Load(font,path,screen,keyed);
    hd_font(font,rel,keyed);SDL_free(rel);
}

// 000114cc Screen_Init
// HD_WRAP Screen_Init
void Screen_Init(Screen *_P32 s,int w,int h)
{
    legacy_Screen_Init(s,w,h);
    for(int i=0;i<5;i++) {
        memset(s->layer[i],0,(size_t)w*h*2);
        hd_buffer(s->layer[i],w,h);
    }
}

// 00012174 Screen_FillLayer
void Screen_FillLayer(Screen *_P32 s,ushort v,char layer)
{
    for(int i=0;i<s->size;i++)s->layer[(unsigned char)layer][i]=v;
    hd_fill(s->layer[(unsigned char)layer],v);
}

// 000121f0 Screen_BlitToLayer
void Screen_BlitToLayer(Screen *_P32 s,int x,int y,int w,int h,ushort *_P32 p,char l)
{hd_blit(s->layer[(unsigned char)l],x,y,w,h,p,w,0,0,1,0,NULL);}

// 00012274 Screen_BlitToLayerStride
void Screen_BlitToLayerStride(Screen *_P32 s,int x,int y,uint w,int h,uint limit,ushort *_P32 p,char l)
{hd_blit(s->layer[(unsigned char)l],x,y,SDL_min(w,limit),h,p,w,0,0,1,0,NULL);}

// 00012318 Screen_BlitDownscaled
void Screen_BlitDownscaled(Screen *_P32 s,int x,int y,undefined4 w,undefined4 h,ushort *_P32 p,char l,char step)
{
    if(step>0)hd_blit(s->layer[(unsigned char)l],x,y,w/step,h/step,p,w,0,0,step,0,NULL);
}

// 00012c64 Screen_BlitRowsToLayer
void Screen_BlitRowsToLayer(Screen *_P32 s,int x,int y,int w,int h,int row,int p,char l)
{hd_blit(s->layer[(unsigned char)l],x,y,w,h,(uint16_t *)(uintptr_t)(uint32_t)p,w,0,row,1,0,NULL);}

// 00012cf8 Screen_BlitMaskedToLayer
void Screen_BlitMaskedToLayer(Screen *_P32 s,int x,int y,int w,int h,short *_P32 p,short *_P32 mask,char l)
{hd_blit(s->layer[(unsigned char)l],x,y,w,h,(uint16_t *)p,w,0,0,1,0,(uint16_t *)mask);}

// 00013048 Screen_BlitKeyedToLayer
void Screen_BlitKeyedToLayer(Screen *_P32 s,int x,int y,int w,int h,short *_P32 p,char l)
{hd_blit(s->layer[(unsigned char)l],x,y,w,h,(uint16_t *)p,w,0,0,1,1,NULL);}

// 00012da4 Screen_ReadLayer
// HD_WRAP Screen_ReadLayer
void Screen_ReadLayer(Screen *_P32 s,int x,int y,int w,int h,ushort *_P32 p,char l)
{
    if(!hd_enabled()) {legacy_Screen_ReadLayer(s,x,y,w,h,p,l);return;}
    // Saved backgrounds must retain native artwork and replacement text.
    hd_buffer(p,w,h);
    hd_blit(p,0,0,w,h,s->layer[(unsigned char)l],s->w,x,y,1,0,NULL);
}

// 000115fc Screen_CopyKeyed
void Screen_CopyKeyed(Screen *_P32 s,short *_P32 p,int dest)
{hd_blit((uint16_t *)(uintptr_t)(uint32_t)dest,0,0,s->w,s->h,(uint16_t *)p,s->w,0,0,1,1,NULL);}

// 00011e40 Screen_Compose
void Screen_Compose(Screen *_P32 s)
{
    hd_blit(s->layer[0],0,0,s->w,s->h,s->layer[3],s->w,0,0,1,0,NULL);
    Screen_CopyKeyed(s,(short *_P32)s->layer[2],(int)s->layer[0]);
    Screen_CopyKeyed(s,(short *_P32)s->layer[1],(int)s->layer[0]);
}

// 00011e80 Screen_ComposeRows
void Screen_ComposeRows(Screen *_P32 s,int rows)
{
    hd_blit(s->layer[0],0,0,s->w,s->h,s->layer[3],s->w,0,0,1,0,NULL);
    hd_blit(s->layer[0],0,0,s->w,SDL_clamp(rows,0,s->h),s->layer[1],s->w,0,0,1,1,NULL);
}

// 00011eb8 Screen_Present
void Screen_Present(Screen *_P32 s)
{
    Screen_Compose(s);
    hd_blit(port_fb,0,0,s->w,s->h,s->layer[0],s->w,0,0,1,0,NULL);
    GXEndDraw();
}

// 00011f5c Screen_PresentRows
void Screen_PresentRows(Screen *_P32 s,int rows)
{
    Screen_ComposeRows(s,rows);
    hd_blit(port_fb,0,0,s->w,SDL_clamp(rows,0,s->h),s->layer[0],s->w,0,0,1,0,NULL);
    GXEndDraw();
}

// 00011ff8 Screen_PresentLayer
void Screen_PresentLayer(Screen *_P32 s,char l)
{
    hd_blit(port_fb,0,0,s->w,s->h,s->layer[(unsigned char)l],s->w,0,0,1,0,NULL);
    GXEndDraw();
}

// 000120a0 Screen_PresentRect
void Screen_PresentRect(Screen *_P32 s,int x,int y,int w,int h,char l)
{
    hd_blit(port_fb,x,y,w,h,s->layer[(unsigned char)l],s->w,x,y,1,0,NULL);
    GXEndDraw();
}

// 00012a24 Screen_DrawDirect
void Screen_DrawDirect(Screen *_P32 s,int x,int y,int w,int h,ushort *_P32 p)
{hd_blit(port_fb,x,y,w,h,p,w,0,0,1,0,NULL);GXEndDraw();}

// 00012ad4 Screen_DrawDirectStride
void Screen_DrawDirectStride(Screen *_P32 s,int x,int y,uint w,int h,uint limit,ushort *_P32 p)
{hd_blit(port_fb,x,y,SDL_min(w,limit),h,p,w,0,0,1,0,NULL);GXEndDraw();}

// 00012ba4 Screen_DrawDirectRows
void Screen_DrawDirectRows(Screen *_P32 s,int x,int y,int w,int h,int row,int p)
{hd_blit(port_fb,x,y,w,h,(uint16_t *)(uintptr_t)(uint32_t)p,w,0,row,1,0,NULL);GXEndDraw();}

// 000133b0 Screen_DrawKeyedDirect
void Screen_DrawKeyedDirect(Screen *_P32 s,uint x,uint y,int w,int h,short *_P32 p)
{hd_blit(port_fb,x,y,w,h,(uint16_t *)p,w,0,0,1,1,NULL);GXEndDraw();}

// 00015bc0 Screen_DrawShadow
// HD_WRAP Screen_DrawShadow
void Screen_DrawShadow(Screen *_P32 s,int x,int y,int w,int h,char source,char dest)
{
    hd_effect(s->layer[(unsigned char)source],s->layer[(unsigned char)dest],0);
    legacy_Screen_DrawShadow(s,x,y,w,h,source,dest);
    hd_sync(s->layer[(unsigned char)dest]);hd_effect(NULL,NULL,0);
}

// 00015090 Screen_FadeFromBlack
// HD_WRAP Screen_FadeFromBlack
void Screen_FadeFromBlack(Screen *_P32 s,uint x,uint y,int w,int h,char source,char dest)
{
    hd_effect(s->layer[(unsigned char)source],s->layer[(unsigned char)dest],1);
    legacy_Screen_FadeFromBlack(s,x,y,w,h,source,dest);
    hd_sync(s->layer[(unsigned char)dest]);hd_effect(NULL,NULL,0);
}

// 000157d4 Screen_FadeFromWhite
// HD_WRAP Screen_FadeFromWhite
void Screen_FadeFromWhite(Screen *_P32 s,uint x,uint y,int w,int h,char source,char dest)
{
    hd_effect(s->layer[(unsigned char)source],s->layer[(unsigned char)dest],2);
    legacy_Screen_FadeFromWhite(s,x,y,w,h,source,dest);
    hd_sync(s->layer[(unsigned char)dest]);hd_effect(NULL,NULL,0);
}
