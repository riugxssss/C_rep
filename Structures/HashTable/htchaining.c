#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 50

typedef struct slots {
    char *key;
    char *value;
    struct slots *next;
}slots;

typedef struct hasht {
    struct slots **entries;
}hasht;

hasht *create_hash_table(){
    hasht *newnht = malloc(sizeof(*newnht));
    if (!newnht) return NULL;
    newnht->entries = calloc(TABLE_SIZE, sizeof(slots *));
    if (!newnht->entries) return NULL;
    return newnht;
}

unsigned int hash_function(const char *key){
    unsigned int key_len = strlen(key);
    unsigned int value = 0;
    for (int i = 0;i< key_len;i++){
        value = value * 3 + key[i];
    }
    return value % TABLE_SIZE;
}

slots *create_slot(const char *key, const char *value){
    slots *ptr = malloc(sizeof(slots));
    if (!ptr) return NULL;
    ptr->key = malloc(strlen(key) + 1);
    ptr->value = malloc(strlen(value) + 1);
    strncpy(ptr->key, key, sizeof(key));
    strncpy(ptr->value, value, sizeof(value));
    ptr->next = NULL;
    return ptr;
}

void ht_set(hasht *ht, const char *key, const char *value){
    unsigned int slot = hash_function(key);
    slots *ptr = ht->entries[slot];
    if (!ptr){
        ht->entries[slot] = create_slot(key, value);
        return;
    }

    slots *prev = NULL;
    while (ptr){
        if (strcmp(ptr->key, key) == 0){
            free(ptr->value);
            ptr->value = malloc(strlen(value) + 1);
            strncpy(ptr->value, value, sizeof(value));
        }
        prev = ptr;
        ptr = ptr->next;
    }
    prev->next = create_slot(key, value);
}

char *ht_get(hasht *ht, const char *key){
    unsigned int slotn = hash_function(key);
    slots *ptr = ht->entries[slotn];
    if (!ptr){
        printf("[INFO] The slot [%d] is NULL\n", slotn);
        return NULL;
    }
    while(ptr){
        if (strcmp(ptr->key, key) == 0){
            return ptr->value;
        }
        ptr = ptr->next;
    }
    return NULL;
}

void ht_dump(hasht *ht){
    for (int i = 0;i<TABLE_SIZE;i++){
        slots *ptr = ht->entries[i];
        if (!ptr) continue;
        printf("Slot[%04d]: ", i);
        while(ptr){
            printf("%s = %s", ptr->key, ptr->value);
            ptr = ptr->next;
        }
        putchar('\n');
    }
}

void free_table(hasht *ht){
    for (int i = 0;i<TABLE_SIZE;i++){
        slots *ptr = ht->entries[i];
        while (ptr){
            slots *tmp = ptr;
            ptr = ptr->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
    }
    free(ht->entries);
    free(ht);
}

int main(void) {

   
    hasht *ht = create_hash_table();
    ht_set(ht, "name1", "em");
    ht_set(ht, "name2", "pizza");
    ht_set(ht, "name3", "test");
    ht_set(ht, "name4", "diocane");
    ht_set(ht, "name5", "mammt");
    printf("%s\n", ht_get(ht, "name1"));
    free_table(ht);


    return 0;
}
