#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "HandlingUtils.h"

typedef struct node_infos {
    int value;
    struct node_infos *prev;
    struct node_infos *next;
    int key;
}node_infos_t;

typedef struct double_l_list {
    struct node_infos *head;  
    struct node_infos *tail;  
    int nNodes;
}double_l_list_t;

double_l_list_t *d_linkedlist_create(){
    double_l_list_t *rethead = malloc(sizeof(*rethead));
    if (rethead == NULL){
        error_handler(ENOMEM);
    }
    rethead->head = NULL;
    rethead->tail = NULL;
    rethead->nNodes = 0;
    return rethead;
}
static node_infos_t *d_linked_list_create_node(int EnteredValue, int key){
    node_infos_t *newnode = malloc(sizeof(*newnode));
    if (!newnode){
        error_handler(ENOMEM);
    }
    newnode->value = EnteredValue;
    newnode->prev = newnode->next = NULL;
    newnode->key = key;
    return newnode;
}
node_infos_t *d_linkedlist_insert_node(double_l_list_t *headptr, int value, int key){
    node_infos_t *newn = d_linked_list_create_node(value, key);
    if (headptr->head){
        headptr->head->prev = newn;
        newn->next = headptr->head;
    }else {
        headptr->tail = newn;
    }
    headptr->head = newn;
    headptr->nNodes++;
    return newn;
}
void d_linkedlist_remove_lru(double_l_list_t *headptr){
    if (headptr->head == NULL) return;
    node_infos_t *tmp = headptr->head;
    if (headptr->nNodes == 1){
        free(tmp);
        headptr->head = headptr->tail = NULL;
    }
    node_infos_t *tmp2 = headptr->tail;
    tmp2->prev->next = NULL;
    free(tmp2);
}
void d_linkedlist_free(double_l_list_t *headptr){
    if (!headptr->head) return;
    node_infos_t *tmp;
    while (headptr->head){
        tmp = headptr->head;
        headptr->head = headptr->head->next;
        free(tmp);
    }
}
int d_linkedlist_getLRU(double_l_list_t *headptr){
    if (!headptr) return -1;
    if (!headptr->tail) return -1;
    return headptr->tail->value;
}
int d_linkedlist_getMRU(double_l_list_t *headptr){
    if (!headptr) return -1;
    if (!headptr->head) return -1;
    return headptr->head->value;
}


void d_linkedlist_move_to_head(node_infos_t *NewMRU, double_l_list_t*headptr){
    if (!headptr || !NewMRU) return;
    if (headptr->head == NewMRU){
        return;
    }
    
    if (headptr->nNodes == 1){
        return;
    }

    //If its not head node
    if (NewMRU->prev){
        NewMRU->prev->next = NewMRU->next;
    }
    //If its not tail
    if (NewMRU->next){
        NewMRU->next->prev = NewMRU->prev;
    //If it is
    }else {
        headptr->tail = NewMRU->prev;
    }

    NewMRU->prev = NULL;
    NewMRU->next = headptr->head;
    headptr->head->prev = NewMRU;
    headptr->head = NewMRU;
    if (!headptr->tail)
            headptr->tail = NewMRU;

}
void d_linkedlist_print(double_l_list_t *headptr){
    printf("PRINTING CACHE\n");
    printf("MRU: %d\nLRU: %d\n", d_linkedlist_getMRU(headptr), d_linkedlist_getLRU(headptr));
    node_infos_t *curr = headptr->head;
    while (curr){
        printf("(key: %d | value: %d)\n", curr->key, curr->value);
        curr = curr->next;
    }
    putchar('\n');
}

int d_linkedlist_getLRU_key(double_l_list_t *ptr){
    return ptr->tail->key;
}
