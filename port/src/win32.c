// Win32 window/message/timer API for the game's single window, plus sndPlaySoundW.
// SDL events become WM_* messages in a queue; GetMessageW/PeekMessageW drain it and fire timers;
// DispatchMessageW calls the game's WndProc (or a SetTimer callback) directly.
#include "port.h"

#define WM_TIMER 0x113
#define WM_QUIT 0x12

// ---- message queue --------------------------------------------------------------------------------
static MSG queue[256];
static int qhead, qlen;

void msg_post(uint32_t msg, uint32_t wp, uint32_t lp)
{
    if (qlen == 256) { port_log("message queue full, dropping %#x", msg); return; }
    MSG *m = &queue[(qhead + qlen++) % 256];
    memset(m, 0, sizeof *m);
    m->hwnd = FADE_HWND; m->message = msg; m->wParam = wp; m->lParam = lp; m->time = SDL_GetTicks();
    if (msg >= 0x200 && msg <= 0x202) { m->pt.x = lp & 0xffff; m->pt.y = lp >> 16; }
}

// first queued message in [lo, hi] (both 0 = any); -1 if none
static int msg_find(UINT lo, UINT hi)
{
    for (int i = 0; i < qlen; i++) {
        UINT m = queue[(qhead + i) % 256].message;
        if ((!lo && !hi) || (m >= lo && m <= hi)) return i;
    }
    return -1;
}

static void msg_take(int i, MSG *out)
{
    *out = queue[(qhead + i) % 256];
    for (int j = i; j > 0; j--) queue[(qhead + j) % 256] = queue[(qhead + j - 1) % 256];
    qhead = (qhead + 1) % 256;
    qlen--;
}

// ---- timers ---------------------------------------------------------------------------------------
static struct { UINT_PTR id; UINT ms; Uint32 due; TIMERPROC proc; int pending; } timers[8];

static void timers_fire(void)
{
    Uint32 now = SDL_GetTicks();
    for (int i = 0; i < 8; i++)
        if (timers[i].id && !timers[i].pending && (Sint32)(now - timers[i].due) >= 0) {
            timers[i].pending = 1;   // Win32 coalesces: one WM_TIMER until it is dispatched
            timers[i].due = now + timers[i].ms;
            msg_post(WM_TIMER, (uint32_t)timers[i].id, 0);
        }
}

int timers_next_ms(void)
{
    Uint32 now = SDL_GetTicks();
    int best = 50;
    for (int i = 0; i < 8; i++)
        if (timers[i].id && !timers[i].pending) best = SDL_min(best, SDL_max(0, (Sint32)(timers[i].due - now)));
    return best;
}

UINT_PTR SetTimer(HWND hwnd, UINT_PTR id, UINT ms, TIMERPROC proc)
{
    int i, free_ = -1;
    for (i = 0; i < 8 && timers[i].id != id; i++) if (!timers[i].id && free_ < 0) free_ = i;
    if (i == 8) i = free_;
    if (i < 0) return 0;
    timers[i].id = id; timers[i].ms = ms; timers[i].due = SDL_GetTicks() + ms; timers[i].proc = proc; timers[i].pending = 0;
    return id;
}

BOOL KillTimer(HWND hwnd, UINT_PTR id)
{
    for (int i = 0; i < 8; i++) if (timers[i].id == id) { timers[i].id = 0; return 1; }
    return 0;
}

// ---- message loop ---------------------------------------------------------------------------------
BOOL PeekMessageW(LPMSG msg, HWND hwnd, UINT lo, UINT hi, UINT remove)
{
    port_present(0);
    port_pump(0);
    timers_fire();
    int i = msg_find(lo, hi);
    if (i < 0) return 0;
    if (remove & 1) msg_take(i, msg);
    else *msg = queue[(qhead + i) % 256];
    return 1;
}

BOOL GetMessageW(LPMSG msg, HWND hwnd, UINT lo, UINT hi)
{
    for (;;) {
        port_present(0);
        timers_fire();
        int i = msg_find(lo, hi);
        if (i >= 0) { msg_take(i, msg); return msg->message != WM_QUIT; }
        port_pump(timers_next_ms());
    }
}

BOOL TranslateMessage(MSG *msg) { return 0; }

LRESULT DispatchMessageW(MSG *msg)
{
    if (msg->message == WM_TIMER)
        for (int i = 0; i < 8; i++)
            if (timers[i].id == msg->wParam) {
                timers[i].pending = 0;
                if (timers[i].proc) { timers[i].proc(msg->hwnd, WM_TIMER, msg->wParam, SDL_GetTicks()); return 0; }
            }
    LRESULT result = WndProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
    if (port_trace && (msg->message == 0x201 || msg->message == 0x202))
        port_log("tap %#x (%u,%u): game=%d menu=%d scene=%u", msg->message,
                 msg->lParam & 0xffff, (uint32_t)msg->lParam >> 16,
                 g_inGame, g_menu.active, ((GameState *)&g_gameState)->curScene);
    return result;
}

BOOL PostMessageW(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) { msg_post(msg, wp, (uint32_t)lp); return 1; }
LRESULT SendMessageW(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) { return WndProc(hwnd, msg, wp, lp); }
void PostQuitMessage(int code) { msg_post(WM_QUIT, (uint32_t)code, 0); }
LRESULT DefWindowProcW(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    // The game's Quit button sends WM_CLOSE and relies on the Win32 default
    // procedure to destroy the window and enter its WM_DESTROY cleanup path.
    if (msg == 0x10 /* WM_CLOSE */) msg_post(2 /* WM_DESTROY */, 0, 0);
    return 0;
}

void Sleep(DWORD ms)
{
    port_present(0);
    SDL_Delay(ms);
    port_pump(0);
}

// ---- window / GDI stubs ---------------------------------------------------------------------------
ATOM RegisterClassW(WNDCLASSW *wc) { return 1; }
HWND CreateWindowExW(DWORD ex, LPCWSTR cls, LPCWSTR title, DWORD style, int x, int y, int w, int h, HWND parent, HMENU menu, HINSTANCE inst, LPVOID param) { return FADE_HWND; }
HWND FindWindowW(LPCWSTR cls, LPCWSTR title) { return 0; }
HWND GetForegroundWindow(void) { return FADE_HWND; }
BOOL SetForegroundWindow(HWND hwnd) { return 1; }
BOOL ShowWindow(HWND hwnd, int cmd) { return 1; }
BOOL UpdateWindow(HWND hwnd) { return 1; }
int GetSystemMetrics(int i) { return i == 0 ? SCREEN_W : i == 1 ? SCREEN_H : 0; }
HDC BeginPaint(HWND hwnd, LPPAINTSTRUCT ps) { if (ps) memset(ps, 0, sizeof *ps); return (HDC)(uintptr_t)1; }
BOOL EndPaint(HWND hwnd, PAINTSTRUCT *ps) { return 1; }
HGDIOBJ GetStockObject(int i) { return (HGDIOBJ)(uintptr_t)1; }

int MessageBoxW(HWND hwnd, LPCWSTR text, LPCWSTR caption, UINT type)
{
    char *t = files_wide_to_utf8(text), *c = files_wide_to_utf8(caption);
    port_log("MessageBox [%s] %s", c, t);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, c, t, NULL);
    SDL_free(t); SDL_free(c);
    return 1;
}

// ---- sndPlaySoundW: one voice, like the real API ---------------------------------------------------
static SDL_AudioDeviceID audio_dev;
static SDL_AudioSpec audio_spec;
static uint8_t *snd_buf;
static Uint32 snd_len, snd_pos;
static int snd_loop;

static void audio_cb(void *ud, Uint8 *out, int len)
{
    memset(out, audio_spec.silence, len);
    while (len > 0 && snd_buf && snd_pos < snd_len) {
        int n = SDL_min((Uint32)len, snd_len - snd_pos);
        memcpy(out, snd_buf + snd_pos, n);
        out += n; len -= n; snd_pos += n;
        if (snd_pos >= snd_len && snd_loop) snd_pos = 0;
    }
}

static void audio_open(void)
{
    SDL_AudioSpec want = {0};
    // Preserve the bandwidth of the enhanced 48 kHz pack. Convert to the
    // obtained rate if the device requires a different output frequency.
    want.freq = 48000; want.format = AUDIO_S16SYS; want.channels = 2; want.samples = 1024; want.callback = audio_cb;
    audio_dev = SDL_OpenAudioDevice(NULL, 0, &want, &audio_spec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    if (audio_dev) {
        port_log("audio output: %d Hz, %d channels", audio_spec.freq, audio_spec.channels);
        SDL_PauseAudioDevice(audio_dev, 0);
    }
    else port_log("no audio: %s", SDL_GetError());
}

BOOL sndPlaySoundW(LPCWSTR name, UINT flags)
{
    if (!audio_dev) { audio_open(); if (!audio_dev) return 0; }
    SDL_LockAudioDevice(audio_dev);
    SDL_free(snd_buf); snd_buf = NULL; snd_len = snd_pos = 0;
    SDL_UnlockAudioDevice(audio_dev);
    if (!name) return 1;

    char *rel = files_game_rel(name);
    SDL_RWops *rw = files_open_asset(rel);
    SDL_AudioSpec spec; Uint8 *wav; Uint32 wlen;
    if (!rw || !SDL_LoadWAV_RW(rw, 1, &spec, &wav, &wlen)) { port_log("sndPlaySoundW: cannot load %s", rel); SDL_free(rel); return 0; }
    SDL_free(rel);
    SDL_AudioCVT cvt;
    SDL_BuildAudioCVT(&cvt, spec.format, spec.channels, spec.freq, audio_spec.format, audio_spec.channels, audio_spec.freq);
    cvt.len = (int)wlen;
    cvt.buf = SDL_malloc((size_t)wlen * (cvt.len_mult > 0 ? cvt.len_mult : 1));
    memcpy(cvt.buf, wav, wlen);
    SDL_FreeWAV(wav);
    if (cvt.needed) SDL_ConvertAudio(&cvt);
    else cvt.len_cvt = cvt.len;

    SDL_LockAudioDevice(audio_dev);
    snd_buf = cvt.buf; snd_len = (Uint32)cvt.len_cvt; snd_pos = 0; snd_loop = (flags & 8) != 0;   // SND_LOOP
    SDL_UnlockAudioDevice(audio_dev);
    if (!(flags & 1) && !snd_loop)   // synchronous unless SND_ASYNC
        while (snd_pos < snd_len) { port_present(0); SDL_Delay(10); }
    return 1;
}
