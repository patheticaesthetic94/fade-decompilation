// Low-memory arena: the original image at its link address, a heap and the game thread's stack, all
// below 4 GB so that the game's 32-bit pointers (clang __ptr32) and (int)ptr casts stay valid.
#include "port.h"
#include "hd.h"
#include "lowmem.h"
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGE_BASE 0x10000u
#define HEAP_SIZE  0x08000000u   // 128 MB

static void *map_at(uintptr_t addr, size_t size)
{
    void *p = lowmem_try(addr, size);
    if (!p) port_fatal("arena: cannot map image (%#zx bytes at %#lx): %s",
                       size, (unsigned long)addr, strerror(errno));
    return p;
}

static void *map_low(size_t size, const char *name)
{
    void *p = lowmem_find(size);
    if (!p) port_fatal("arena: cannot reserve %s (%#zx bytes below 2 GB): %s",
                       name, size, strerror(errno));
    port_log("arena: %s at %p (%#zx bytes)", name, p, size);
    return p;
}

// ---- image ---------------------------------------------------------------------------------------
// Map SizeOfImage at the image base and copy every section's raw data (only .rdata/.data matter: the
// code is native now, but keeping .text too costs nothing and keeps any stray address valid).
void arena_load_image(const uint8_t *pe, size_t len)
{
    uint32_t e = *(uint32_t *)(pe + 0x3c);
    if (len < e + 0xf8 || memcmp(pe + e, "PE\0\0", 4)) port_fatal("Fade.exe: not a PE file");
    uint16_t nsec = *(uint16_t *)(pe + e + 6);
    uint16_t optsz = *(uint16_t *)(pe + e + 0x14);
    uint32_t base = *(uint32_t *)(pe + e + 0x18 + 0x1c);
    uint32_t size = *(uint32_t *)(pe + e + 0x18 + 0x38);
    if (base != IMAGE_BASE) port_fatal("Fade.exe: unexpected image base %#x", base);
    uint8_t *img = map_at(base, (size + 0xffff) & ~0xffffu);
    const uint8_t *sh = pe + e + 0x18 + optsz;
    for (int i = 0; i < nsec; i++, sh += 40) {
        uint32_t va = *(uint32_t *)(sh + 12), raw = *(uint32_t *)(sh + 16), off = *(uint32_t *)(sh + 20);
        if (raw && off + raw <= len) memcpy(img + va, pe + off, raw);
    }
}

// ---- heap: boundary-tag first-fit allocator with coalescing -------------------------------------
// Block: [u32 size|used] payload [u32 size|used]; sizes include both tags, 8-aligned.
typedef struct FreeBlk { uint32_t tag; struct FreeBlk *_P32 next, *_P32 prev; } FreeBlk;
static uint8_t *heap_lo, *heap_hi;
static FreeBlk *free_head;
static SDL_mutex *heap_lock;

#define TAG(p) (*(uint32_t *)(p))
#define SIZE(t) ((t) & ~7u)
#define FOOT(b) ((uint32_t *)((uint8_t *)(b) + SIZE(TAG(b)) - 4))

static void fl_insert(FreeBlk *b) { b->prev = 0; b->next = free_head; if (free_head) free_head->prev = b; free_head = b; }
static void fl_remove(FreeBlk *b)
{
    if (b->prev) b->prev->next = b->next; else free_head = b->next;
    if (b->next) b->next->prev = b->prev;
}
static void set_tags(void *b, uint32_t size, int used) { TAG(b) = size | used; *FOOT(b) = size | used; }

static void heap_init(void)
{
    heap_lo = map_low(HEAP_SIZE, "heap");
    heap_hi = heap_lo + HEAP_SIZE;
    // sentinels: a used 8-byte block at each end so coalescing never walks off the heap
    set_tags(heap_lo, 8, 1);
    set_tags(heap_hi - 8, 8, 1);
    FreeBlk *b = (FreeBlk *)(heap_lo + 8);
    set_tags(b, HEAP_SIZE - 16, 0);
    fl_insert(b);
    heap_lock = SDL_CreateMutex();
}

void *arena_alloc(size_t n)
{
    uint32_t need = (uint32_t)((n + 8 + 7) & ~7u);
    if (need < sizeof(FreeBlk) + 4) need = (sizeof(FreeBlk) + 4 + 7) & ~7u;
    SDL_LockMutex(heap_lock);
    for (FreeBlk *b = free_head; b; b = b->next) {
        uint32_t sz = SIZE(b->tag);
        if (sz < need) continue;
        fl_remove(b);
        if (sz - need >= 32) {   // split, keep the tail free
            FreeBlk *r = (FreeBlk *)((uint8_t *)b + need);
            set_tags(r, sz - need, 0);
            fl_insert(r);
            sz = need;
        }
        set_tags(b, sz, 1);
        SDL_UnlockMutex(heap_lock);
        return (uint8_t *)b + 4;
    }
    SDL_UnlockMutex(heap_lock);
    port_fatal("arena: out of memory (%zu bytes)", n);
    return NULL;
}

void *arena_calloc(size_t n) { void *p = arena_alloc(n); memset(p, 0, n); return p; }

void arena_free(void *p)
{
    if (!p) return;
    uint8_t *b = (uint8_t *)p - 4;
    if ((uint8_t *)p < heap_lo || (uint8_t *)p >= heap_hi) return;   // image data (e.g. empty CString)
    hd_forget(p);
    SDL_LockMutex(heap_lock);
    uint32_t sz = SIZE(TAG(b));
    uint32_t prev = *(uint32_t *)(b - 4);
    if (!(prev & 1)) { b -= SIZE(prev); fl_remove((FreeBlk *)b); sz += SIZE(prev); }
    uint8_t *nx = b + sz;
    if (!(TAG(nx) & 1)) { fl_remove((FreeBlk *)nx); sz += SIZE(TAG(nx)); }
    set_tags(b, sz, 0);
    fl_insert((FreeBlk *)b);
    SDL_UnlockMutex(heap_lock);
}

size_t arena_size(void *p) { return SIZE(TAG((uint8_t *)p - 4)) - 8; }

void *arena_stack(size_t size)
{
    return map_low(size, "stack");
}

void arena_init(void) { heap_init(); }
