#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stackutils.h"

/*Function that alloc a pointer to the struct and for the stack (dynamic array)
with proper container size (arraysize = containersize) and elementsize how many.*/
$sp AllocDyn($i containersize){
    $sp ptrstruct = malloc(sizeof(*ptrstruct));
    if (!ptrstruct){
        fprintf(stderr, "[!] Failed malloc\n");
        exit(EXIT_FAILURE);
    }
    ptrstruct->elementsize = 0;
    if (containersize < 1){
        ptrstruct->container = DEFAULTSIZE; //Default size
        ptrstruct->block = malloc(sizeof(int) * DEFAULTSIZE);
    }else {
    ptrstruct->container = containersize;
    ptrstruct->block = malloc(sizeof(int) * containersize);
    }

    return ptrstruct;
}


hidden bool empty($sp ptrstruct){
    if (ptrstruct->elementsize == 0) return true;
    return false;
}   

hidden bool full($sp ptrstruct){
    if (ptrstruct->elementsize == ptrstruct->container) return true;
    return false;
}

void freeall($sp ptrstruct){
    free(ptrstruct->block);
    free(ptrstruct);
}
$i push($sp ptrstruct, $i n){
    if (full(ptrstruct)){ //if full we realloc to another block larger
        dam(ptrstruct, EXPANDSIZE);
    }
    ptrstruct->block[ptrstruct->elementsize++] = n;
    return n;
}

$i pop($sp ptrstruct, $i n){
    if (empty(ptrstruct)) return EMPTY;
    n = ptrstruct->block[--ptrstruct->elementsize];
    //return the popped number
    return n;
}

void peekall($sp ptrstruct){
    if (empty(ptrstruct)) return;
    for ($i i = 0;i<ptrstruct->elementsize;i++){
        printf("%d ", ptrstruct->block[i]); //print all the number in the array
    }
    putchar('\n');
}

void dam($sp ptrstruct, $i expand){
    if (expand <= 0){
        return;
    }
    $i new_container = ptrstruct->container + expand;
    $i *new_block = realloc(ptrstruct->block, sizeof($i) * new_container); //new block 
    if (!new_block){ //if fail, we have the old size with the old ptr
        fprintf(stderr, "[!] Failed malloc\n");
        exit(EXIT_FAILURE);
    }
    ptrstruct->block = new_block; //update the ptr
    ptrstruct->container = new_container; //update the container size
}

