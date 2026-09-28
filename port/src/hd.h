#pragma once
#include "port.h"
#define HD_SCALE 4
void hd_init(void);
int hd_enabled(void);
const uint32_t *hd_frame(void);
void hd_register(uint16_t *low, int w, int h, const char *path);
void hd_font(FontGlyphs *font, const char *path, int keyed);
void hd_forget(void *low);
void hd_buffer(uint16_t *low, int w, int h);
void hd_fill(uint16_t *low, uint16_t color);
void hd_sync(uint16_t *low);
void hd_blit(uint16_t *dst, int x, int y, int w, int h, const uint16_t *src,
             int stride, int sx, int sy, int step, int keyed, const uint16_t *mask);
void hd_effect(uint16_t *src, uint16_t *dst, int mode);
void hd_alpha(uint16_t *dst, int x, int y, int w, int h, const uint8_t *alpha,
              uint32_t rgb, int left, int top, int right, int bottom);
