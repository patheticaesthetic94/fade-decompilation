// Reserve low addresses without replacing Android/JVM mappings. The original
// image needs an exact address; heap and stack can occupy any free low range.
#pragma once
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/mman.h>

static void *lowmem_try(uintptr_t addr, size_t size)
{
    int flags = MAP_PRIVATE | MAP_ANONYMOUS;
#ifdef __linux__
    // Older kernels may ignore this flag and treat addr as a hint. Always
    // validate the return value, and release any unwanted mapping.
#ifndef MAP_FIXED_NOREPLACE
#define MAP_FIXED_NOREPLACE 0x100000
#endif
    flags |= MAP_FIXED_NOREPLACE;
#endif
    void *p = mmap((void *)addr, size, PROT_READ | PROT_WRITE, flags, -1, 0);
    if (p == MAP_FAILED) return NULL;
    if (p != (void *)addr) {
        munmap(p, size);
        errno = EEXIST;
        return NULL;
    }
    return p;
}

static void *lowmem_find(size_t size)
{
    // Stay below 2 GB: recovered code sometimes converts pointers to signed
    // ints. 16 MB steps are aligned for both 4 KB and 16 KB Android pages.
    const uintptr_t first = 0x00400000u, limit = 0x80000000u;
    if (!size || size > limit - first) { errno = ENOMEM; return NULL; }
    for (uintptr_t addr = first; addr <= limit - size; addr += 0x01000000u) {
        void *p = lowmem_try(addr, size);
        if (p) return p;
    }
    return NULL;
}
