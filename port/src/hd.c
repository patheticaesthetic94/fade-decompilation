// Native 4x backing stores; legacy pointers and all game coordinates remain unchanged.
// No SDL renderer objects or native pointers are stored in recovered game structures.
#include "hd.h"
#include "stb_image.h"
#include <stdlib.h>

typedef struct HDImage {
    uint16_t *low, *seen;
    uint32_t *rgba;
    int w, h, font, sprite_patch;
    struct HDImage *next;
} HDImage;
static HDImage *images;
static int enabled;
static char *index_data;
static struct { char *name, *path; } *index_hd;
static int count;
static HDImage *effect_src, *effect_dst;
static int effect_mode;

static uint32_t color(uint16_t v)
{
    int r = (v >> 11) * 255 / 31, g = ((v >> 5) & 63) * 255 / 63, b = (v & 31) * 255 / 31;
    return (v == (uint16_t)g_colorKey ? 0 : 0xff000000u) | r << 16 | g << 8 | b;
}

static HDImage *find(const void *p, size_t *offset)
{
    uintptr_t at = (uintptr_t)p;
    for (HDImage *im = images; im; im = im->next) {
        uintptr_t start = (uintptr_t)im->low;
        if (at >= start && at < start + (size_t)im->w*im->h*2) {
            if (offset) *offset = (at-start)/2;
            return im;
        }
    }
    return NULL;
}

int hd_enabled(void) { return enabled; }

void hd_init(void)
{
    size_t n;
    index_data = SDL_LoadFile("hd/files.txt", &n);
    if (!index_data) {
        void *runtime=SDL_LoadFile("fonts/runtime.txt", &n);
        if (!runtime) return;
        SDL_free(runtime);enabled=1;
        hd_buffer(port_fb, SCREEN_W, SCREEN_H);
        return;
    }
    enabled = 1;
    for (size_t i=0; i<n; i++) if (index_data[i]=='\n') count++;
    index_hd = SDL_calloc(count, sizeof *index_hd);
    int i=0;
    for (char *line = strtok(index_data, "\n"); line; line = strtok(NULL, "\n")) {
        char *tab = strchr(line, '\t');
        if (!tab) port_fatal("invalid HD resource index");
        *tab = 0;
        index_hd[i].name = line; index_hd[i++].path = tab+1;
    }
    count=i;
    hd_buffer(port_fb, SCREEN_W, SCREEN_H);
    port_log("HD: 960x1280, %d replacement images, Comic Neue Bold / Arimo", count);
}

static uint32_t *load_png(const char *path, int expected_w, int expected_h)
{
    size_t n;
    uint8_t *data = SDL_LoadFile(path, &n);
    if (!data) port_fatal("HD asset missing: %s", path);
    int w,h,channels;
    uint8_t *rgb = stbi_load_from_memory(data, (int)n, &w, &h, &channels, 4);
    SDL_free(data);
    if (!rgb || w != expected_w || h != expected_h)
        port_fatal("HD asset invalid dimensions/PNG: %s (%dx%d expected)", path, expected_w, expected_h);
    uint32_t *rgba = SDL_malloc((size_t)w*h*4);
    if (!rgba) port_fatal("HD: out of memory loading %s", path);
    for (size_t i=0; i<(size_t)w*h; i++)
        rgba[i] = (uint32_t)rgb[i*4+3]<<24 | rgb[i*4]<<16 | rgb[i*4+1]<<8 | rgb[i*4+2];
    stbi_image_free(rgb);
    return rgba;
}

void hd_buffer(uint16_t *low, int w, int h)
{
    if (!enabled || find(low, NULL)) return;
    if (w <= 0 || h <= 0 || w > 4096 || h > 4096) port_fatal("HD: invalid logical buffer %dx%d", w,h);
    HDImage *im = SDL_calloc(1, sizeof *im);
    im->low=low; im->w=w; im->h=h;
    im->seen=SDL_malloc((size_t)w*h*2);
    im->rgba=SDL_calloc((size_t)w*h*HD_SCALE*HD_SCALE,4);
    if (!im->seen || !im->rgba) port_fatal("HD: out of memory allocating %dx%d",w,h);
    memcpy(im->seen, low, (size_t)w*h*2);
    for (int y=0;y<h*4;y++) for (int x=0;x<w*4;x++)
        im->rgba[y*w*4+x]=color(low[(y/4)*w+x/4]) | (low==port_fb ? 0xff000000u : 0);
    im->next=images;images=im;
}

void hd_forget(void *p)
{
    if (!enabled) return;
    HDImage **link=&images;
    while (*link) {
        HDImage *im=*link;
        if (im->low==p) {
            if (effect_src==im) effect_src=NULL;
            if (effect_dst==im) effect_dst=NULL;
            *link=im->next;
            SDL_free(im->rgba);SDL_free(im->seen);SDL_free(im);
            return;
        }
        link=&im->next;
    }
}

void hd_register(uint16_t *low, int w, int h, const char *path)
{
    if (!enabled || !strncmp(path,"fonts/",6)) return;
    int lo=0,hi=count-1;
    const char *rel=NULL;
    while (lo<=hi) {
        int m=(lo+hi)/2,c=strcmp(path,index_hd[m].name);
        if (!c) { rel=index_hd[m].path;break; }
        if (c<0) hi=m-1;else lo=m+1;
    }
    if (!rel) {
        if(!index_data)return; // Runtime fonts with original-resolution artwork.
        port_fatal("HD resource not indexed: %s",path);
    }
    hd_buffer(low,w,h);
    HDImage *im=find(low,NULL);
    // JPEG sprites are rectangular room patches. Independently upscaled edges
    // can disagree with the room; BMP cutouts retain their exact colour key.
    const char *ext=strrchr(path,'.');
    im->sprite_patch=!strncmp(path,"sprites/",8) && ext && !strcmp(ext,".ifj");
    SDL_free(im->rgba);
    char full[600];SDL_snprintf(full,sizeof full,"hd/%s",rel);
    im->rgba=load_png(full,w*4,h*4);
    for (int y=0;y<h*4;y++) for (int x=0;x<w*4;x++) {
        uint32_t *p=&im->rgba[y*w*4+x];
        int gamma=(signed char)g_gamma;
        int r=SDL_clamp((int)(*p>>16&255)+gamma,0,255);
        int g=SDL_clamp((int)(*p>>8&255)+gamma,0,255);
        int b=SDL_clamp((int)(*p&255)+gamma,0,255);
        *p=(low[(y/4)*w+x/4]==g_colorKey ? 0 : 0xff000000u) | r<<16 | g<<8 | b;
    }
    if (port_trace) port_log("HD load: %s %dx%d",path,w*4,h*4);
}

void hd_font(FontGlyphs *font, const char *path, int keyed)
{
    if (!enabled) return;
    const char *name=strrchr(path,'/');name=name ? name+1 : path;
    // Index paths are lowercase, while staged atlas filenames preserve source casing.
    char upper[200];SDL_strlcpy(upper,name,sizeof upper);
    for (char *p=upper;*p;p++) *p=SDL_toupper(*p);
    char *dot=strrchr(upper,'.');if(dot) strcpy(dot,".bmp");
    char full[300];SDL_snprintf(full,sizeof full,"hd/fonts/%s.png",upper);
    uint32_t *atlas=load_png(full,1024,1024);
    for (int c=0;c<255;c++) {
        Glyph *gl=&font->glyphs[c];
        if (!gl->loaded || !gl->w || !gl->h || !gl->pixels || find(gl->pixels,NULL)) continue;
        hd_buffer(gl->pixels,gl->w,gl->h);
        HDImage *im=find(gl->pixels,NULL);im->font=1;
        for(int y=0;y<gl->h*4;y++) for(int x=0;x<gl->w*4;x++) {
            uint32_t v=atlas[(c/16*64+y)*1024+c%16*64+x];
            im->rgba[y*im->w*4+x]=v;
        }
    }
    SDL_free(atlas);
    port_log("HD font: %s",upper);
}

void hd_fill(uint16_t *low, uint16_t v)
{
    HDImage *im=find(low,NULL);if (!im) return;
    for (int i=0;i<im->w*im->h;i++) im->seen[i]=v;
    for (size_t i=0;i<(size_t)im->w*im->h*16;i++) im->rgba[i]=color(v);
}

void hd_effect(uint16_t *src, uint16_t *dst, int mode)
{
    effect_src=find(src,NULL);effect_dst=find(dst,NULL);effect_mode=mode;
}

// Legacy effects write logical layer pixels directly. Apply their channel change
// to the existing native detail (or source layer for two-layer fades/shadows).
void hd_sync(uint16_t *low)
{
    HDImage *im=find(low,NULL);if (!im) return;
    for (int y=0;y<im->h;y++) for(int x=0;x<im->w;x++) {
        int i=y*im->w+x;
        uint16_t now=low[i],old=im->seen[i];
        if(now==old) continue;
        HDImage *base=im;
        if(im==effect_dst && effect_src) {
            base=effect_src;
            if(base!=im)old=base->low[i];
        }
        uint32_t a=color(old),b=color(now);
        for(int yy=0;yy<4;yy++) for(int xx=0;xx<4;xx++) {
            int j=(y*4+yy)*im->w*4+x*4+xx;
            uint32_t v=base->rgba[j],out=(im==effect_dst && effect_mode==0) ? v&0xff000000u : 0xff000000u;
            for(int shift=0;shift<=16;shift+=8) {
                int c=v>>shift&255,from=a>>shift&255,to=b>>shift&255;
                if(im==effect_dst && effect_mode==1) c=from ? c*to/from : to;
                else if(im==effect_dst && effect_mode==2) c=from<255 ? 255-(255-c)*(255-to)/(255-from) : to;
                else c+=to-from;
                out|=(uint32_t)SDL_clamp(c,0,255)<<shift;
            }
            if(now==g_colorKey && low!=port_fb) out&=0xffffff;
            im->rgba[j]=out;
        }
        im->seen[i]=now;
    }
}

static uint32_t blend(uint32_t s,uint32_t d)
{
    unsigned a=s>>24;if(a==255)return s;if(!a)return d;
    unsigned da=d>>24,oa=a+da*(255-a)/255;
    uint32_t out=oa<<24;
    for(int sh=0;sh<=16;sh+=8) {
        unsigned c=((s>>sh&255)*a+(d>>sh&255)*da*(255-a)/255)/oa;
        out|=c<<sh;
    }
    return out;
}

static uint32_t patch_edge(uint32_t pixel,int x,int y,int w,int h)
{
    // Ease into the existing room over two logical pixels, reducing the band
    // for tiny patches. The outermost native pixels match the room exactly.
    int band=SDL_min(HD_SCALE*2,SDL_min(w,h)/4);
    if(band<1)return pixel;
    int edge=SDL_min(SDL_min(x,w-1-x),SDL_min(y,h-1-y));
    if(edge>=band)return pixel;
    unsigned coverage=255*edge*edge*(3*band-2*edge)/(band*band*band);
    return (pixel&0xffffff) | ((pixel>>24)*coverage/255)<<24;
}

void hd_blit(uint16_t *dst,int x,int y,int w,int h,const uint16_t *src,
             int stride,int sx,int sy,int step,int keyed,const uint16_t *mask)
{
    size_t off=0;
    HDImage *d=find(dst,NULL),*s=find(src,&off);
    int feather=s && s->sprite_patch && !mask;
    if(d)hd_sync(dst);if(s)hd_sync(s->low);
    int dw=d ? d->w : SCREEN_W,dh=d ? d->h : SCREEN_H;
    for(int dy=0;dy<h;dy++) for(int dx=0;dx<w;dx++) {
        if(x+dx<0 || y+dy<0 || x+dx>=dw || y+dy>=dh) continue;
        int at=(sy+dy*step)*stride+sx+dx*step;
        uint16_t v=src[at];
        if(mask && mask[dy*w+dx]==g_colorKey)continue;
        int skip=keyed && v==g_colorKey;
        if(!skip) dst[(y+dy)*dw+x+dx]=mask && v==g_colorKey ? g_colorKey+1 : v;
        if(!d)continue;
        if(!skip)d->seen[(y+dy)*dw+x+dx]=dst[(y+dy)*dw+x+dx];
        // Native text may have coverage inside a logically transparent pixel.
        // Registered sources carry their own opacity, including composed layers.
        if(skip && !s)continue;
        for(int yy=0;yy<4;yy++) for(int xx=0;xx<4;xx++) {
            uint32_t pixel=color(v);
            if(s) {
                size_t pos=off+at;
                if(pos >= (size_t)s->w*s->h)port_fatal("HD blit exceeds source");
                int px=(pos%s->w)*4+xx*step,py=(pos/s->w)*4+yy*step;
                px=SDL_min(px,s->w*4-1);py=SDL_min(py,s->h*4-1);
                pixel=s->rgba[py*s->w*4+px];
                if(feather)pixel=patch_edge(pixel,px,py,s->w*4,s->h*4);
            }
            if(mask)pixel|=0xff000000u;
            int j=((y+dy)*4+yy)*dw*4+(x+dx)*4+xx;
            // The GAPI framebuffer is opaque. Layer glyphs can carry fractional
            // alpha over keyed black; flatten it before SDL's opaque upload.
            // Copying their straight RGB alone would reveal invisible AA fringes.
            if(dst==port_fb && !keyed && !(s && s->font) && !feather)
                pixel=blend(pixel,color(g_colorKey)|0xff000000u);
            d->rgba[j]=(keyed || (s && s->font) || feather) ? blend(pixel,d->rgba[j]) : pixel;
        }
    }
}

// Font masks use native pixel coordinates and logical clipping bounds.
void hd_alpha(uint16_t *dst,int x,int y,int w,int h,const uint8_t *alpha,
              uint32_t rgb,int left,int top,int right,int bottom)
{
    HDImage *d=find(dst,NULL);if(!d || !alpha)return;
    hd_sync(dst);
    int x0=SDL_max(x,SDL_max(0,left)*4),y0=SDL_max(y,SDL_max(0,top)*4);
    int x1=SDL_min(x+w,SDL_min(d->w,right)*4),y1=SDL_min(y+h,SDL_min(d->h,bottom)*4);
    if(x0>=x1 || y0>=y1)return;
    for(int yy=y0;yy<y1;yy++)for(int xx=x0;xx<x1;xx++) {
        uint32_t a=alpha[(yy-y)*w+xx-x];
        int i=yy*d->w*4+xx;
        d->rgba[i]=blend(a<<24|rgb,d->rgba[i]);
    }
    // Maintain low-resolution mirrors and snapshots for original effects/saves.
    for(int yy=y0/4;yy<(y1+3)/4;yy++)for(int xx=x0/4;xx<(x1+3)/4;xx++) {
        unsigned r=0,g=0,b=0,a=0;
        for(int sy=0;sy<4;sy++)for(int sx=0;sx<4;sx++) {
            uint32_t v=d->rgba[(yy*4+sy)*d->w*4+xx*4+sx];
            unsigned coverage=v>>24;a+=coverage;
            r+=(v>>16&255)*coverage;g+=(v>>8&255)*coverage;b+=(v&255)*coverage;
        }
        uint16_t low=a ? ((r/4080)>>3)<<11|((g/4080)>>2)<<5|((b/4080)>>3) : g_colorKey;
        if(a && low==g_colorKey)low=g_colorKey+1;
        dst[yy*d->w+xx]=d->seen[yy*d->w+xx]=low;
    }
}

const uint32_t *hd_frame(void)
{
    hd_sync(port_fb);
    HDImage *im=find(port_fb,NULL);
    return im ? im->rgba : NULL;
}
