#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "binaryheap.h"

typedef struct bh_struct {
    
    /*The implementation will use a 
     * binary heap as a dynamic array with a DEFAULT size setted
     * view the bh_h to modify it (if you need to test)*/
    int *binheap;

    /*Total of the node currently used not the max capacity [!]*/
    ui32 tot_nodes;
    
}bh_struct_t;

bh_struct_t *create_bh(){

    bh_struct_t *bhsrt = malloc(sizeof(*bhsrt));
    if (bhsrt == NULL){
        perror("Error ");
        abort(); //Send SIGABRT to the process, the OS will handle it
    }

    bhsrt->binheap = malloc(sizeof(int) * DEFAULT_SIZE);
    if (bhsrt->binheap == NULL){
        perror("Error ");
        abort();
    }

    //Init active nodes
    bhsrt->tot_nodes = 0;

    return bhsrt;
}

int *bh_peek(bh_struct_t *bh){
    if (bh == NULL)
        return NULL;
    if (bh->tot_nodes == 0 || bh->binheap == NULL)
        return NULL;
    
    return &bh->binheap[0]; //We return the root of our Binary Heap
}

//Numbers swap (Simple function)

static void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//For debug we make the function type int 

int bh_insert(bh_struct_t *bh, int value){
    if (bh == NULL) return I_FAIL;

    /* First case of inserting in Binary Heap */   
    

    if (bh->tot_nodes == 0){
        bh->binheap[0] = value;
        bh->tot_nodes++;
        return I_SUCC;
    }

    //If tot_node not 0 insert at the value of tot_node
    bh->binheap[bh->tot_nodes] = value;
    bh->tot_nodes++;
    


    int tmptot = bh->tot_nodes - 1;

    int idx = GET_SUPER(tmptot);

    if (bh->binheap[idx] <= value){
        return I_SUCC;
    }

    do {
    
        idx = GET_SUPER(tmptot);

        if (bh->binheap[idx] <= bh->binheap[tmptot]){
            break;
        }else {
            swap(&bh->binheap[idx], &bh->binheap[tmptot]);

        }
    
        tmptot = idx;

    }while (tmptot != 0);

    return I_SUCC;
}

void bh_print(bh_struct_t *bh){
    if (bh == NULL)
        return;
    if (bh->binheap == NULL)
        return;


    printf("START OF THE BINARY HEAP\n");
    
    for (int i = 0; i < bh->tot_nodes;i++){
        printf("[%d] %d\n", i , bh->binheap[i]);
    }
    
}

void bh_free(bh_struct_t *bh){
    if (bh == NULL) return;

    free(bh->binheap);
    bh->tot_nodes = 0;
    free(bh);
    return;
}

//Remove doing bubble-down starting from the root

int bh_remove(bh_struct_t *bh){
    if (bh == NULL || bh->tot_nodes == 0){
        return R_FAIL;
    }

    bh->binheap[0] = bh->binheap[bh->tot_nodes - 1];
    bh->tot_nodes--;

    int idx = 0;

    int left;
    int right;
    int smallest;

    while (1){
        left =  GET_LEFT(idx);
        right = GET_RIGHT(idx);
        smallest = idx;


        if (left < bh->tot_nodes && bh->binheap[left] < bh->binheap[smallest]){
            smallest = left;
        }
        if (right < bh->tot_nodes && bh->binheap[right] < bh->binheap[smallest]){
            smallest = right;
        }

        if (smallest == idx) break;

        swap(&bh->binheap[idx], &bh->binheap[smallest]);

        idx = smallest;
    }


    return R_SUCC;
}

int is_min_heap(bh_struct_t *bh) {
    if (!bh || bh->tot_nodes == 0) return 1;

    for (int i = 0; i < bh->tot_nodes; i++) {
        int left = GET_LEFT(i);
        int right = GET_RIGHT(i);

        if (left < bh->tot_nodes && bh->binheap[i] > bh->binheap[left])
            return 0;
        if (right < bh->tot_nodes && bh->binheap[i] > bh->binheap[right])
            return 0;
    }
    return 1;
}
