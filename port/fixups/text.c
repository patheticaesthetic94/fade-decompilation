// Recovered text API adapters. Legacy mode retains the original implementation.
#include "../src/text.h"
#include <math.h>

// 0001d600 Font_MaxGlyphWidth
// HD_WRAP Font_MaxGlyphWidth
uint Font_MaxGlyphWidth(int font)
{ return text_enabled() ? text_step((FontGlyphs *)(uintptr_t)(uint32_t)font) : legacy_Font_MaxGlyphWidth(font); }

// 0001c064 TextList_Ctor
// HD_WRAP TextList_Ctor
int TextList_Ctor(TextList *_P32 t)
{ if(text_enabled())text_clear(t,1);return legacy_TextList_Ctor(t); }

// 0001c3a4 TextList_Reset
// HD_WRAP TextList_Reset
void TextList_Reset(TextList *_P32 t)
{ if(text_enabled())text_clear(t,1);legacy_TextList_Reset(t); }

// 0001c550 TextList_Clear
// HD_WRAP TextList_Clear
void TextList_Clear(TextList *_P32 t)
{ if(text_enabled())text_clear(t,0);legacy_TextList_Clear(t); }

// 0001c4c4 TextList_SetRect
// HD_WRAP TextList_SetRect
void TextList_SetRect(TextList *_P32 t,int x,int y,int right,int bottom,FontGlyphs *_P32 font)
{
    legacy_TextList_SetRect(t,x,y,right,bottom,font);
    if(text_enabled())text_reflow(t);
}

// 0001c4e4 TextList_SetFont
// HD_WRAP TextList_SetFont
void TextList_SetFont(TextList *_P32 t,FontGlyphs *_P32 font)
{
    if(!text_enabled()) {legacy_TextList_SetFont(t,font);return;}
    FontGlyphs *old=t->font;t->font=font;
    TextLayout *l=text_layout(t);
    for(int i=0;i<l->paragraphs_n;i++)if(l->paragraphs[i].font==old)l->paragraphs[i].font=font;
    text_reflow(t);
}

// 0001c6b0 TextList_CalcLinesPerPage
// HD_WRAP TextList_CalcLinesPerPage
undefined1 TextList_CalcLinesPerPage(TextList *_P32 t,FontGlyphs *_P32 font)
{ return text_enabled() ? SDL_clamp((t->bottom-t->top_y)/text_step(font),1,255) : legacy_TextList_CalcLinesPerPage(t,font); }

// 0001c570 TextList_SetText
// HD_WRAP TextList_SetText
void TextList_SetText(TextList *_P32 t,CString s)
{
    if(!text_enabled()) {legacy_TextList_SetText(t,s);return;}
    TextList_Clear(t);
    if(*(int *)(s.str-4)>0)text_append(t,s,t->font,0,-1);
    CString_Dtor(&s);
}

// 0001c5e8 TextList_AppendText
// HD_WRAP TextList_AppendText
void TextList_AppendText(TextList *_P32 t,CString s,int font,char indent)
{
    if(!text_enabled()) {legacy_TextList_AppendText(t,s,font,indent);return;}
    if(*(int *)(s.str-4)>0)text_append(t,s,(FontGlyphs *)(uintptr_t)(uint32_t)font,indent,-1);
    CString_Dtor(&s);
}

// 0001d260 TextList_WrapText
// HD_WRAP TextList_WrapText
void TextList_WrapText(TextList *_P32 t,CString s,FontGlyphs *_P32 font,char indent)
{
    if(!text_enabled()) {legacy_TextList_WrapText(t,s,font,indent);return;}
    text_append(t,s,font,indent,-1);CString_Dtor(&s);
}

// 0001c65c TextList_SetLineTag
// HD_WRAP TextList_SetLineTag
void TextList_SetLineTag(TextList *_P32 t,char line,int font)
{
    if(!text_enabled()) {legacy_TextList_SetLineTag(t,line,font);return;}
    TextLayout *l=text_layout(t);int at=(unsigned char)line;
    if(at<l->lines_n) {
        l->paragraphs[l->lines[at].paragraph].font=(FontGlyphs *)(uintptr_t)(uint32_t)font;
        text_reflow(t);
    }
}

// 0001caf8 TextList_GetLineCount
// HD_WRAP TextList_GetLineCount
byte TextList_GetLineCount(TextList *_P32 t)
{ return text_enabled() ? SDL_min(text_layout(t)->lines_n,255) : legacy_TextList_GetLineCount(t); }

static bool navigate(TextList *t,int delta,int page)
{
    TextLayout *l=text_layout(t);int old=l->top;
    if(page)delta*=l->page;
    if(delta>0 && old+l->page<l->lines_n)l->top=SDL_min(old+delta,l->lines_n-1);
    if(delta<0)l->top=SDL_max(0,old+delta);
    t->top=SDL_min(l->top,255);return old!=l->top;
}

// 0001cb00 TextList_PageUp
// HD_WRAP TextList_PageUp
bool TextList_PageUp(TextList *_P32 t)
{ return text_enabled() ? navigate(t,-1,1) : legacy_TextList_PageUp(t); }
// 0001cb30 TextList_PageDown
// HD_WRAP TextList_PageDown
bool TextList_PageDown(TextList *_P32 t)
{ return text_enabled() ? navigate(t,1,1) : legacy_TextList_PageDown(t); }
// 0001cb58 TextList_LineUp
// HD_WRAP TextList_LineUp
bool TextList_LineUp(TextList *_P32 t)
{ return text_enabled() ? navigate(t,-1,0) : legacy_TextList_LineUp(t); }
// 0001cb74 TextList_LineDown
// HD_WRAP TextList_LineDown
bool TextList_LineDown(TextList *_P32 t)
{ return text_enabled() ? navigate(t,1,0) : legacy_TextList_LineDown(t); }
// 0001cb9c TextList_AtEnd
// HD_WRAP TextList_AtEnd
bool TextList_AtEnd(TextList *_P32 t)
{ TextLayout *l=text_enabled() ? text_layout(t) : NULL;return l ? l->top+l->page>=l->lines_n : legacy_TextList_AtEnd(t); }

// 0001d164 TextList_LineAt
// HD_WRAP TextList_LineAt
int TextList_LineAt(TextList *_P32 t,undefined4 x,int y)
{
    if(!text_enabled())return legacy_TextList_LineAt(t,x,y);
    if((int)x<t->x || (int)x>=t->right)return -1;
    int line=text_line_at(t,y);
    // Inventory's recovered caller expects a visible object ordinal, not a line.
    return text_layout(t)->inventory ? text_identity(t,line) : line;
}

// 0001cda8 TextList_Draw
// HD_WRAP TextList_Draw
void TextList_Draw(TextList *_P32 t,char layer)
{ if(text_enabled())text_draw(t,(unsigned char)layer,0,0);else legacy_TextList_Draw(t,layer); }
// 0001cf38 TextList_DrawTyped
// HD_WRAP TextList_DrawTyped
void TextList_DrawTyped(TextList *_P32 t,char layer,char skip)
{ if(text_enabled())text_draw(t,(unsigned char)layer,1,skip);else legacy_TextList_DrawTyped(t,layer,skip); }

// 0001cbc0 Text_DrawLine
// HD_WRAP Text_DrawLine
void Text_DrawLine(TextList *_P32 t,CString s,FontGlyphs *_P32 font,undefined4 indent,int y,char layer)
{
    if(!text_enabled()) {legacy_Text_DrawLine(t,s,font,indent,y,layer);return;}
    text_run(font,s.str,*(int *)(s.str-4),t->screen->layer[(unsigned char)layer],t->x,y,t->x,t->top_y,t->right,t->bottom,-1);
    CString_Dtor(&s);
}

// 0001cc40 Text_TypeLine
// HD_WRAP Text_TypeLine
int Text_TypeLine(TextList *_P32 t,CString s,FontGlyphs *_P32 font,undefined4 indent,uint y,char layer,char skip)
{
    if(!text_enabled())return legacy_Text_TypeLine(t,s,font,indent,y,layer,skip);
    int typing=text_type_run(t,font,s.str,*(int *)(s.str-4),t->x,y,(unsigned char)layer,skip);
    CString_Dtor(&s);return typing;
}

// 0001e3cc Font_TextWidth
// HD_WRAP Font_TextWidth
char Font_TextWidth(FontGlyphs *_P32 font,CString s)
{
    if(!text_enabled())return legacy_Font_TextWidth(font,s);
    // Byte ABI is retained for compatibility; authoritative layout uses floats.
    int w=(int)ceilf(text_width(font,s.str,*(int *)(s.str-4)));CString_Dtor(&s);
    return (char)SDL_clamp(w,0,127);
}

// 0001e440 Text_CountLines
// HD_WRAP Text_CountLines
byte Text_CountLines(FontGlyphs *_P32 font,int left,int right,CString s)
{
    if(!text_enabled())return legacy_Text_CountLines(font,left,right,s);
    TextList *t=arena_calloc(sizeof *t);TextList_Ctor(t);
    t->font=font;t->x=left;t->right=right;t->bottom=200;
    text_append(t,s,font,0,-1);int n=text_layout(t)->lines_n;
    CString_Dtor(&s);TextList_Reset(t);arena_free(t);return SDL_min(n,255);
}

static void dialog(TextList *t,Rec15c *topic,FontGlyphs *title,FontGlyphs *normal,FontGlyphs *hi,int selected)
{
    int old=text_layout(t)->top;
    TextList_Clear(t);
    text_append(t,topic->title,title,0,-1);
    CString blank;CString_CtorA(&blank,"");text_append(t,blank,title,0,-1);CString_Dtor(&blank);
    for(int i=0;i<topic->count && i<5;i++)if(Rec44_AnyActive((Rec44 *_P32)topic,i))
        text_append(t,topic->choices[i].text,i==selected ? hi : normal,2,i);
    TextLayout *l=text_layout(t);l->top=SDL_min(old,SDL_max(0,l->lines_n-1));t->top=SDL_min(l->top,255);
}
// 0001c704 TextList_SetDialogMenu
// HD_WRAP TextList_SetDialogMenu
void TextList_SetDialogMenu(TextList *_P32 t,int topic,FontGlyphs *_P32 title,FontGlyphs *_P32 normal,FontGlyphs *_P32 hi,char selected)
{
    if(!text_enabled()) {legacy_TextList_SetDialogMenu(t,topic,title,normal,hi,selected);return;}
    dialog(t,(Rec15c *)(uintptr_t)(uint32_t)topic,title,normal,hi,selected);
}
// 0001c904 TextList_SetDialogMenu2
// HD_WRAP TextList_SetDialogMenu2
void TextList_SetDialogMenu2(TextList *_P32 t,int topic,FontGlyphs *_P32 title,FontGlyphs *_P32 normal,FontGlyphs *_P32 hi,char selected)
{
    if(!text_enabled()) {legacy_TextList_SetDialogMenu2(t,topic,title,normal,hi,selected);return;}
    dialog(t,(Rec15c *)(uintptr_t)(uint32_t)topic,title,normal,hi,selected);
}

// 00026f94 Game_DialogChoiceAtLine
// HD_WRAP Game_DialogChoiceAtLine
uint Game_DialogChoiceAtLine(Game *_P32 g,int line)
{ return text_enabled() ? (uint)text_identity(&g->desc,line) : legacy_Game_DialogChoiceAtLine(g,line); }

// 00026ec4 Game_SetInventoryText
// HD_WRAP Game_SetInventoryText
void Game_SetInventoryText(Game *_P32 g,CString s)
{
    if(!text_enabled()) {legacy_Game_SetInventoryText(g,s);return;}
    CString_Assign(&g->invStr,&s);TextList_Clear(&g->inv);int ordinal=0;
    int count=Inventory_Count(&g->state->inventory)&255;
    for(int i=0;i<count;i++) {
        GameObj *obj=Inventory_GetObj(&g->state->inventory,i);
        if(!GameObj_IsSelected(obj))continue;
        text_append(&g->inv,obj->name,i==g->invSel ? (FontGlyphs *)(uintptr_t)(uint32_t)g->font2 : g->inv.font,0,ordinal++);
    }
    text_layout(&g->inv)->inventory=1;CString_Dtor(&s);
}

// 0001e9a0 PopupMenu_DrawText
// HD_WRAP PopupMenu_DrawText
void PopupMenu_DrawText(PopupMenu *_P32 p,int x,int y,int font,CString s)
{
    if(!text_enabled()) {legacy_PopupMenu_DrawText(p,x,y,font,s);return;}
    text_run((FontGlyphs *)(uintptr_t)(uint32_t)font,s.str,*(int *)(s.str-4),p->screen->layer[p->fc],x,y,x,y,
             SDL_min(240,p->left+p->itemW),SDL_min(320,y+p->itemH),-1);CString_Dtor(&s);
}
// 0001fe60 Menu_DrawText
// HD_WRAP Menu_DrawText
void Menu_DrawText(Menu *_P32 menu,uint x,uint y,int str)
{
    if(!text_enabled()) {legacy_Menu_DrawText(menu,x,y,str);return;}
    CString s;s.str=(wchar16 *_P32)(uintptr_t)(uint32_t)str;
    text_run((FontGlyphs *)(uintptr_t)(uint32_t)menu->font,s.str,*(int *)(s.str-4),menu->screen->layer[0],x&65535,y&65535,x&65535,y&65535,240,320,-1);
    CString_Dtor(&s);
}

// 000130d8 DrawLoadingProgress
void DrawLoadingProgress(char progress)
{
    // Resource loading finishes before input dispatch; no progress UI is needed.
    (void)progress;
}
