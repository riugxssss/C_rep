#include <stdio.h>
#include <stdlib.h>
#include "double_linked_list.h"
#include "HandlingUtils.h"
#include <errno.h>

#define INITVAR 0        // Initial value used for counters or indexes
#define OCCUPIED 1       // Indicates that a hash table slot is currently in use
#define DELETED 2        // Indicates that a slot previously held a value but is now deleted

// This structure represents a single slot in the hash table.
// Each slot can be empty, occupied, or marked as deleted for linear probing purposes.
typedef struct slot_info {
    int status:3;           // Status of the slot: INITVAR (unused), OCCUPIED, DELETED
    int key;                // The key stored in this slot
    node_infos_t *node;     // Pointer to a node in the LRU list corresponding to this key
} slot_info_t;

// Structure representing the hash table itself.
// It stores the maximum number of slots and an array of pointers to slot_info structures.
typedef struct hash_table {
    int max_slots;          // Maximum capacity of the hash table
    slot_info_t **slots;    // Array of pointers to slot structures (buckets)
} hash_table_t;

// Function to create a new hash table with a given number of slots.
// Allocates memory for the table and initializes all slots to NULL.
hash_table_t *hash_table_create(int max_slots){
    // Allocate memory for the hash_table structure
    hash_table_t *table = malloc(sizeof(*table));
    if (!table){
        error_handler(ENOMEM);   // Handle memory allocation failure
    }

    table->max_slots = max_slots;

    // Allocate memory for the array of slot pointers and initialize all to NULL
    table->slots = calloc(max_slots, sizeof(slot_info_t *));
    if (!table->slots){
        free(table);             // Free previously allocated memory to prevent leaks
        error_handler(ENOMEM);
    }

    return table;
}

// Function to create a new slot (bucket) for a given key and corresponding node in LRU list.
// Sets the key, node pointer, and marks the slot as OCCUPIED.
static slot_info_t *hash_table_create_bucket(int key, node_infos_t *node){
    slot_info_t *bucket = malloc(sizeof(*bucket));
    if (!bucket){
        error_handler(ENOMEM);   // Handle memory allocation failure
    }

    bucket->key = key;           // Store the key in the slot
    bucket->node = node;         // Associate the node from the LRU list
    bucket->status = OCCUPIED;   // Mark the slot as occupied

    return bucket;
}

// Simple hash function using modulo operation.
// Maps the integer key into the range [0, max_slots-1].
static inline int hash_table_hash_function(int key, int max_slots){
    return key % max_slots;
}

// Linear probing function to handle collisions in the hash table.
// If a slot is already occupied, we try the next slot in sequence.
static inline int hash_table_linear_probing(int key, int i, hash_table_t *table){
    return (hash_table_hash_function(key, table->max_slots) + i) % table->max_slots;
}

// Function to delete a key from the hash table.
// Marks the corresponding slot as DELETED without physically removing it to maintain probe sequences.
void hash_table_delete(hash_table_t *table, int key){
    int i = INITVAR;  // Counter for probing sequence
    int idx = INITVAR; // Computed index in the hash table

    // Iterate over the hash table with linear probing
    while (i < table->max_slots){
        idx = hash_table_linear_probing(key, i, table);

        if (table->slots[idx] == NULL){
            // Slot is empty, key does not exist in the table
            return;
        }

        if (table->slots[idx]->key == key){
            // Found the key, mark it as DELETED
            table->slots[idx]->status = DELETED;
            return;
        }

        i++; // Move to the next slot in the probing sequence
    }
}

// Function to insert a key-node pair into the hash table.
// Uses linear probing to handle collisions and skips deleted slots.
void hash_table_insert(hash_table_t *table, int key, node_infos_t *node){
    int i = INITVAR;
    int idx = INITVAR;

    while (i < table->max_slots){
        idx = hash_table_linear_probing(key, i, table);

        if (table->slots[idx] == NULL){
            // Empty slot found, create a new bucket here
            table->slots[idx] = hash_table_create_bucket(key, node);
            return;
        }

        if (table->slots[idx]->status == DELETED){
            // Skip deleted slots; could reuse them instead if implementing "lazy deletion"
            i++;
            continue;
        }

        if (table->slots[idx]){
            // Slot occupied, continue probing
            i++;
            continue;
        }

        i++;
    }
}

// Function to search for a key in the hash table.
// Returns the pointer to the corresponding node in the LRU list, or NULL if not found.
node_infos_t *hash_table_search(int key, hash_table_t *table){
    int i = INITVAR;
    int idx = INITVAR;

    while (i < table->max_slots){
        idx = hash_table_linear_probing(key, i, table);

        if (table->slots[idx] == NULL){
            // Empty slot means key is not present
            return NULL;
        }

        if (table->slots[idx]->key == key){
            // Key found, return associated node
            return table->slots[idx]->node;
        }

        if (table->slots[idx]->status == DELETED){
            // Skip deleted slots, continue searching
            i++;
            continue;
        }

        i++;
    }

    // Key not found after probing all slots
    return NULL;
}

// Function to free the memory allocated for the hash table.
// Iterates through all slots and frees each bucket, then frees the slots array and table.
void hash_table_free(hash_table_t *table){
    if (!table) return;

    if (table->slots){
        for (int i = INITVAR; i < table->max_slots; i++){
            free(table->slots[i]);    // Safe to call free(NULL) in C
        }
        free(table->slots);           // Free the array of slot pointers
    }

    free(table);                      // Free the hash table structure itself
}

// Function to compute the load factor of the hash table.
// Load factor = number of occupied slots / total slots, useful for resizing decisions.
float hash_table_load_factor(int n, int m){
    return (float)(n) / m;
}
