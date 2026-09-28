// Uses actual APK native code and bundled outline fonts, without an Android UI.
#include "../../port/src/text.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#undef main
void *SDL_LoadFile(const char *path,size_t *size)
{
    FILE *f=fopen(path,"rb");if(!f)return NULL;
    fseek(f,0,SEEK_END);long n=ftell(f);rewind(f);
    char *data=SDL_malloc(n+1);assert(fread(data,1,n,f)==(size_t)n);
    data[n]=0;fclose(f);if(size)*size=n;return data;
}
static CString string(const char *s) {CString c;CString_CtorA(&c,(char *_P32)s);return c;}
static void set(TextList *t,const char *s)
{
    // ANSI constructor receives low arena memory under the guest ABI.
    char *low=arena_alloc(strlen(s)+1);strcpy(low,s);
    CString c=string(low);arena_free(low);TextList_SetText(t,c);
}
int main(void)
{
    SDL_Init(0);arena_init();size_t n;
    void *exe=SDL_LoadFile("Fade.exe",&n);assert(exe);arena_load_image(exe,n);SDL_free(exe);
    g_colorKey=0;port_fb=arena_calloc(240*320*2);hd_init();text_init();assert(text_enabled());
    text_load(&g_fontTextWhite,"fonts/font texte blanche.bmp");
    text_load(&g_fontTextYellow,"fonts/font texte jaune.bmp");
    text_load(&g_fontPopupWhite,"fonts/font popups blanche.bmp");
    wchar16 natural[]={'M','y',' ','d','i','a','r','y'};
    float width=text_width(&g_fontTextWhite,natural,8);
    assert(width>20 && width<43); // Outline advance differs from 43 legacy cell pixels.
    wchar16 quote[]={0x92,0xe9},unicode[]={0x2019,0xe9},bad[]={0xd800},fallback[]={'?'};
    assert(fabsf(text_width(&g_fontTextWhite,quote,2)-text_width(&g_fontTextWhite,unicode,2))<0.001f);
    assert(text_width(&g_fontTextWhite,bad,1)>0);
    assert(text_width(&g_fontTextWhite,fallback,1)>0);
    Screen *s=arena_calloc(sizeof *s);Screen_Init(s,240,320);
    TextList *t=arena_calloc(sizeof *t);TextList_Ctor(t);t->screen=s;
    TextList_SetRect(t,21,240,214,300,&g_fontTextWhite);
    set(t,"first\nsecond\n");assert(text_layout(t)->lines_n==3);
    set(t,"012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
    TextLayout *l=text_layout(t);assert(l->lines_n>1);
    for(int i=0;i<l->lines_n;i++) {
        TextLine ln=l->lines[i];TextParagraph *p=&l->paragraphs[ln.paragraph];
        assert(text_width(p->font,p->text+ln.start,ln.length)<=193.01f);
    }
    // No signed-char index hangs above 127 characters or byte-page wrap above 255.
    char longtext[4000];for(int i=0;i<600;i++) {longtext[i*2]='A';longtext[i*2+1]='\n';}longtext[1200]=0;
    set(t,longtext);assert(l->lines_n==601);
    while(TextList_PageDown(t)) {}
    assert(l->top>255 && TextList_AtEnd(t));
    assert(TextList_LineAt(t,30,241)==l->top);
    TextList_SetRect(t,21,240,150,300,&g_fontTextWhite);assert(l->top>255);
    while(TextList_PageUp(t)) {}assert(l->top==0);
    // Wrapped choice continuation lines share one ID and colour-only highlights
    // leave line breaks, page and every tap target unchanged.
    Rec15c *topic=arena_calloc(sizeof *topic);
    char *low=arena_alloc(256);strcpy(low,"A title");CString_CtorA(&topic->title,low);
    strcpy(low,"A longer dialogue choice that deliberately wraps over several lines in the narrow panel");
    CString_CtorA(&topic->choices[0].text,low);topic->choices[0].replies[0].val=0;topic->choices[0].active=1;topic->count=1;
    TextList_SetDialogMenu(t,(int)(uintptr_t)topic,&g_fontTextWhite,&g_fontTextWhite,&g_fontTextYellow,-1);
    int lines=l->lines_n;assert(lines>3);
    for(int i=2;i<lines;i++)assert(text_identity(t,i)==0);
    assert(text_identity(t,0)==-1 && text_identity(t,1)==-1);
    TextList_PageDown(t);int top=l->top;
    TextList_SetDialogMenu(t,(int)(uintptr_t)topic,&g_fontTextWhite,&g_fontTextWhite,&g_fontTextYellow,0);
    assert(l->lines_n==lines && l->top==top);
    for(int i=2;i<lines;i++)assert(text_identity(t,i)==0);
    Screen_FillAll(s,0);Screen_FillLayer(s,0x001f,3);
    text_run(&g_fontTextWhite,natural,8,s->layer[1],30,40,30,40,100,60,-1);
    Screen_Present(s);int covered=0,fractional=0;
    const uint32_t *frame=hd_frame();
    for(int y=160;y<240;y++)for(int x=120;x<400;x++) {
        unsigned v=frame[y*960+x]&0xffffff;
        if(v!=0x0000ff)covered++;
        if((v>>16)>0 && (v>>16)<255)fractional++;
    }
    assert(covered>0 && fractional>0);
    uint16_t *saved=arena_alloc(70*20*2);Screen_ReadLayer(s,30,40,70,20,saved,0);
    uint32_t before[70*4*20*4];
    for(int y=0;y<80;y++)memcpy(before+y*280,frame+(160+y)*960+120,280*4);
    Screen_FillAll(s,0);Screen_BlitToLayer(s,30,40,70,20,saved,3);Screen_Present(s);frame=hd_frame();
    for(int y=0;y<80;y++)assert(!memcmp(before+y*280,frame+(160+y)*960+120,280*4));
    // Explicit clip excludes ALL native ink outside bounds.
    Screen_FillAll(s,0);
    text_run(&g_fontTextWhite,natural,8,s->layer[1],30,40,35,42,45,48,-1);
    Screen_PresentLayer(s,1);frame=hd_frame();
    for(int y=0;y<1280;y++)for(int x=0;x<960;x++)
        if(x<140 || x>=180 || y<168 || y>=192)assert((frame[y*960+x]&0xffffff)==0);
    // Skipping the typewriter produces exactly the full run, without AA buildup.
    TextList_SetRect(t,21,40,214,60,&g_fontTextWhite);
    Screen_FillAll(s,0);Screen_FillLayer(s,0x001f,1);
    text_run(&g_fontTextWhite,natural,8,s->layer[1],21,40,21,40,214,60,-1);
    Screen_PresentLayer(s,1);frame=hd_frame();
    uint32_t *expected=SDL_malloc(960*1280*4);memcpy(expected,frame,960*1280*4);
    Screen_FillLayer(s,0x001f,1);msg_post(0x202,0,0);
    assert(text_type_run(t,&g_fontTextWhite,natural,8,21,40,1,1)==0);
    Screen_PresentLayer(s,1);assert(!memcmp(expected,hd_frame(),960*1280*4));SDL_free(expected);
    // Wrapped inventory names map all continuation rows to one visible ordinal.
    Game *game=arena_calloc(sizeof *game);game->state=arena_calloc(sizeof(GameState));
    TextList_Ctor(&game->inv);game->inv.screen=s;
    TextList_SetRect(&game->inv,21,40,90,170,&g_fontTextWhite);
    low[0]=0;CString_CtorA(&game->invStr,low);game->font2=&g_fontTextYellow;
    game->state->inventory.count=1;
    GameObj *obj=&game->state->inventory.objs[0];obj->selected=1;
    strcpy(low,"A deliberately long inventory item name");CString_CtorA(&obj->name,low);
    strcpy(low,"ignored legacy display string");CString input;CString_CtorA(&input,low);
    Game_SetInventoryText(game,input);TextLayout *inv=text_layout(&game->inv);assert(inv->lines_n>1);
    for(int i=0;i<inv->lines_n;i++)assert(text_identity(&game->inv,i)==0);
    for(int i=0;i<inv->lines_n && i<inv->page;i++)
        assert(TextList_LineAt(&game->inv,30,41+i*text_step(&g_fontTextWhite))==0);
    TextList_Reset(t);TextList_Ctor(t);assert(text_layout(t)->lines_n==0);
    printf("Runtime text passed: natural width %.3f, encoding, newlines, long words, 601 lines, paging/reflow, wrapped choice IDs/highlights, alpha, saved backgrounds, clipping, typewriter skip, inventory IDs, pointer reuse\n",width);
    return 0;
}
