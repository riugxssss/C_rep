#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "double_linked_list.h"
#include "HandlingUtils.h"
#include "HashTable.h"

typedef struct lru_cache {
    int capacity;
    double_l_list_t *Dll;
    hash_table_t *Ht;
}lru_cache_t;

lru_cache_t *lru_cache_create(int capacity){
    lru_cache_t *newcache = malloc(sizeof(*newcache));
    if (!newcache){
        error_handler(ENOMEM);
    }
    newcache->capacity = capacity;
    newcache->Dll = d_linkedlist_create();
    newcache->Ht = hash_table_create(capacity + 50);
    return newcache;
}
int lru_cache_get(int key, lru_cache_t *ptr){
    node_infos_t *retval = hash_table_search(key, ptr->Ht);
    int ValueRet = 0;
    if (retval){
        ValueRet = retval->value;
        d_linkedlist_move_to_head(retval, ptr->Dll);
        return ValueRet;
    }else {
        printf("The value searched does not exist.");
        return -1;
    }
}
void lru_cache_put(int key, int value, lru_cache_t *ptr){
    if (!ptr) return;
    node_infos_t *RetSearch = hash_table_search(key, ptr->Ht);
    if (RetSearch){
        RetSearch->value = value;
        hash_table_insert(ptr->Ht, key, RetSearch); //Handler for common keys
        d_linkedlist_move_to_head(RetSearch, ptr->Dll);
    }else {
        hash_table_insert(ptr->Ht, key, d_linkedlist_insert_node(ptr->Dll, value, key));
    }
}
void lru_cache_clear(lru_cache_t *ptr){
    if (!ptr) return;
    hash_table_free(ptr->Ht);
    d_linkedlist_free(ptr->Dll);
    free(ptr);
}
void lru_cache_print(lru_cache_t *ptr){
    d_linkedlist_print(ptr->Dll);
}

void lru_cache_remove_LRU(lru_cache_t *ptr){
    if (!ptr) return;
    d_linkedlist_remove_lru(ptr->Dll);
    hash_table_delete(ptr->Ht, d_linkedlist_getLRU_key(ptr->Dll));
}

void lru_cache_make_logs(lru_cache_t *ptr){
    int LRU = d_linkedlist_getLRU(ptr->Dll);
    int MRU = d_linkedlist_getMRU(ptr->Dll);
    logging_function(MRU, LRU);
}
