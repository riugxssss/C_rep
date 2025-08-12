#include <stdio.h>
#include <stdlib.h>

typedef struct queue_t {
    int front;
    int rear;
    int sizearr;
    int arr[];
}queue_t;

queue_t *create_queue(int val){
    queue_t *ptr = malloc(sizeof(*ptr) + sizeof(int) * val);
    if (!ptr){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    ptr->front = -1;
    ptr->rear = -1;
    ptr->sizearr = val;
    return ptr;
}

int isempty(queue_t *ptr){
    return ptr->front == -1;
}
int isfull(queue_t *ptr){
    return ((ptr->rear + 1) % ptr->sizearr) == ptr->front;
}

void enqueue(queue_t *ptr, int val){
    if (isfull(ptr)){
        return;
    }else if(isempty(ptr)){
        ptr->front = ptr->rear = 0;
    }else {
        ptr->rear = (ptr->rear + 1) % ptr->sizearr;
    }
    ptr->arr[ptr->rear] = val;
}
void dequeue(queue_t *ptr){
    if (isempty(ptr)) {
        return;
    }else if (ptr->front == ptr->rear){
        ptr->front = ptr->rear = -1;
    }else {
        ptr->front = (ptr->front + 1) % ptr->sizearr;
    }
}

void print_queue(queue_t *ptr){
    if (isempty(ptr)){
        printf("<empty>\n");
        return;
    }

    int i = ptr->front;
    while (1){
        printf("%d ", ptr->arr[i]);
        if (i == ptr->rear) break;
        i = (i + 1) % ptr->sizearr;
    }

    putchar('\n');
}


int main(void){

    queue_t *arr = create_queue(4);
    enqueue(arr, 1);
    enqueue(arr, 4);
    enqueue(arr, 6);
    dequeue(arr);
    enqueue(arr, 5);
    enqueue(arr, 2);
    print_queue(arr);
    free(arr);

    return 0;
