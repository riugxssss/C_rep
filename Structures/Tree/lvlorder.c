#include <stdio.h>
#include <stdlib.h>

//Tree nodes
typedef struct nodest {
    int data;
    struct nodest *left;
    struct nodest *right;
}nodest;

//Tree struct
typedef struct tree {
    int totnodes;
    struct nodest *root;
}tree;

//Queue Nodes
typedef struct nodesq {
    nodest *node;
    struct nodesq *next;
}nodesq;

//Queue struct
typedef struct queue {
    struct nodesq *front;
    struct nodesq *rear;    
}queue;


int isempty(queue *ptr){
    return ptr->front == NULL;
}

nodesq *create_node(nodest *ptrt){
    nodesq *ptr = malloc(sizeof(*ptr));
    if (!ptr){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    ptr->node = ptrt;
    ptr->next = NULL;
    return ptr;
}
tree *create_tree(){
    tree *ptr = malloc(sizeof(*ptr));
    if (!ptr){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    ptr->root = NULL;
    ptr->totnodes = 0;
    return ptr;
}
nodest *create_nodet(int val){
    nodest *newn = malloc(sizeof(*newn));
    if (!newn){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    newn->left = newn->right = NULL;
    newn->data = val;
    return newn;
}

void insertT(tree *ptr, int val){
    if (!ptr->root){
        ptr->root = create_nodet(val);
        ptr->totnodes++;
        return;
    }
    nodest *curr = ptr->root;
    while (1){
        if (curr->data > val){
            if (!curr->left){
                curr->left = create_nodet(val);
                ptr->totnodes++;
                break;
            }
            curr = curr->left;
        }else if (curr->data < val){
            if (!curr->right){
                curr->right = create_nodet(val);
                ptr->totnodes++;
                break;
            }
            curr = curr->right;
        }else {
            break;
        }
    }
}
void free_tree(nodest *ptr){
    if (!ptr){
        return;
    }
    free_tree(ptr->left);
    free_tree(ptr->right);
    free(ptr);
}
queue *create_queue(){
    queue *ptr = malloc(sizeof(*ptr));
    if (!ptr){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    ptr->front = ptr->rear = NULL;
    return ptr;
}
void enqueue(queue *ptr, nodest *t){
    nodesq *newn = create_node(t);
    if (isempty(ptr)){
        ptr->front = ptr->rear = newn;
        return;
    }
    ptr->rear->next = newn;
    ptr->rear = newn;
}
nodest *dequeue(queue *ptr){
    if (isempty(ptr)){
        return NULL;
    }
    nodesq *tmp = ptr->front;
    ptr->front = ptr->front->next;
    nodest *res = tmp->node;
    free(tmp);
    return res;
}
void free_queue(queue *ptr){
    while (ptr->front){
        nodesq *tmp = ptr->front;
        ptr->front = ptr->front->next;
        free(tmp);
    }
    free(ptr);
}
void level_order(tree *ptrt){
    if (!ptrt || !ptrt->root) return;
    queue *ptrq = create_queue();
    enqueue(ptrq, ptrt->root);
    while (!isempty(ptrq)){
        nodest *curr = dequeue(ptrq);
        printf("%d\n", curr->data);
        if (curr->left) enqueue(ptrq, curr->left);
        if (curr->right) enqueue(ptrq, curr->right);
    }
    free_queue(ptrq);
}

int main(void){

    tree *t = create_tree();
    insertT(t, 4);
    insertT(t, 1);
    insertT(t, 5);
    insertT(t, 7);
    insertT(t, 3);
    level_order(t);
    free_tree(t->root);
    free(t);
    return 0;
}
