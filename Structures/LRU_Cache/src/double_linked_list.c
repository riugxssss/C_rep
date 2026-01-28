#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "HandlingUtils.h"

// Structure representing a single node in a doubly linked list.
// Each node stores a key-value pair and pointers to the previous and next nodes.
typedef struct node_infos {
    int value;                  // Value associated with the node (data stored)
    int key;                    // Key associated with the node (for quick lookup in a hash table)
    struct node_infos *prev;    // Pointer to the previous node in the list
    struct node_infos *next;    // Pointer to the next node in the list
} node_infos_t;

// Structure representing a doubly linked list.
// This list is typically used to implement an LRU cache, where head = MRU and tail = LRU.
typedef struct double_l_list {
    node_infos_t *head;         // Most recently used (MRU) node, at the head of the list
    node_infos_t *tail;         // Least recently used (LRU) node, at the tail of the list
    int n_nodes;                // Number of nodes currently in the list
} double_l_list_t;

// Function to create a new empty doubly linked list.
// Initializes head and tail to NULL and node count to 0.
double_l_list_t *d_linkedlist_create(){
    double_l_list_t *list = malloc(sizeof(*list));
    if (!list){
        error_handler(ENOMEM); // Handle memory allocation failure
    }

    list->head = NULL;   // No nodes yet
    list->tail = NULL;
    list->n_nodes = 0;   // Node count starts at 0

    return list;
}

// Internal helper function to create a new node with a given key and value.
// The node is isolated (prev and next are NULL) and must be inserted into the list manually.
static node_infos_t *d_linked_list_create_node(int value, int key){
    node_infos_t *node = malloc(sizeof(*node));
    if (!node){
        error_handler(ENOMEM); // Handle memory allocation failure
    }

    node->value = value;  // Set node value
    node->key = key;      // Set node key
    node->prev = node->next = NULL; // Initially isolated

    return node;
}

// Insert a new node at the head of the doubly linked list (MRU position).
// This operation is O(1) because we keep a pointer to the head.
node_infos_t *d_linkedlist_insert_node(double_l_list_t *list, int value, int key){
    node_infos_t *new_node = d_linked_list_create_node(value, key);

    if (list->head){
        // If list is not empty, update current head's previous pointer
        list->head->prev = new_node;
        new_node->next = list->head;
    } else {
        // If list was empty, the new node is also the tail (LRU)
        list->tail = new_node;
    }

    list->head = new_node; // Update head pointer to new node
    list->n_nodes++;       // Increment node count

    return new_node;
}

// Remove the least recently used (LRU) node from the tail of the list.
// Frees memory of the removed node and updates list pointers accordingly.
void d_linkedlist_remove_lru(double_l_list_t *list){
    if (!list->head) return; // Empty list, nothing to remove

    node_infos_t *lru_node = list->tail;

    if (list->n_nodes == 1){
        // Only one node in the list; after removal list becomes empty
        free(lru_node);
        list->head = list->tail = NULL;
        list->n_nodes = 0;
        return;
    }

    // Remove tail node and update previous node as the new tail
    list->tail = lru_node->prev;
    list->tail->next = NULL;
    free(lru_node);
    list->n_nodes--;
}

// Free the entire doubly linked list and all its nodes.
// Iterates through the list and frees each node individually.
void d_linkedlist_free(double_l_list_t *list){
    if (!list || !list->head) return; // Nothing to free

    node_infos_t *curr;
    while (list->head){
        curr = list->head;
        list->head = list->head->next;
        free(curr);
    }
    list->tail = NULL;
    list->n_nodes = 0;
}

// Return the value stored in the least recently used (LRU) node.
// If list is empty, returns -1 to indicate no value exists.
int d_linkedlist_getLRU(double_l_list_t *list){
    if (!list || !list->tail) return -1;
    return list->tail->value;
}

// Return the value stored in the most recently used (MRU) node.
// If list is empty, returns -1 to indicate no value exists.
int d_linkedlist_getMRU(double_l_list_t *list){
    if (!list || !list->head) return -1;
    return list->head->value;
}

// Move a given node to the head of the list (MRU position).
// This operation is commonly used in LRU caches when a node is accessed.
void d_linkedlist_move_to_head(node_infos_t *node, double_l_list_t *list){
    if (!list || !node || list->head == node || list->n_nodes <= 1) return;

    // Detach the node from its current position
    if (node->prev){
        node->prev->next = node->next;
    }
    if (node->next){
        node->next->prev = node->prev;
    } else {
        // Node is the tail, so update tail pointer
        list->tail = node->prev;
    }

    // Insert node at head
    node->prev = NULL;
    node->next = list->head;
    list->head->prev = node;
    list->head = node;

    if (!list->tail){
        // If list was previously empty (should not happen here), set tail
        list->tail = node;
    }
}

// Print the entire list for debugging purposes.
// Displays MRU, LRU, and all key-value pairs in order from head to tail.
void d_linkedlist_print(double_l_list_t *list){
    if (!list) return;

    printf("PRINTING CACHE\n");
    printf("MRU: %d\nLRU: %d\n", d_linkedlist_getMRU(list), d_linkedlist_getLRU(list));

    node_infos_t *curr = list->head;
    while (curr){
        printf("(key: %d | value: %d)\n", curr->key, curr->value);
        curr = curr->next;
    }
    putchar('\n');
}

// Return the key stored in the least recently used (LRU) node.
// Returns -1 if list is empty.
int d_linkedlist_getLRU_key(double_l_list_t *list){
    if (!list || !list->tail) return -1;
    return list->tail->key;
}
