//Queue with linked list project

#include <stdio.h>
#include <stdbool.h>
#include  <stdlib.h>

typedef struct Node
{
    int value;
    struct Node * next;
}Node;
typedef struct 
{
    int size;
    Node *tail;
    Node *head;
}Queue;

Queue *func();
bool isempty(Queue *var);
void destroy(Queue *var);
int peek(Queue *var, int *status);
void enqueue(Queue *var, int value);
int dequeue(Queue *var, int *status);
int size(Queue *var);

int main(){

    Queue *m2 = func();
    
    if (isempty(m2)) printf("The queue is empty\n");
    enqueue(m2, 10);
    if (!(isempty(m2))) printf("Queue is not empty..\n");
    enqueue(m2, 11);

    enqueue(m2, 13);
    printf("The queue size: %d\n", m2->size);
    bool pek = false;
    int value = 0;
    value = peek(m2, &pek);
    printf("%d\n", value);
    int value1 = 0;
    value1 = dequeue(m2, &pek);
    printf("Dequeue: %d", value1);
    destroy(m2);

    return 0;
}

Queue *func(){
    Queue * n1 = malloc(sizeof(Queue));
    if (n1 == NULL) return NULL;
    n1->head = NULL;
    n1->tail = NULL;
    n1->size = 0;
    return n1;
}
bool isempty(Queue *var){
    return var->size == 0;
}
void destroy(Queue *var){
    Node *current = var->head;
    while(current != NULL){
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(var);
}
int peek(Queue *var, int *status){
    if (isempty(var)){
        *status = false;
        return 0;
    }
    *status = true;
    return var->head->value;
}
void enqueue(Queue *var, int value){
    Node *new = malloc(sizeof(Node));
    new->value = value;
    new->next = NULL;
    if (isempty(var)){
        var->head = new;
        var->tail = new;
    }else{
        var->tail->next = new;
        var->tail = new;

    }
    var->size++;

}
int dequeue(Queue *var, int *status){
    if (isempty(var)){
        *status = false;
    }
    *status = true;
    int value = var->head->value;
    Node *temp = var->head;
    if (var->size == 1){
        var->head = NULL;
        var->tail = NULL;
    } else {
        var->head = var->head->next;
    }
    free(temp);
    var->size--;
    return value;
}
int size(Queue *var){
    return var->size;
}
