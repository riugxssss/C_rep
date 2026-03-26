#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "binaryheap.h"

int main() {
    bh_struct_t *heap = create_bh();
    if (!heap) {
        fprintf(stderr, "Failed to create heap\n");
        return 1;
    }

    const int N = 25; 
    srand((unsigned int)time(NULL));

    printf("---- Stress test: insert ----\n");
    for (int i = 0; i < N; i++) {
        int val = rand() % 1000;
        if (bh_insert(heap, val) != I_SUCC) {
            fprintf(stderr, "Insert failed for value %d\n", val);
            bh_free(heap);
            return 1;
        }
        if (!is_min_heap(heap)) {
            printf("Heap invalid after inserting %d\n", val);
            bh_print(heap);
            bh_free(heap);
            return 1;
        }
    }

    printf("All inserts maintained min-heap property.\n");

    printf("\n---- Stress test: remove ----\n");
    int *root;
    while ((root = bh_peek(heap)) != NULL) {
        printf("Removing root: %d\n", *root);
        if (bh_remove(heap) != R_SUCC) {
            fprintf(stderr, "Remove failed\n");
            bh_free(heap);
            return 1;
        }
        if (!is_min_heap(heap)) {
            printf("Heap invalid after removal\n");
            bh_print(heap);
            bh_free(heap);
            return 1;
        }
    }

    printf("All removals maintained min-heap property.\n");

    bh_free(heap);
    printf("\nStress test completed successfully!\n");
    return 0;
}
