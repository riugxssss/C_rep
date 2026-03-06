#include <stdio.h>
#include <string.h>
#include "my_malloc.h"

int main() {
    char *p1 = (char *)my_malloc(20);
    char *p2 = (char *)my_malloc(30);
    char *p3 = (char *)my_malloc(40);

    if (!p1 || !p2 || !p3) {
        printf("Failed allocation\n");
        return 1;
    }

    strcpy(p1, "bloc1");
    strcpy(p2, "bloc2");
    strcpy(p3, "bloc3");

    my_free(p2);
    my_free(p3);

    my_free(p1);

    printf("Free success, coalescing executed.\n");

    return 0;
}
