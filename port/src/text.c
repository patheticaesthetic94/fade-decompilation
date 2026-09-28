// English/Windows-1252 adapter backed by pinned stb_truetype. Natural fractional
// advances and pair kerning are used for BOTH line layout and raster placement.
#include "text.h"
#include <math.h>
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include "stb_truetype.h"

typedef struct Face { stbtt_fontinfo info; void *data; float scale; int ascent, step; } Face;
typedef struct Style { FontGlyphs *legacy; Face *face; uint32_t rgb; } Style;
static Face faces[2];
static Style styles[6];
static int enabled, styles_n;
static TextLayout *layouts;
// Bounded glyph-mask cache. Quarter-pixel x phases preserve fractional spacing.
typedef struct Mask { Face *face; int code, phase, w,h,x,y; unsigned char *ink; } Mask;
static Mask cache[512];
static int cache_next;

int text_enabled(void) { return enabled; }
void text_init(void)
{
    size_t n;
    void *flag=SDL_LoadFile("fonts/runtime.txt",&n);
    if(!flag)return;
    SDL_free(flag);enabled=1;
    const char *paths[]={"fonts/ComicNeue-Bold.ttf","fonts/Arimo.ttf"};
    for(int i=0;i<2;i++) {
        Face *f=&faces[i];f->data=SDL_LoadFile(paths[i],&n);
        if(!f->data || !stbtt_InitFont(&f->info,f->data,0))port_fatal("Invalid bundled font: %s",paths[i]);
        // EM sizes, independent of bitmap cells. 9px game text, 7px popup text.
        f->scale=stbtt_ScaleForMappingEmToPixels(&f->info,(i ? 7.f : 9.f)*HD_SCALE);
        int a,d,g;stbtt_GetFontVMetrics(&f->info,&a,&d,&g);
        f->ascent=(int)ceilf(a*f->scale/HD_SCALE);
        f->step=(int)ceilf((a-d+g)*f->scale/HD_SCALE);
    }
    port_log("Runtime fonts: Comic Neue Bold / Arimo; natural advances, kerning, 4x rasterization");
}
static Style *style(FontGlyphs *font)
{
    for(int i=0;i<styles_n;i++)if(styles[i].legacy==font)return &styles[i];
    port_fatal("Runtime font identity not loaded: %p",(void *)font);return NULL;
}
void text_load(FontGlyphs *font,const char *path)
{
    Style *s=NULL;
    for(int i=0;i<styles_n;i++)if(styles[i].legacy==font)s=&styles[i];
    if(!s) {if(styles_n==6)port_fatal("Too many font roles");s=&styles[styles_n++];}
    s->legacy=font;s->face=&faces[strstr(path,"popups") ? 1 : 0];
    s->rgb=strstr(path,"orange") ? 0xff8c00 : strstr(path,"jaune") ? 0xffff00 :
        strstr(path,"bleu") ? 0x0080ff : strstr(path,"noir") ? 0 : 0xffffff;
    port_log("Runtime font role: %s (line step %d)",path,s->face->step);
}
// Decode UTF-16; normalize surviving CP1252 apostrophes; malformed input is U+FFFD.
static int codepoint(const wchar16 *s,int n,int *at)
{
    unsigned c=s[(*at)++];
    if(c==0x91)return 0x2018;if(c==0x92)return 0x2019;
    if(c>=0xd800 && c<=0xdbff) {
        if(*at<n && s[*at]>=0xdc00 && s[*at]<=0xdfff) return 0x10000+((c-0xd800)<<10)+(s[(*at)++]-0xdc00);
        return 0xfffd;
    }
    return c>=0xdc00 && c<=0xdfff ? 0xfffd : c;
}
static int glyph(Face *f,int c)
{
    int g=stbtt_FindGlyphIndex(&f->info,c);
    return g ? g : stbtt_FindGlyphIndex(&f->info,'?');
}
float text_width(FontGlyphs *font,const wchar16 *s,int n)
{
    Face *f=style(font)->face;float x=0;int prev=0;
    for(int i=0;i<n;) {
        int c=codepoint(s,n,&i),g=glyph(f,c),a,b;
        if(prev)x+=stbtt_GetGlyphKernAdvance(&f->info,prev,g)*f->scale;
        stbtt_GetGlyphHMetrics(&f->info,g,&a,&b);x+=a*f->scale;prev=g;
    }
    return x/HD_SCALE;
}
int text_step(FontGlyphs *font) { return style(font)->face->step; }
static Mask *mask(Face *f,int g,int phase)
{
    for(int i=0;i<512;i++)if(cache[i].face==f && cache[i].code==g && cache[i].phase==phase)return &cache[i];
    Mask *m=&cache[cache_next++%512];stbtt_FreeBitmap(m->ink,NULL);
    m->face=f;m->code=g;m->phase=phase;
    m->ink=stbtt_GetGlyphBitmapSubpixel(&f->info,f->scale,f->scale,phase/4.f,0,g,&m->w,&m->h,&m->x,&m->y);
    return m;
}
void text_run(FontGlyphs *font,const wchar16 *s,int n,uint16_t *dst,
              int x,int y,int left,int top,int right,int bottom,int reveal)
{
    Style *st=style(font);Face *f=st->face;
    float pen=x*HD_SCALE;int prev=0,shown=0;
    for(int i=0;i<n;) {
        int c=codepoint(s,n,&i),g=glyph(f,c),a,b;
        if(prev)pen+=stbtt_GetGlyphKernAdvance(&f->info,prev,g)*f->scale;
        // Reveal fixed glyph positions from the complete run; no prefix re-layout.
        if(reveal<0 || shown<reveal) {
            int px=(int)floorf(pen),phase=(int)floorf((pen-px)*4);
            Mask *m=mask(f,g,phase);
            hd_alpha(dst,px+m->x,(y+f->ascent)*HD_SCALE+m->y,m->w,m->h,m->ink,st->rgb,
                     left,top,right,bottom);
        }
        stbtt_GetGlyphHMetrics(&f->info,g,&a,&b);pen+=a*f->scale;prev=g;shown++;
    }
}
TextLayout *text_layout(TextList *list)
{
    for(TextLayout *l=layouts;l;l=l->next)if(l->owner==list)return l;
    TextLayout *l=SDL_calloc(1,sizeof *l);if(!l)port_fatal("Text layout allocation failed");
    l->owner=list;l->page=1;l->next=layouts;layouts=l;return l;
}
static void compatibility(TextLayout *l)
{
    TextList *t=l->owner;
    t->count=SDL_min(l->lines_n,255);t->top=SDL_min(l->top,255);t->page=SDL_min(l->page,255);
    t->hasText=l->lines_n>0;
}
void text_clear(TextList *list,int destroy)
{
    TextLayout *l=text_layout(list);
    for(int i=0;i<l->paragraphs_n;i++)SDL_free(l->paragraphs[i].text);
    SDL_free(l->paragraphs);SDL_free(l->lines);
    l->paragraphs=NULL;l->lines=NULL;l->paragraphs_n=l->lines_n=l->top=l->inventory=0;
    compatibility(l);
    if(destroy) {
        TextLayout **link=&layouts;while(*link!=l)link=&(*link)->next;
        *link=l->next;SDL_free(l);
    }
}
static void add_line(TextLayout *l,int p,int start,int length)
{
    l->lines=SDL_realloc(l->lines,(l->lines_n+1)*sizeof *l->lines);
    if(!l->lines)port_fatal("Text line allocation failed");
    l->lines[l->lines_n++]=(TextLine){p,start,length};
}
void text_reflow(TextList *list)
{
    TextLayout *l=text_layout(list);
    int anchor_p=-1,anchor_s=0;
    if(l->top<l->lines_n) {anchor_p=l->lines[l->top].paragraph;anchor_s=l->lines[l->top].start;}
    SDL_free(l->lines);l->lines=NULL;l->lines_n=0;
    for(int p=0;p<l->paragraphs_n;p++) {
        TextParagraph *para=&l->paragraphs[p];int n=para->length,pos=0;
        wchar16 space=' ';float room=list->right-list->x-para->indent*text_width(para->font,&space,1);
        while(pos<n) {
            int start=pos,end=pos,last_space=-1;
            while(end<n && para->text[end]!='\r' && para->text[end]!='\n') {
                int next=end+1;
                if(para->text[end]>=0xd800 && para->text[end]<=0xdbff && next<n && para->text[next]>=0xdc00 && para->text[next]<=0xdfff)next++;
                if(text_width(para->font,para->text+start,next-start)>room && end>start)break;
                if(para->text[end]==' ')last_space=end;
                end=next;
            }
            if(end<n && para->text[end]!='\r' && para->text[end]!='\n' && last_space>start)end=last_space;
            int ink_end=end;while(ink_end>start && para->text[ink_end-1]==' ')ink_end--;
            add_line(l,p,start,ink_end-start);pos=end;
            if(pos<n && (para->text[pos]=='\r' || para->text[pos]=='\n')) {
                if(para->text[pos++]=='\r' && pos<n && para->text[pos]=='\n')pos++;
                if(pos==n)add_line(l,p,pos,0);
            } else while(pos<n && para->text[pos]==' ')pos++;
        }
        if(!n)add_line(l,p,0,0);
    }
    l->page=SDL_max(1,(list->bottom-list->top_y)/text_step(list->font));
    l->top=0;
    if(anchor_p>=0)for(int i=0;i<l->lines_n;i++)if(l->lines[i].paragraph==anchor_p && l->lines[i].start<=anchor_s)l->top=i;
    l->top=SDL_clamp(l->top,0,SDL_max(0,l->lines_n-1));compatibility(l);
}
void text_append(TextList *list,CString text,FontGlyphs *font,int indent,int identity)
{
    TextLayout *l=text_layout(list);int n=*(int *)(text.str-4);
    l->paragraphs=SDL_realloc(l->paragraphs,(l->paragraphs_n+1)*sizeof *l->paragraphs);
    if(!l->paragraphs)port_fatal("Text paragraph allocation failed");
    TextParagraph *p=&l->paragraphs[l->paragraphs_n++];
    p->text=SDL_malloc((n+1)*sizeof *p->text);if(!p->text)port_fatal("Text allocation failed");
    memcpy(p->text,text.str,n*sizeof *p->text);p->text[n]=0;
    p->length=n;p->font=font;p->indent=indent;p->identity=identity;
    text_reflow(list);
}
int text_line_at(TextList *list,int y)
{
    TextLayout *l=text_layout(list);int row=(y-list->top_y)/text_step(list->font);
    if(y<list->top_y || y>=list->bottom || row>=l->page || row+l->top>=l->lines_n)return -1;
    return row+l->top;
}
int text_identity(TextList *list,int line)
{
    TextLayout *l=text_layout(list);
    if(line<0 || line>=l->lines_n)return -1;
    return l->paragraphs[l->lines[line].paragraph].identity;
}
int text_type_run(TextList *list,FontGlyphs *font,const wchar16 *s,int n,
                  int x,int y,int layer,int can_skip)
{
    int w=list->right-list->x,h=SDL_min(text_step(list->font),list->bottom-y),typing=1;
    if(w<=0 || h<=0)return typing;
    uint16_t *saved=arena_alloc((size_t)w*h*2);
    tagMSG *msg=arena_alloc(sizeof *msg);
    Screen_ReadLayer(list->screen,list->x,y,w,h,saved,layer);
    int count=0;for(int i=0;i<n;) {codepoint(s,n,&i);count++;}
    for(int chars=1;chars<=count;chars++) {
        Screen_BlitToLayer(list->screen,list->x,y,w,h,saved,layer);
        text_run(font,s,n,list->screen->layer[layer],x,y,list->x,list->top_y,list->right,list->bottom,typing ? chars : -1);
        Screen_PresentRect(list->screen,list->x,y,w,h,layer);
        if(!typing)break;
        Sleep(30);
        if(PeekMessageW(msg,0,0,0,1) && can_skip && (msg->message==0x100 || msg->message==0x202))typing=0;
    }
    arena_free(msg);arena_free(saved);return typing;
}
void text_draw(TextList *list,int layer,int animated,int can_skip)
{
    TextLayout *l=text_layout(list);int step=text_step(list->font),typing=animated;
    if(!l->lines_n)return;
    TextList_BlitToLayer(list,layer);
    if(animated)TextList_DrawDirect(list);
    for(int row=0;row<l->page && l->top+row<l->lines_n;row++) {
        TextLine *line=&l->lines[l->top+row];TextParagraph *p=&l->paragraphs[line->paragraph];
        wchar16 space=' ';int x=list->x+(int)ceilf(p->indent*text_width(p->font,&space,1)),y=list->top_y+row*step;
        int n=line->length;
        if(!typing)text_run(p->font,p->text+line->start,n,list->screen->layer[layer],x,y,list->x,list->top_y,list->right,list->bottom,-1);
        else typing=text_type_run(list,p->font,p->text+line->start,n,x,y,layer,can_skip);
    }
    if(animated)Screen_PresentRect(list->screen,list->x,list->top_y,list->right-list->x,list->bottom-list->top_y,layer);
}
