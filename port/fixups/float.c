// Hand-written replacements for functions that use the COREDLL soft-float helpers (__utos, __muls, ...).
// Ghidra drops the helper arguments that are set up before a branch, and types floats inconsistently, so
// these are re-derived from the disassembly (tools/armdis.py <name>). Integer->float conversions are
// unsigned (__utos) where the original used them.
#include "fade.h"

static float bits2f(uint u) { float f; memcpy(&f, &u, 4); return f; }

// 00018aa4 Line_Init
void Line_Init(Line *_P32 this, int x1, int y1, int x2, int y2)
{
  if (x1 == x2) {
    this->vertical = 1;
    this->m = (float)(uint)x1;           // vertical line: m holds x
    this->b = this->m;
  } else {
    this->vertical = 0;
    float fy1 = (float)(uint)y1, fx1 = (float)(uint)x1;
    this->m = ((float)(uint)y2 - fy1) / ((float)(uint)x2 - fx1);
    this->b = fy1 - this->m * fx1;
  }
  this->horizontal = this->m == 0.0f;
}

// 00018bf8 Line_IsBelow
bool Line_IsBelow(Line *_P32 this, int x, int y)
{
  if (this->vertical) return false;
  return (float)(uint)y >= (float)(uint)x * this->m + this->b;
}

// 00018ca4 Line_IsAbove
bool Line_IsAbove(Line *_P32 this, int x, int y)
{
  if (this->vertical) return false;
  return (float)(uint)y <= (float)(uint)x * this->m + this->b;
}

// 00018d50 Line_IsLeftOf
bool Line_IsLeftOf(Line *_P32 this, int x, int y)
{
  if (this->horizontal) return false;
  if (this->vertical) return (float)(uint)x <= this->m;
  return (float)(uint)x <= ((float)(uint)y - this->b) / this->m;
}

// 00018e28 Line_IsRightOf
bool Line_IsRightOf(Line *_P32 this, int x, int y)
{
  if (this->horizontal) return false;
  if (this->vertical) return (float)(uint)x >= this->m;
  return (float)(uint)x >= ((float)(uint)y - this->b) / this->m;
}

// 0001bfd0 RandomRange
char RandomRange(char n)
{
  // (char)(rand() * n * 3.0518e-5f), re-drawn while it equals n
  char r;
  do {
    float f = (float)rand15() * (float)n;
    r = (char)(int)(f * bits2f(0x38000100));
  } while (r == n);
  return r;
}
