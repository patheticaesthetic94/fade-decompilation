#pragma once
#include "hd.h"
// Native state never enters the recovered ILP32 structures.
int text_enabled(void);
void text_init(void);
void text_load(FontGlyphs *font, const char *path);
float text_width(FontGlyphs *font, const wchar16 *s, int n);
int text_step(FontGlyphs *font);
void text_run(FontGlyphs *font, const wchar16 *s, int n, uint16_t *dst,
              int x, int y, int left, int top, int right, int bottom, int reveal);
int text_type_run(TextList *list, FontGlyphs *font, const wchar16 *s, int n,
                  int x, int y, int layer, int can_skip);
typedef struct TextParagraph {
    wchar16 *text;
    int length, indent, identity;
    FontGlyphs *font;
} TextParagraph;
typedef struct TextLine {
    int paragraph, start, length;
} TextLine;
typedef struct TextLayout {
    TextList *owner;
    TextParagraph *paragraphs;
    TextLine *lines;
    int paragraphs_n, lines_n, top, page, inventory;
    struct TextLayout *next;
} TextLayout;
TextLayout *text_layout(TextList *list);
void text_clear(TextList *list, int destroy);
void text_append(TextList *list, CString text, FontGlyphs *font, int indent, int identity);
void text_reflow(TextList *list);
int text_line_at(TextList *list, int y);
int text_identity(TextList *list, int line);
void text_draw(TextList *list, int layer, int animated, int can_skip);
