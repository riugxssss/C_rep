#include <stdio.h>
#include <stdlib.h>

typedef struct stack_t {
    int val;
    struct stack_t *next;
}stack_t;

int isempty(stack_t *head){
    return head == NULL;
}

stack_t *create_node(int val){
    stack_t *newn = malloc(sizeof(*newn));
    if (!newn){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    newn->val = val;
    newn->next = NULL;
    return newn;
}

void push(stack_t **head, int v) {
    stack_t *newn = create_node(v);
    if (*head) newn->next = *head;
    *head = newn;
}

void pop(stack_t **head){
    if (isempty(*head)){
        fprintf(stderr, "[!] The stack is empty\n");
        return;
    }
    stack_t *tmp = *head;
    *head = (*head)->next;
    printf("Popped the value: %d\n", tmp->val);
    free(tmp);
}

void print_all(stack_t *head){
    if (!head) {
        putchar('\n');
        return;}
    printf("%d ", head->val);
    print_all(head->next);
}

void free_all(stack_t **head){
    while (*head){
        stack_t *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
    *head = NULL; //No dangling ptr
}

int main(void){

    stack_t *head = NULL;
    push(&head, 5);
    push(&head, 1);
    push(&head, 2);
    print_all(head);
    pop(&head);
    print_all(head);
    pop(&head);
    pop(&head);
    pop(&head);

    free_all(&head);


    return 0;
}
