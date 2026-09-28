// Statically linked MFC-for-CE / CE CRT pieces that game code calls: CString (MFC memory layout), CTime,
// CPlex, operator new/free, rand, div, and the ARM division helpers. See port/include/rt.h.
#include "port.h"
#include <stdlib.h>
#include <time.h>

// ---- CString ------------------------------------------------------------------------------------
// MFC CStringData { long nRefs; int nDataLength; int nAllocLength; } followed by the wchar16 text;
// CString.str points at the text (game code reads the length at str-8). Copies are deep (MFC shares
// and copies on write, which is observably the same). The empty string is the image's afxEmptyString.
typedef struct { int32_t refs, len, alloc; } CSData;

static wchar16 *cs_empty(void) { return (wchar16 *)(uintptr_t)g_afxEmptyString; }
static CSData *cs_data(wchar16 *s) { return (CSData *)((uint8_t *)s - sizeof(CSData)); }
static int wlen16(const wchar16 *s) { int n = 0; if (s) while (s[n]) n++; return n; }

static wchar16 *cs_alloc(int n)
{
    if (n <= 0) return cs_empty();
    CSData *d = arena_alloc(sizeof(CSData) + (size_t)(n + 1) * 2);
    d->refs = 1; d->len = n; d->alloc = n;
    wchar16 *s = (wchar16 *)(d + 1);
    s[n] = 0;
    return s;
}

static void cs_free(wchar16 *s) { if (s && s != cs_empty()) arena_free(cs_data(s)); }

// this = a[0..na) + b[0..nb); a/b may alias this->str
static void cs_set2(CString *this, const wchar16 *a, int na, const wchar16 *b, int nb)
{
    wchar16 *s = cs_alloc(na + nb);
    if (na) memcpy(s, a, (size_t)na * 2);
    if (nb) memcpy(s + na, b, (size_t)nb * 2);
    wchar16 *old = this->str;
    this->str = s;
    cs_free(old);
}

static int cs_len(CString *s) { return s->str ? cs_data(s->str)->len : 0; }

// CE ANSI code page: Windows-1252
static const uint16_t cp1252[32] = {
    0x20ac, 0x81, 0x201a, 0x192, 0x201e, 0x2026, 0x2020, 0x2021, 0x2c6, 0x2030, 0x160, 0x2039, 0x152, 0x8d, 0x17d, 0x8f,
    0x90, 0x2018, 0x2019, 0x201c, 0x201d, 0x2022, 0x2013, 0x2014, 0x2dc, 0x2122, 0x161, 0x203a, 0x153, 0x9d, 0x17e, 0x178};
static wchar16 ansi2w(uint8_t c) { return c >= 0x80 && c < 0xa0 ? cp1252[c - 0x80] : c; }

static void cs_setA(CString *this, const char *a)
{
    int n = a ? (int)strlen(a) : 0;
    wchar16 *s = cs_alloc(n);
    for (int i = 0; i < n; i++) s[i] = ansi2w((uint8_t)a[i]);
    wchar16 *old = this->str;
    this->str = s;
    cs_free(old);
}

CString *CString_CtorW(CString *this, wchar16 *s) { this->str = cs_empty(); cs_set2(this, s, wlen16(s), 0, 0); return this; }
CString *CString_CtorA(CString *this, char *s) { this->str = cs_empty(); cs_setA(this, s); return this; }
int *CString_CopyCtor(CString *this, CString *src) { this->str = cs_empty(); cs_set2(this, src->str, cs_len(src), 0, 0); return (int *)this; }
void CString_Dtor(CString *this) { cs_free(this->str); this->str = cs_empty(); }
CString *CString_Assign(CString *this, CString *src) { if (this != src) cs_set2(this, src->str, cs_len(src), 0, 0); return this; }
CString *CString_AssignW(CString *this, wchar16 *s)
{
    cs_set2(this, s, wlen16(s), 0, 0);
    if (port_trace) { char *u = files_wide_to_utf8(s); port_log("AssignW '%s' len=%d", u, cs_len(this)); SDL_free(u); }
    return this;
}
undefined4 *CString_AssignA(CString *this, char *s) { cs_setA(this, s); return (undefined4 *)this; }
CString *CString_AssignChar(CString *this, wchar16 c) { cs_set2(this, &c, 1, 0, 0); return this; }
CString *CString_Plus(CString *res, CString *a, CString *b)
{
    res->str = cs_empty();
    cs_set2(res, a->str, cs_len(a), b->str, cs_len(b));
    if (port_trace) { char *u = files_wide_to_utf8(res->str); port_log("Plus %d+%d '%s'", cs_len(a), cs_len(b), u); SDL_free(u); }
    return res;
}
CString *CString_PlusChar(CString *res, CString *a, wchar16 c) { res->str = cs_empty(); cs_set2(res, a->str, cs_len(a), &c, 1); return res; }
CString *CString_Append(CString *this, CString *b) { cs_set2(this, this->str, cs_len(this), b->str, cs_len(b)); return this; }
CString *CString_AppendChar(CString *this, wchar16 c) { cs_set2(this, this->str, cs_len(this), &c, 1); return this; }

wchar16 *CString_GetBuffer(CString *this, int min)
{
    int n = cs_len(this);
    if (this->str == cs_empty() || cs_data(this->str)->alloc < min) {
        wchar16 *s = cs_alloc(min > n ? min : (n ? n : 1));
        memcpy(s, this->str, (size_t)n * 2);
        s[n] = 0;
        cs_data(s)->len = n;
        cs_free(this->str);
        this->str = s;
    }
    return this->str;
}

void CString_MakeUpper(CString *this)
{
    int n = cs_len(this);
    for (int i = 0; i < n; i++) {
        wchar16 c = this->str[i];
        if ((c >= 'a' && c <= 'z') || (c >= 0xe0 && c <= 0xfe && c != 0xf7)) this->str[i] = c - 0x20;
    }
}

void CString_SetAt(CString *this, int i, wchar16 c) { if (i >= 0 && i < cs_len(this)) this->str[i] = c; }

// ---- CTime / CPlex / CArchive ------------------------------------------------------------------
uint time32(int t) { (void)t; return (uint)time(NULL); }

undefined4 *CTime_GetCurrentTime(undefined4 *out) { *out = time32(0); return out; }

Tm *CTime_GetLocalTm(undefined4 ptime, undefined1 *unused)
{
    static Tm *tm;
    (void)unused;
    if (!tm) tm = arena_calloc(sizeof(Tm));
    time_t t = *(uint32_t *)(uintptr_t)ptime;
    struct tm lt;
    localtime_r(&t, &lt);
    tm->sec = lt.tm_sec; tm->min = lt.tm_min; tm->hour = lt.tm_hour; tm->mday = lt.tm_mday; tm->mon = lt.tm_mon;
    tm->year = lt.tm_year; tm->wday = lt.tm_wday; tm->yday = lt.tm_yday; tm->isdst = lt.tm_isdst;
    return tm;
}

// CPlex::Create(CPlex*& head, nMax, cbElement): block = { next; elements... }
int CPlex_Create(void *head, int nmax, int cb)
{
    uint32_t *slot = head;
    uint32_t *p = arena_alloc(4 + (size_t)nmax * cb);
    p[0] = *slot;
    *slot = (uint32_t)(uintptr_t)p;
    return (int)(uintptr_t)p;
}

void CPlex_FreeDataChain(void *p)
{
    while (p) { void *next = (void *)(uintptr_t)*(uint32_t *)p; arena_free(p); p = next; }
}

int CArchive_Read(CArchive *a, void *p, uint n) { port_log("CArchive_Read unsupported"); return 0; }
void CArchive_Write(CArchive *a, void *p, uint n) { port_log("CArchive_Write unsupported"); }
void CArchive_WriteCount(CArchive *a, uint n) { port_log("CArchive_WriteCount unsupported"); }
uint CArchive_ReadCount(CArchive *a) { port_log("CArchive_ReadCount unsupported"); return 0; }

// ---- CRT ----------------------------------------------------------------------------------------
void *operator_new(size_t n) { return arena_alloc(n ? n : 1); }
void game_free(void *p) { arena_free(p); }
undefined4 set_new_handler(void (*h)(void)) { (void)h; return 0; }

void crt_exit(int code)
{
    port_log("game exit(%d)", code);
    SDL_Quit();
    exit(code);
}

static uint32_t rand_seed = 1;
void srand15(uint s) { rand_seed = s; }
int rand15(void) { rand_seed = rand_seed * 214013u + 2531011u; return (rand_seed >> 16) & 0x7fff; }

gdiv_t *div32(gdiv_t *out, int n, int d) { out->quot = d ? n / d : 0; out->rem = d ? n % d : 0; return out; }

int wcscmp16(const wchar16 *a, const wchar16 *b)
{
    while (*a && *a == *b) a++, b++;
    return (int)*a - (int)*b;
}

// ARM runtime: __rt_sdiv(divisor, dividend) -> quotient
int __rt_sdiv_exref;
int __rt_sdiv(int d, int n) { return d ? n / d : 0; }
uint __rt_udiv(uint d, uint n) { return d ? n / d : 0; }
