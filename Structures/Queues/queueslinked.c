#include <stdio.h>
#include <stdlib.h>

typedef struct nodes {
    struct nodes *next;
    int val;
}nodes;

typedef struct queues {
    struct nodes *front;
    struct nodes *rear;
}queues;

nodes *create_nodes(int data){
    nodes *newn = malloc(sizeof(*newn));
    if (!newn){
        fprintf(stderr, "[!] Alloc fail\n");
        exit(EXIT_FAILURE);
    }
    newn->val = data;
    newn->next = NULL;
    return newn;
}
queues *create_queue(){
    queues *newqueue = malloc(sizeof(*newqueue));
    if (!newqueue){
        fprintf(stderr, "[!] Alloc queue fail\n");
        exit(EXIT_FAILURE);
    }
    newqueue->front = newqueue->rear = NULL;
    return newqueue;
}
int isempty(queues *ptr){
    return ptr->front == NULL;
}

void enqueue(queues *ptr, int x){

    nodes *newn = create_nodes(x);
    if (isempty(ptr)){
        ptr->front = ptr->rear =newn;
    }
    ptr->rear->next = newn;
    ptr->rear = newn;

}

void dequeue(queues *ptr){
    if (isempty(ptr)) return;
    nodes *tmp = ptr->front;
    ptr->front = ptr->front->next;
    if (ptr->front == NULL){
        ptr->rear = NULL;
    }
    free(tmp);
}

void free_all(queues *ptr){
    nodes *tmp;
    while (ptr->front){
        tmp = ptr->front;
        ptr->front = ptr->front->next;
        free(tmp);
    }
    free(ptr);
}

void print_queue(queues *ptr){
    nodes *tmp = ptr->front;
    while (tmp){
        printf("%d ", tmp->val);
        tmp = tmp->next;
    }
    putchar('\n');
}

int main(void){

    queues *ptr = create_queue();
    enqueue(ptr, 5);
    enqueue(ptr, 1);
    enqueue(ptr, 4);
    print_queue(ptr);
    free_all(ptr);

    return 0;
