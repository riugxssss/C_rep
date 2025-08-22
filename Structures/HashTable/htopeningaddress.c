#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 26

typedef enum Status {
    ALIVE = 1,
    DEAD = 0,
    DELETED = 2
}status_t;

typedef struct items {
    int key;
    int value;
    int status;
}items;

typedef struct ht {
    struct items **arr;
}ht;

ht *create_hash_table(){
    ht *ptr = malloc(sizeof(*ptr));
    if (!ptr) return NULL;
    ptr->arr = calloc(CAPACITY, sizeof(items *));
    if (!ptr->arr) return NULL;
    return ptr;
}

items *create_slot(int key, int value){
    items *ptr = malloc(sizeof(*ptr));
    if (!ptr) return NULL;
    ptr->value = value;
    ptr->key = key;
    ptr->status = ALIVE;
    return ptr;
}

//Hash function 1
int h1(int key){
    return key % CAPACITY;
}

//Hash Function 2
int h2(int key){
    return 13 - (key % 13);
}

//Linear Probing
int linear_probing(int key, int i){
    return (h1(key) + i) % CAPACITY; //lineaer probing +1, +2, +3
}

//Quadratic Probing
int quadratic_probing(int key, int i){
    return (h1(key) + i * i) % CAPACITY;
}

//Double Hashing
int double_hashing(int key, int i){
    return (h1(key) + i * h2(key)) % CAPACITY;
}


int search(ht *ptr, int key){
    int i = 0;
    int idx = 0;
    while (i < CAPACITY){
        idx = linear_probing(key, i);
        if (ptr->arr[idx] == NULL){
            return 0;
        }
        if (ptr->arr[idx]->status == DELETED){
            i++;
            continue;
        }
        if (ptr->arr[idx]->key == key){
            return 1;
        }
        i++;
    }
    return 0;
}

void insert(ht *ptr, int key, int value){
    int idx =0 ;
    int i = 0;
    int first_deleted = -1; //take the first deleted node and reuse
    while (i < CAPACITY){
        idx = linear_probing(key, i);
        //First case
        if (!ptr->arr[idx]){
            if (first_deleted != -1){
                ptr->arr[first_deleted]->key = key;
                ptr->arr[first_deleted]->value = value;
                ptr->arr[first_deleted]->status = ALIVE;
            }else {
                ptr->arr[idx] = create_slot(key, value);
                ptr->arr[idx]->status = ALIVE;
            }
            return;
        }
        //Second case
        if (ptr->arr[idx]->status == DELETED){
            if (first_deleted == -1){
                first_deleted = idx; //We save up the first deleted element in the hash table
            }
            i++;
            continue;
        }
        //Third case (if we want to modify an exisistent value)
        if (ptr->arr[idx]->key == key){
            ptr->arr[idx]->value = value;
            return;
        }
        i++;
    }
    if (first_deleted != -1) {
        ptr->arr[first_deleted]->key = key;
        ptr->arr[first_deleted]->value = value;
        ptr->arr[first_deleted]->status = ALIVE;
        return;
    }

    printf("[INFO] Max capacity REACHED: [%d]\n", CAPACITY);
}

void delete(ht *ptr, int key){
    int i = 0;
    int idx = 0;
    while (i< CAPACITY){
        idx = linear_probing(key, i);
        if (ptr->arr[idx] == NULL){
            return;
        }
        if (ptr->arr[idx]->key == key){
            ptr->arr[idx]->status = DELETED;
            return;
        }
        i++;
    }
}

void dump(ht *ptr){
    printf("-----Hash Table-----\n");
    for (int i = 0;i<CAPACITY;i++){
        if (ptr->arr[i] == NULL){
            printf("slot[%02d]: <>", i);
        }
        else if (ptr->arr[i]->status == DELETED){
            printf("slot[%02d]: <deleted>", i);
        }
        else {
            printf("slot[%02d]: %d -> %d",i, ptr->arr[i]->key, ptr->arr[i]->value);
        }
        putchar('\n');
    }
    printf("---------------\n");
}

void free_hash_table(ht *ptr){
    if (!ptr) return;
    for (int i =0 ;i<CAPACITY;i++){
        if (ptr->arr[i]){
            free(ptr->arr[i]);
        }
    }
    free(ptr->arr);
    free(ptr);
}

int main(void) {

    ht *ptr = create_hash_table();
    insert(ptr, 1, 10);
    insert(ptr, 14, 20); 
    insert(ptr, 27, 30); 
    insert(ptr, 5, 50);
    insert(ptr, 18, 60);

    dump(ptr);

    printf("Search key=14 -> %d\n", search(ptr ,14));

    dump(ptr);
    free_hash_table(ptr);

    return 0;
}
