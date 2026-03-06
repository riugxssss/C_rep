#ifndef MY_MALLOC_H
#define MY_MALLOC_H
#include <stddef.h>

//Macro alignment
#define ALIGNMENT 0x8
//EXAMPLE: size = 13. 13 + 7= 20 & 11111000 => 20 in bit 00010100 & 11111000 = 16

#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(0x7))
//BIT PACKING
#define ISFREE(p) ((p)->size & 0x1)
#define GET_SIZE(p) ((p)->size & ~0x7)  
#define PACK(size, alloc) ((size) | (alloc))

//overhead size
#define BLOCK_SIZE sizeof(block_t)

//Utils
#define $i (int *)
#define $c (char *)
#define $b (block_t *)
#define $bt block_t

#define hidden __attribute__((visibility("hidden")))

//Struct without free flag (1 free | 0 alloc) i used the PACK macro to set 1 or 0
typedef struct blockstruct {
    struct blockstruct *prev;
    struct blockstruct *next;
    size_t size;
}block_t;

    
    void *my_malloc(size_t size);
    void my_free(void *ptr);
    

#endif
