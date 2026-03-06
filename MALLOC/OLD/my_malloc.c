#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"
#include <unistd.h>
#include <string.h>

//free list ptr to NULL (no blocks)
$bt *free_list = NULL;

//b = start of the block + tot size of the block (end of the block now) - overhead => result: start of the boundary tags(footer)
hidden $bt *get_footer($bt *b){
    return $b ($c b + GET_SIZE(b) - BLOCK_SIZE);
}

//using sbrk (syscall that expand the heap moving the program break limit of the heap) the kernel will do the work for us
//we set the new block to free and his pointers to NULL and we put it in the free list
hidden $bt *request_space(size_t size){
    void *space_ptr = sbrk(size);
    if (space_ptr == (void*) -1) return NULL;
    $bt *b = $b space_ptr;
    b->size = PACK(size, 1); 
    b->prev = b->next = NULL;
    $bt *bf = get_footer(b);
    bf->size = b->size;

    if (!free_list) free_list = b;
    return b;
}

//first fit search (find the first block that satisfy the request)
hidden $bt *first_fit(size_t size){
    $bt *curr = free_list;
    while (curr){
        if (ISFREE(curr) && GET_SIZE(curr) >= size) return curr; 
        curr = curr->next;
    }
    return NULL;
}

//best fit search (find the smallest block that satisfy the size request)
hidden $bt *best_fit(size_t size){
    $bt *curr = free_list;
    $bt *best = NULL;
    while (curr){
        if (ISFREE(curr) && GET_SIZE(curr) >= size){
            if (!best || GET_SIZE(curr) < GET_SIZE(best)){
                best = curr;
            }
        }
        curr = curr->next;
    }
    return best;
}

//worst fit search (find the largest block in the free list this strategy is used to reduce the small block (extern fragmentation))
hidden $bt *worst_fit(size_t size){
    $bt *curr = free_list;
    $bt *worst = NULL;
    while(curr){
        if (ISFREE(curr) && GET_SIZE(curr) > size){
            if (!worst || GET_SIZE(curr) >= GET_SIZE(worst)){
                worst = curr;
            }
        }
        curr = curr->next;
    }
    return worst;
}

//this function split the block b is the allocated block size is the actually user request the remain is the result of the split
//if he have enough bytes in memory we can use that and build up a new block for allocation
hidden void split_block($bt *b, size_t size){
    size_t bsize = GET_SIZE(b);
    size_t remain = bsize - size;
    if (remain < BLOCK_SIZE + ALIGNMENT) return;

    $bt *newb = $b ($c b + remain);
    newb->size = PACK(remain, 1); 
    $bt *newf = get_footer(newb);
    newf->size = newb->size;

    b->size = PACK(size, 0); //Redimension of the block with the exact size request
    $bt *bf = get_footer(b);
    bf->size = b->size;

    newb->next = b->next;
    if (newb->next) newb->next->prev = newb;
    newb->prev = b;
    b->next = newb;
}

//malloc allocation func using the first_fit strategy
void *my_malloc(size_t size){
    if (!size) return NULL;

    size_t tot_size = ALIGN(size) + BLOCK_SIZE;
    $bt *b = first_fit(tot_size);
    if (!b){
        b = request_space(tot_size);
        if (!b) return NULL;
    } else {
        //if we found the block we split it to have the exact size for allocated block and save e reutilize the memory
        b->size = PACK(GET_SIZE(b), 0);
        split_block(b, tot_size);
    }
    if (!free_list) free_list = b;

    return $c b + BLOCK_SIZE;
}

//coalescing is a process that we can use to increment the current block with a union between the next or prev block (or both)
hidden $bt *coalescing($bt *b){
    //next
    $bt *next = $b ($c b + GET_SIZE(b));
    if ((void*)next < sbrk(0) && ISFREE(next)){
        b->size = PACK(GET_SIZE(b) + GET_SIZE(next), 1);
        $bt *bf = get_footer(b);
        bf->size = b->size;

        b->next = next->next;
        if (next->next) next->next->prev = b;
    }

    //prev
    $bt *prev_footer = $b ($c b - BLOCK_SIZE);
    if ((void*)prev_footer > (void*)free_list && ISFREE(prev_footer)){
        $bt *prev = $b ($c b - GET_SIZE(prev_footer));
        prev->size = PACK(GET_SIZE(prev) + GET_SIZE(b), 1);
        $bt *bf = get_footer(prev);
        bf->size = prev->size;

        prev->next = b->next;
        if (b->next) b->next->prev = prev; //update b => prev
        b = prev; //reupdate b with prev
    }
    return b;
}

//free func 
void my_free(void *ptr){
    if (!ptr) return;
    //ptr used by malloc so he punct to the start of the payload, - BLOCK_SIZE he punct to the start of the block
    $bt *b = $b ($c ptr - BLOCK_SIZE);
    b->size = PACK(GET_SIZE(b), 1); 
    $bt *bf = get_footer(b);
    bf->size = b->size;

    $bt *merged = coalescing(b);
    if (!merged->prev) free_list = merged; //if prevptr = NULL <> merged block => update free_list > merged first block in the free_list
}

//by riugxs
