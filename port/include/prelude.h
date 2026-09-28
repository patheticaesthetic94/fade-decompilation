// Ghidra builtin types for the generated game source (C, clang -fms-extensions).
// The port keeps the original ILP32 memory model: the image's data sections sit at their original
// addresses (0x10000+), the heap and the game thread's stack live in a low arena, and every pointer in
// game code and game data is a 32-bit `T *_P32` (clang __ptr32 __uptr: stored as 32 bits, zero-extended
// on use). So struct layouts, size constants, save files and the decompiler's (int)ptr casts all stay exact.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#ifdef __EMSCRIPTEN__
// wasm32 already uses the game's ILP32 pointer layout.
#define _P32
#else
#define _P32 __ptr32 __uptr
#endif

typedef uint8_t byte, uchar, undefined1, undefined;
typedef int8_t sbyte;
typedef uint16_t ushort, undefined2, wchar16, word;
typedef uint32_t uint, undefined4, dword, undefined3, uint3;
typedef int32_t int3;
typedef uint64_t undefined8, ulonglong;
typedef int64_t longlong;
typedef void code(void *);   // native function pointer (vector ctor/dtor iterators)

#define CONCAT31(hi, lo) ((uint32_t)(hi) << 8 | (uint8_t)(lo))
#define CONCAT11(hi, lo) ((uint16_t)((uint8_t)(hi) << 8 | (uint8_t)(lo)))
#define CONCAT22(hi, lo) ((uint32_t)(uint16_t)(hi) << 16 | (uint16_t)(lo))
// Ghidra partial access x._off_size_
#define PART(x, off, T) (*(T *)((char *)&(x) + (off)))
#define PART3(x, off) ((*(uint32_t *)((char *)&(x) + (off) - 1)) >> 8)
