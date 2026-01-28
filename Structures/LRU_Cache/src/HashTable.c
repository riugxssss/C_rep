#include <stdio.h>
#include <stdlib.h>
#include "double_linked_list.h"
#include "HandlingUtils.h"
#include <errno.h>

#define INITVAR 0
#define OCCUPED 1
#define DELETED 2

typedef struct slot_info {
    int status:3;
    int key;
    node_infos_t *address;
}slot_info_t;

typedef struct hash_table{
    int MaxSlot; 
    struct slot_info **associativearr;
} hash_table_t;

hash_table_t *hash_table_create(int MaxSlot){
    hash_table_t *ptr = malloc(sizeof(*ptr));
    if (!ptr){
        error_handler(ENOMEM);
    }
    ptr->MaxSlot = MaxSlot;
    ptr->associativearr = calloc(MaxSlot, sizeof(slot_info_t *));
    if (ptr->associativearr == NULL){
        free(ptr);
        error_handler(ENOMEM);
    }
    return ptr;
}
static slot_info_t *hash_table_create_bucket(int key, node_infos_t *address){
    slot_info_t *ptr = malloc(sizeof(*ptr));
    if (!ptr){
        error_handler(ENOMEM);
    }
    ptr->address = address;
    ptr->key = key;
    ptr->status = OCCUPED;
    return ptr;
}
static inline int hash_table_hash_function(int key, int MaxSlots){
    return key % MaxSlots;
}
static inline int hash_table_linear_probing(int key, int i, hash_table_t *ptr){
    return(hash_table_hash_function(key, ptr->MaxSlot) + i) % ptr->MaxSlot;
}
void hash_table_delete(hash_table_t *ptr, int key){
    int i = INITVAR;
    int idx = INITVAR;
    while (i < ptr->MaxSlot){
        idx = hash_table_linear_probing(key, i , ptr);
        if (ptr->associativearr[idx]->key == key){
            ptr->associativearr[idx]->status = DELETED;
            return;
        }
        if (ptr->associativearr[idx] == NULL){
            return;
        }
        i++;
    }
}
void hash_table_insert(hash_table_t *ptr, int key, node_infos_t *NewMRU){
    int i = INITVAR;
    int idx = INITVAR;
    while (i < ptr->MaxSlot){
        idx = hash_table_linear_probing(key, i, ptr);
         if (ptr->associativearr[idx] == NULL){
            ptr->associativearr[idx] = hash_table_create_bucket(key, NewMRU);
            return;
        }
        if (ptr->associativearr[idx]->key == key){
            ptr->associativearr[idx]->address = NewMRU;
            return;
        }
        if (ptr->associativearr[idx]->status == DELETED){
            i++;
            continue;
        }
        if (ptr->associativearr[idx]){
            i++;
            continue;
        }
       
        i++;
    }
}
node_infos_t *hash_table_search(int key, hash_table_t *ptr){
    int i = INITVAR;
    int idx = INITVAR;
    while (i < ptr->MaxSlot){
        idx = hash_table_linear_probing(key, i, ptr);
        if (ptr->associativearr[idx] == NULL){
            return NULL;
        }
        if (ptr->associativearr[idx]->key == key){
            return ptr->associativearr[idx]->address;
        }
        if (ptr->associativearr[idx]->status == DELETED){
            i++;
            continue;
        }
        i++;
    }
    return NULL;
}
void hash_table_free(hash_table_t *ptr){
    if (!ptr) return;
    if (ptr->associativearr){
    for (int i = INITVAR;i < ptr->MaxSlot;i++){
            free(ptr->associativearr[i]);    //In C free(NULL) it is not a problem.
        }
       free(ptr->associativearr);
    }
    free(ptr);
}

float hash_table_load_factor(int n, int m){
    return (float)(n / m);
}
