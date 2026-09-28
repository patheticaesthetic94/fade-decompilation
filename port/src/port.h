// Internal interface of the platform layer (port/src). Game code only sees port/include/.
#pragma once
#include "fade.h"
#include <SDL.h>

// arena.c
void arena_init(void);
void arena_load_image(const uint8_t *pe, size_t len);
void *arena_alloc(size_t n);
void *arena_calloc(size_t n);
void arena_free(void *p);
size_t arena_size(void *p);
void *arena_stack(size_t size);

// gen/funcs.c: every game function by original address
typedef struct { uint32_t addr; void (*fn)(void); } GameFunc;
extern const GameFunc game_funcs[];
extern const int game_nfuncs;
void (*game_func_at(uint32_t addr))(void);

// main.c
void port_fatal(const char *fmt, ...);
extern int port_trace;             // verbose API logging: FADE_TRACE=1, or on Android: adb shell setprop debug.fade.trace 1
#define port_log(...) SDL_Log(__VA_ARGS__)
void port_present(int force);
extern uint16_t *port_fb;          // 240x320 RGB565 GAPI framebuffer (arena)
void port_pump(int wait_ms);       // SDL events -> Win32 message queue
void port_delay(uint32_t ms);      // cooperative browser wait, SDL delay natively

// win32.c
void msg_post(uint32_t msg, uint32_t wp, uint32_t lp);
int timers_next_ms(void);

// files.c
void files_init(void);
SDL_RWops *files_open_asset(const char *rel);   // case-insensitive lookup of a game data file
char *files_wide_to_utf8(const wchar16 *w);
char *files_game_rel(const wchar16 *path);  // game path -> lowercase data-relative path (SDL_free it)

#define FADE_HWND ((HWND)(uintptr_t)0x100)
#define SCREEN_W 240
#define SCREEN_H 320
