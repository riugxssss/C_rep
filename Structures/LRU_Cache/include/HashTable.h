#pragma once
#include "double_linked_list.h"


//Slots informations
typedef struct slot_info {
    int key;
    node_infos_t *address;
    int status: 2;
}slot_info_t;

//Hash table informations
typedef struct hash_table{
    int UsedSlot;
    int MaxSlot; 
    struct slot_info **associativearr;
} hash_table_t;

hash_table_t *hash_table_create(int MaxSlot);

void hash_table_delete(hash_table_t *ptr, int key);

void hash_table_insert(hash_table_t *ptr, int key, node_infos_t *NewMRU);

void hash_table_free(hash_table_t *ptr);

node_infos_t *hash_table_search(int key, hash_table_t *ptr);

float hash_table_load_factor(int n, int m);

