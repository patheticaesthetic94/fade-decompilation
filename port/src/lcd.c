// Optional Pocket PC screen simulation. Models a 2001-era 3.8" 240x320 transflective
// TFT (about 105 ppi, 65,536 colours): the frame is reduced to the panel's 240x320
// RGB565 grid, then drawn at 4x with vertical RGB stripes and the black matrix between
// cells. Transflective panels had a narrow gamut, raised blacks, a cool front light that
// lit the glass unevenly from one edge, and slow liquid-crystal response (smearing).
#include "port.h"
#include "hd.h"
#include <math.h>

#define LW SCREEN_W
#define LH SCREEN_H
#define OW (LW * 4)
#define OH (LH * 4)

static uint16_t state[LW * LH * 3];   // displayed panel value per channel, 8.8 fixed point
static uint32_t *out;
static int primed, settling;
static Uint32 last_ms;
static uint8_t tone[3][256];          // panel response per channel, after desaturation
static uint8_t cell[16][3][256];      // subpixel mask x front-light-independent gain
static uint16_t light[LW * LH];       // front-light falloff, 8.8 fixed point

static void tables(void)
{
    // Black level and white point of a front-lit transflective panel (slightly cool).
    static const float black[3] = {20, 23, 26}, white[3] = {222, 233, 238};
    for (int c = 0; c < 3; c++)
        for (int v = 0; v < 256; v++)
            tone[c][v] = (uint8_t)(black[c] + (white[c] - black[c]) * powf(v / 255.f, 1.12f) + .5f);
    // 4x4 output cell: R, G, B stripes then the column gap; the bottom row is the row gap.
    static const float col[4][3] = {{1, .52f, .5f}, {.5f, 1, .5f}, {.5f, .52f, 1}, {.58f, .6f, .6f}};
    static const float row[4] = {1, 1, 1, .7f};
    const float gain = 1.42f;
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            for (int c = 0; c < 3; c++)
                for (int v = 0; v < 256; v++) {
                    float o = v * col[x][c] * row[y] * gain;
                    cell[y * 4 + x][c][v] = (uint8_t)(o > 255 ? 255 : o + .5f);
                }
    // The front light enters from the top edge and fades towards the bottom and sides.
    for (int y = 0; y < LH; y++)
        for (int x = 0; x < LW; x++) {
            float dx = (x + .5f) / LW * 2 - 1, dy = (y + .5f) / LH;
            float f = (1.05f - .1f * dy) * (1 - .06f * dx * dx) * (1 - .05f * dy * dy * dy);
            light[y * LW + x] = (uint16_t)(f * 256 + .5f);
        }
}

void lcd_reset(void) { primed = 0; }
int lcd_settling(void) { return settling; }

const uint32_t *lcd_render(void)
{
    if (!out) { out = SDL_malloc(OW * OH * 4); tables(); }
    const uint32_t *hd = hd_enabled() ? hd_frame() : NULL;
    // Liquid crystal response: about 35 ms to settle most of the way between frames.
    Uint32 now = SDL_GetTicks();
    float dt = primed ? (float)(now - last_ms) : 1000.f;
    last_ms = now;
    int keep = (int)(expf(-dt / 35.f) * 256);
    settling = 0;
    for (int y = 0; y < LH; y++)
        for (int x = 0; x < LW; x++) {
            int rgb[3];
            if (hd) {
                // Average the 4x4 HD block onto one panel pixel.
                int s[3] = {0, 0, 0};
                for (int j = 0; j < 4; j++) {
                    const uint32_t *p = hd + (y * 4 + j) * OW + x * 4;
                    for (int i = 0; i < 4; i++) { s[0] += p[i] >> 16 & 255; s[1] += p[i] >> 8 & 255; s[2] += p[i] & 255; }
                }
                for (int c = 0; c < 3; c++) rgb[c] = s[c] >> 4;
            } else {
                uint16_t p = port_fb[y * LW + x];
                rgb[0] = (p >> 11) << 3; rgb[1] = (p >> 5 & 63) << 2; rgb[2] = (p & 31) << 3;
            }
            // 16-bit panel depth, then a narrower gamut (about 78% saturation).
            rgb[0] = (rgb[0] & ~7) | rgb[0] >> 5; rgb[1] = (rgb[1] & ~3) | rgb[1] >> 6; rgb[2] = (rgb[2] & ~7) | rgb[2] >> 5;
            int lum = (77 * rgb[0] + 150 * rgb[1] + 29 * rgb[2]) >> 8;
            uint16_t *st = &state[(y * LW + x) * 3];
            int lit = light[y * LW + x], v[3];
            for (int c = 0; c < 3; c++) {
                int target = (lum + ((rgb[c] - lum) * 200 >> 8)) << 8;
                int cur = primed ? st[c] : target;
                cur = target + (((cur - target) * keep) >> 8);
                if (cur - target > 96 || target - cur > 96) settling = 1;
                else cur = target;
                st[c] = (uint16_t)cur;
                int t = tone[c][cur >> 8] * lit >> 8;
                v[c] = t > 255 ? 255 : t;
            }
            uint32_t *o = out + y * 4 * OW + x * 4;
            for (int j = 0; j < 4; j++)
                for (int i = 0; i < 4; i++) {
                    uint8_t (*m)[256] = cell[j * 4 + i];
                    o[j * OW + i] = 0xff000000u | (uint32_t)m[0][v[0]] << 16 | (uint32_t)m[1][v[1]] << 8 | m[2][v[2]];
                }
        }
    primed = 1;
    return out;
}
