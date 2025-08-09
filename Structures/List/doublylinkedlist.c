#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
}Node;

static Node *create_node(int val){
    Node *newn = malloc(sizeof(*newn));
     if (!newn) {
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    newn->prev = newn->next = NULL;
    newn->value = val;
    return newn;
}

void insert_at_head(Node **root, int val){
    Node *newn = create_node(val);
    if (*root){
        (*root)->prev = newn;
        newn->next = *root;
    }
    *root = newn;
}

void print_list_reverse(Node *head) {
    while (head->next) {
        head = head->next;
    }
    while (head) {
        printf("%d ", head->value);
        head = head->prev;
    }
    putchar('\n');
}

void print_recursive(Node *root){
    if (!root) {
        putchar('\n');
        return;
    }
    printf("%d ", root->value);
    print_recursive(root->next);
}

void print_iterative(Node *root){
    while (root){
        printf("%d ", root->value);
        root = root->next;
    }
    putchar('\n');
}

void insert_at_tail(Node **root, int val){
    Node *newn = create_node(val);
    
    if (!*root){
        *root = newn;
        return;
    }

    Node *tmp = *root;
    while (tmp->next){
        tmp = tmp->next; //end of list
    }

    tmp->next = newn;
    newn->prev = tmp;
}

void free_list(Node **root){
    Node *tmp;
    while (*root){
        tmp = *root;
        *root = (*root)->next;
        free(tmp);
    }
    *root = NULL;
}

int main(void){

    Node *root = NULL;
    insert_at_head(&root, 5);
    insert_at_head(&root, 7);
    insert_at_head(&root, 8);
    print_list_reverse(root);
    print_iterative(root);
    insert_at_tail(&root, 10);
    print_recursive(root);
    free_list(&root);


    return 0;
}
