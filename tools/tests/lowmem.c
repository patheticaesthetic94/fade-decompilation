// Regression: reproduce a device with mappings in the old fixed heap/stack
// ranges, then ensure relocated reservations leave those mappings untouched.
#include "../../port/src/lowmem.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const size_t heap_size = 128u << 20, stack_size = 16u << 20;
    unsigned char *occupied = lowmem_try(0x00400000u, heap_size + stack_size);
    assert(occupied);
    occupied[0] = 0x5a;
    occupied[heap_size] = 0xa5;
    assert(!lowmem_try(0x00400000u, heap_size));
    assert(occupied[0] == 0x5a && occupied[heap_size] == 0xa5);
    unsigned char *heap = lowmem_find(heap_size);
    unsigned char *stack = lowmem_find(stack_size);
    assert(heap && stack);
    assert((uintptr_t)heap + heap_size <= 0x80000000u);
    assert((uintptr_t)stack + stack_size <= 0x80000000u);
    assert((uintptr_t)heap + heap_size <= (uintptr_t)stack ||
           (uintptr_t)stack + stack_size <= (uintptr_t)heap);
    memset(heap, 0x33, heap_size);
    memset(stack, 0x44, stack_size);
    assert(occupied[0] == 0x5a && occupied[heap_size] == 0xa5);
    assert(heap[0] == 0x33 && heap[heap_size - 1] == 0x33);
    assert(stack[0] == 0x44 && stack[stack_size - 1] == 0x44);
    printf("PASS: occupied=%p heap=%p stack=%p; existing mappings preserved\n",
           occupied, heap, stack);
    munmap(stack, stack_size);
    munmap(heap, heap_size);
    munmap(occupied, heap_size + stack_size);
    return 0;
}
