#pragma once

//Main struct for the DLL
typedef struct double_l_list {
    struct node_infos *head;  
    struct node_infos *tail;  
    int n_nodes;
}double_l_list_t;

//Node struct with extra record (key)
typedef struct node_infos {
    int value;
    struct node_infos *prev;
    struct node_infos *next;
    int key;
}node_infos_t;

double_l_list_t *d_linkedlist_create();

node_infos_t *d_linkedlist_insert_node(double_l_list_t *headptr, int value, int key);

void d_linkedlist_remove_lru(double_l_list_t *headptr);

void d_linkedlist_print(double_l_list_t *headptr);

void d_linkedlist_free(double_l_list_t *headptr); 

int d_linkedlist_getLRU(double_l_list_t *headptr);

int d_linkedlist_getMRU(double_l_list_t *headptr);

void d_linkedlist_move_to_head(node_infos_t *NewMRU, double_l_list_t*headptr);

int d_linkedlist_getLRU_key(double_l_list_t *ptr);

