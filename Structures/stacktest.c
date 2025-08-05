#include <stdio.h>
#include "stackutils.h"

int main() {
    stack_t *s = AllocDyn(3);
    push(s, 10);
    push(s, 20);
    push(s, 30);
    push(s, 40);  
    peek(s);      

    printf("Pop: %d\n", pop(s, 0));
    peekall(s);

    freeall(s);
    return 0;
}
