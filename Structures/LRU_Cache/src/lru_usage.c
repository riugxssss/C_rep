#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "double_linked_list.h"
#include "HandlingUtils.h"
#include "HashTable.h"

// LRU cache structure
typedef struct lru_cache {
    int capacity;                   // Maximum number of items
    double_l_list_t *list;          // Doubly linked list
    hash_table_t *table;            // Hash table for fast access
} lru_cache_t;

/*Create function where takes a capacity from the inpu
and allocate dinamically the mem for our 'cache' after it check if malloc returned
a NULL ptr (ENOMEM)

Allocate memory for the 2 structure
cache->list = create
cache->table = create*/
lru_cache_t *lru_cache_create(int capacity){
    lru_cache_t *cache = malloc(sizeof(*cache));
    if (!cache){
        error_handler(ENOMEM);
    }

    cache->capacity = capacity;
    cache->list = d_linkedlist_create();
    cache->table = hash_table_create(capacity + 50);

    return cache;
}

/*The get function call an internal hash table function
called search that saerch if the value with (entered by the user)
key exist, it return the address node if it was in the hash table
altough it returns NULL

search - return node - check NULL

if the node exist the node get to the head of the Double linked list
Example with 3 node:

3 - 5 - 7 => in this moment the LRU is the 7 and the MRU is the 3.
if we use get function to access a value to read, that node of the value
become MRU

get(7)

7 - 3 - 5 => MRU is 7 and the LRU is 5
*/
int lru_cache_get(int key, lru_cache_t *cache){
    node_infos_t *node = hash_table_search(key, cache->table);
    int value = 0;

    if (node){
        value = node->value;
        d_linkedlist_move_to_head(node, cache->list);
        return value;
    } else {
        printf("The value searched does not exist.\n");
        return -1;
    }
}

/*The put function can create and modify value
we use search function  (esplicative function that can be found in HashTable.c)
If the node exist we modify his value -> existing_node->value = value from param
and update the Double LL, updating the MRU and LRU
If the node does not exist the function insert the node at MRU and
create a slot in the hash table*/
void lru_cache_put(int key, int value, lru_cache_t *cache){
    if (!cache) return;

    node_infos_t *existing_node = hash_table_search(key, cache->table);
    if (existing_node){
        existing_node->value = value;
        d_linkedlist_move_to_head(existing_node, cache->list);
    } else {
        node_infos_t *new_node = d_linkedlist_insert_node(cache->list, value, key);
        hash_table_insert(cache->table, key, new_node);
    }
}

/*Free all the data structures allocated before with create*/
void lru_cache_clear(lru_cache_t *cache){
    if (!cache) return;

    hash_table_free(cache->table);
    d_linkedlist_free(cache->list);
    free(cache);
}

// Print the LRU cache
void lru_cache_print(lru_cache_t *cache){
    if (!cache) return;

    d_linkedlist_print(cache->list);
}

/*The function remove the LRU getting the key of it
and removing it from dlinkedlist and hashtable*/
void lru_cache_remove_LRU(lru_cache_t *cache){
    if (!cache) return;

    int lru_key = d_linkedlist_getLRU_key(cache->list);
    d_linkedlist_remove_lru(cache->list);
    hash_table_delete(cache->table, lru_key);
}

/*A function that get the MRU and LRU and insert the param of the logging function*/
void lru_cache_make_logs(lru_cache_t *cache){
    if (!cache) return;

    int lru_value = d_linkedlist_getLRU(cache->list);
    int mru_value = d_linkedlist_getMRU(cache->list);

    logging_function(mru_value, lru_value);
}
