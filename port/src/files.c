// Win32 file and registry API on top of SDL.
// Game paths look like "\Program Files\fade\menu\CSRXMRYI.IFJ": the install-dir prefix is dropped and the
// rest is looked up case-insensitively in the packaged data (fade/files.txt lists it). Data files are
// opened as private in-memory copies (LoadImageFile un-XORs image headers in place and writes them
// back); files under save/ live in SDL_GetPrefPath() and persist.
#include "port.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#define DATA_DIR "fade/"
#define INVALID_HANDLE 0xffffffffu

static char *pref_dir;
static struct { char *lower, *real; } *index_;
static int nindex;

static char *lower_dup(const char *s) { char *d = SDL_strdup(s); for (char *p = d; *p; p++) *p = (char)SDL_tolower(*p); return d; }

static int idx_cmp(const void *a, const void *b) { return strcmp(*(char *const *)a, *(char *const *)b); }

void files_init(void)
{
#ifdef __EMSCRIPTEN__
    // Mounted and restored from IndexedDB by the site's preRun hook.
    pref_dir = SDL_strdup("/saves/");
#else
    pref_dir = SDL_GetPrefPath("FadeTeam", "Fade");
#endif
    if (!pref_dir) pref_dir = SDL_strdup("./");
    size_t len;
    char *list = SDL_LoadFile(DATA_DIR "files.txt", &len);
    if (!list) port_fatal("missing game data (" DATA_DIR "files.txt): %s", SDL_GetError());
    for (size_t i = 0; i < len; i++) if (list[i] == '\n') nindex++;
    index_ = SDL_calloc(nindex + 1, sizeof *index_);
    nindex = 0;
    for (char *line = strtok(list, "\r\n"); line; line = strtok(NULL, "\r\n")) {
        index_[nindex].real = SDL_strdup(line);
        index_[nindex].lower = lower_dup(line);
        nindex++;
    }
    SDL_free(list);
    qsort(index_, nindex, sizeof *index_, idx_cmp);
    port_log("data: %d files, saves in %s", nindex, pref_dir);
}

char *files_wide_to_utf8(const wchar16 *w)
{
    int n = 0;
    while (w && w[n]) n++;
    char *s = SDL_malloc((size_t)n * 3 + 1), *o = s;
    for (int i = 0; i < n; i++) {
        unsigned c = w[i];
        if (c < 0x80) *o++ = (char)c;
        else if (c < 0x800) { *o++ = (char)(0xc0 | c >> 6); *o++ = (char)(0x80 | (c & 0x3f)); }
        else { *o++ = (char)(0xe0 | c >> 12); *o++ = (char)(0x80 | (c >> 6 & 0x3f)); *o++ = (char)(0x80 | (c & 0x3f)); }
    }
    *o = 0;
    return s;
}

// "\Program Files\fade\Menu\x.IFJ" -> "menu/x.ifj" (lowercase, relative)
char *files_game_rel(const wchar16 *path)
{
    char *s = files_wide_to_utf8(path);
    for (char *p = s; *p; p++) *p = *p == '\\' ? '/' : (char)SDL_tolower(*p);
    static const char *prefix = "program files/fade/";
    char *r = s;
    while (*r == '/') r++;
    if (!strncmp(r, prefix, strlen(prefix))) r += strlen(prefix);
    while (*r == '/') r++;
    char *out = SDL_strdup(r);
    SDL_free(s);
    return out;
}

// the exe's asset-name mangling (MangleAssetPath), for callers that pass plain names
static void mangle(char *rel)
{
    char *base = strrchr(rel, '/');
    base = base ? base + 1 : rel;
    char *dot = strrchr(base, '.');
    for (char *p = base + 1; *p && p != dot; p++)
        if (*p >= 'a' && *p <= 'z') *p = (char)('a' + (*p - 'a' + 4) % 26);
    static const char *ext[][2] = {{".jpg", ".ifj"}, {".bmp", ".ifb"}, {".wav", ".ifv"}, {".gif", ".ifg"}};
    for (int i = 0; dot && i < 4; i++)
        if (!strcmp(dot, ext[i][0])) strcpy(dot, ext[i][1]);
}

static const char *find_data(const char *lower)
{
    int lo = 0, hi = nindex - 1;
    while (lo <= hi) {
        int m = (lo + hi) / 2, c = strcmp(lower, index_[m].lower);
        if (!c) return index_[m].real;
        if (c < 0) hi = m - 1; else lo = m + 1;
    }
    return NULL;
}

SDL_RWops *files_open_asset(const char *rel_lower)
{
    const char *real = find_data(rel_lower);
    char tmp[512];
    if (!real) {
        SDL_strlcpy(tmp, rel_lower, sizeof tmp - 4);
        mangle(tmp);
        real = find_data(tmp);
    }
    if (!real) return NULL;
    char full[600];
    SDL_snprintf(full, sizeof full, DATA_DIR "%s", real);
    return SDL_RWFromFile(full, "rb");
}

// ---- handles -------------------------------------------------------------------------------------
typedef struct {
    int used;
    uint8_t *mem; size_t size, pos;   // in-memory data file
    FILE *fp;                          // save file
} FileH;
static FileH fh[64];

static HANDLE to_handle(int i) { return (HANDLE)(uintptr_t)(0x1000 + i); }
static FileH *from_handle(HANDLE h)
{
    uint32_t v = (uint32_t)(uintptr_t)h;
    return v >= 0x1000 && v < 0x1000 + 64 && fh[v - 0x1000].used ? &fh[v - 0x1000] : NULL;
}

static void save_path(char *out, size_t n, const char *rel) { SDL_snprintf(out, n, "%s%s", pref_dir, rel); }

static void mkdirs_for(char *path)
{
    for (char *p = path + strlen(pref_dir); *p; p++)
        if (*p == '/') { *p = 0; mkdir(path, 0755); *p = '/'; }
}

HANDLE CreateFileW(LPCWSTR name, DWORD access, DWORD share, LPSECURITY_ATTRIBUTES sa, DWORD disp, DWORD flags, HANDLE tmpl)
{
    char *rel = files_game_rel(name);
    if (port_trace) { char *u = files_wide_to_utf8(name); port_log("CreateFileW %s -> %s", u, rel); SDL_free(u);
        char hx[400] = ""; for (int k = 0; k < 40 && k * 5 < 390; k++) SDL_snprintf(hx + strlen(hx), 8, "%04x ", name[k]); port_log("  %s", hx); }
    int i;
    for (i = 0; i < 64 && fh[i].used; i++) ;
    if (i == 64) port_fatal("CreateFileW: too many open files");
    FileH *f = &fh[i];
    memset(f, 0, sizeof *f);
    char sp[700];
    save_path(sp, sizeof sp, rel);
    int is_save = !strncmp(rel, "save/", 5);
    if (is_save || disp != 3 /* OPEN_EXISTING */) {
        struct stat st;
        int exists = stat(sp, &st) == 0;
        const char *mode = NULL;
        switch (disp) {
        case 1: mode = exists ? NULL : "w+b"; break;             // CREATE_NEW
        case 2: mode = "w+b"; break;                             // CREATE_ALWAYS
        case 3: mode = exists ? "r+b" : NULL; break;             // OPEN_EXISTING
        case 4: mode = exists ? "r+b" : "w+b"; break;            // OPEN_ALWAYS
        case 5: mode = exists ? "w+b" : NULL; break;             // TRUNCATE_EXISTING
        }
        if (mode) { mkdirs_for(sp); f->fp = fopen(sp, mode); }
        if (!f->fp) { SDL_free(rel); return (HANDLE)(uintptr_t)INVALID_HANDLE; }
    } else {
        SDL_RWops *rw = files_open_asset(rel);
        if (!rw) { port_log("CreateFileW: not found: %s", rel); SDL_free(rel); return (HANDLE)(uintptr_t)INVALID_HANDLE; }
        f->mem = SDL_LoadFile_RW(rw, &f->size, 1);
    }
    SDL_free(rel);
    f->used = 1;
    return to_handle(i);
}

BOOL ReadFile(HANDLE h, LPVOID buf, DWORD n, DWORD *nread, LPOVERLAPPED ov)
{
    FileH *f = from_handle(h);
    if (!f) return 0;
    size_t got;
    if (f->fp) got = fread(buf, 1, n, f->fp);
    else { got = f->pos < f->size ? SDL_min(n, f->size - f->pos) : 0; memcpy(buf, f->mem + f->pos, got); f->pos += got; }
    if (nread) *nread = (DWORD)got;
    return 1;
}

BOOL WriteFile(HANDLE h, LPCVOID buf, DWORD n, DWORD *nwritten, LPOVERLAPPED ov)
{
    FileH *f = from_handle(h);
    if (!f) return 0;
    size_t put = n;
    if (f->fp) put = fwrite(buf, 1, n, f->fp);
    else {
        if (f->pos + n > f->size) { f->mem = SDL_realloc(f->mem, f->pos + n); f->size = f->pos + n; }
        memcpy(f->mem + f->pos, buf, n); f->pos += n;
    }
    if (nwritten) *nwritten = (DWORD)put;
    return 1;
}

DWORD SetFilePointer(HANDLE h, LONG dist, LONG *high, DWORD method)
{
    FileH *f = from_handle(h);
    if (!f) return 0xffffffffu;
    if (f->fp) { fseek(f->fp, dist, method == 0 ? SEEK_SET : method == 1 ? SEEK_CUR : SEEK_END); return (DWORD)ftell(f->fp); }
    long base = method == 0 ? 0 : method == 1 ? (long)f->pos : (long)f->size;
    f->pos = (size_t)SDL_max(0, base + dist);
    return (DWORD)f->pos;
}

BOOL CloseHandle(HANDLE h)
{
    FileH *f = from_handle(h);
    if (!f) return 0;
    if (f->fp) fclose(f->fp);
    SDL_free(f->mem);
    memset(f, 0, sizeof *f);
    return 1;
}

BOOL DeleteFileW(LPCWSTR name)
{
    char *rel = files_game_rel(name), sp[700];
    save_path(sp, sizeof sp, rel);
    SDL_free(rel);
    return remove(sp) == 0;
}

BOOL CreateDirectoryW(LPCWSTR name, LPSECURITY_ATTRIBUTES sa)
{
    char *rel = files_game_rel(name), sp[700];
    save_path(sp, sizeof sp, rel);
    SDL_free(rel);
    return mkdir(sp, 0755) == 0 || errno == EEXIST;
}

// ---- registry: HKCU\SOFTWARE\Fade DWORD values, persisted as name=value lines ------------------
static struct { char name[32]; uint32_t val; } reg[16];
static int nreg;

static void reg_load(void)
{
    static int loaded;
    if (loaded++) return;
    char p[700];
    SDL_snprintf(p, sizeof p, "%sregistry.txt", pref_dir);
    FILE *fp = fopen(p, "r");
    if (!fp) return;
    while (nreg < 16 && fscanf(fp, "%31[^=]=%u\n", reg[nreg].name, &reg[nreg].val) == 2) nreg++;
    fclose(fp);
}

static void reg_save(void)
{
    char p[700];
    SDL_snprintf(p, sizeof p, "%sregistry.txt", pref_dir);
    FILE *fp = fopen(p, "w");
    if (!fp) return;
    for (int i = 0; i < nreg; i++) fprintf(fp, "%s=%u\n", reg[i].name, reg[i].val);
    fclose(fp);
}

LSTATUS RegOpenKeyExW(HKEY key, LPCWSTR sub, DWORD opt, REGSAM sam, PHKEY out) { reg_load(); *out = (HKEY)(uintptr_t)0x200; return 0; }
LSTATUS RegCloseKey(HKEY key) { return 0; }

LSTATUS RegQueryValueExW(HKEY key, LPCWSTR name, DWORD *res, DWORD *type, BYTE *data, DWORD *cb)
{
    char *n = files_wide_to_utf8(name);
    // Startup's recovered code checks RegCloseKey's result after this query.
    // Supply a valid Install_Dir rather than leaving its heap buffer uninitialized.
    if (!strcmp(n, "Install_Dir")) {
        static const wchar16 install_dir[] = {
            '\\', 'P', 'r', 'o', 'g', 'r', 'a', 'm', ' ', 'F', 'i', 'l', 'e', 's',
            '\\', 'f', 'a', 'd', 'e', 0
        };
        SDL_free(n);
        if (type) *type = 1;   // REG_SZ
        if (!cb) return 87;    // ERROR_INVALID_PARAMETER
        DWORD capacity = *cb;
        *cb = sizeof install_dir;
        if (data && capacity < sizeof install_dir) return 234; // ERROR_MORE_DATA
        if (data) memcpy(data, install_dir, sizeof install_dir);
        return 0;
    }
    for (int i = 0; i < nreg; i++)
        if (!strcmp(reg[i].name, n)) {
            SDL_free(n);
            if (type) *type = 4;   // REG_DWORD
            if (data && cb && *cb >= 4) memcpy(data, &reg[i].val, 4);
            if (cb) *cb = 4;
            return 0;
        }
    SDL_free(n);
    return 2;   // ERROR_FILE_NOT_FOUND
}

LSTATUS RegSetValueExW(HKEY key, LPCWSTR name, DWORD res, DWORD type, BYTE *data, DWORD cb)
{
    char *n = files_wide_to_utf8(name);
    int i;
    for (i = 0; i < nreg && strcmp(reg[i].name, n); i++) ;
    if (i == nreg && nreg < 16) SDL_strlcpy(reg[nreg++].name, n, sizeof reg[0].name);
    SDL_free(n);
    if (i < 16) { reg[i].val = 0; memcpy(&reg[i].val, data, SDL_min(cb, 4u)); reg_save(); }
    return 0;
}
