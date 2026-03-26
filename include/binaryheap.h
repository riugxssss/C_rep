

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

/*---- LIBRARIES ----*/
#include <stdint.h>

/*---- MACRO ----*/
#define ui32 uint32_t

/*I use 64 bytes the same as a cache line 
 * (It greatly help when you come around with THREADS systems due false sharing in MESI)*/
#define DEFAULT_SIZE 64

#define GET_LEFT(i)  (2 * (i) + 1)
#define GET_RIGHT(i) (2 * (i) + 2)
#define GET_SUPER(i) (((i) - 1) / 2)

#define I_SUCC 0xff
#define I_FAIL 0x00

#define R_SUCC 0x0f
#define R_FAIL 0xf0

/*---- STRUCTURE ----*/
typedef struct bh_struct bh_struct_t;

/*---- FUNCTIONS ----*/
bh_struct_t *create_bh();
int *bh_peek(bh_struct_t *bh);
int bh_insert(bh_struct_t *bh, int value);
void bh_print(bh_struct_t *bh);
int bh_remove(bh_struct_t *bh);
void bh_free(bh_struct_t *bh);
int is_min_heap(bh_struct_t *bh);

#endif /* - BINARYHEAP_H -*/
