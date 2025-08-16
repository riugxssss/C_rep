#ifndef QUEUE_UTILS_H
#define QUEUE_UTILS_H

#include "tree_utils.h"

// Queue node structure, stores a pointer to a tree node and a pointer to the next queue node
typedef struct QueueNode {
    TreeNode *node;           
    struct QueueNode *next;  
} QueueNode;

// Queue structure, keeps track of front and rear of the queue
typedef struct QueueStruct {
    struct QueueNode* rear;   
    struct QueueNode* front;  
} QueueStruct;

/*
Queue visualization:

Initially empty:
front -> NULL
rear  -> NULL

After enqueueing nodes A, B, C:

front -> [A] -> [B] -> [C] <- rear

Dequeue removes from front:
Dequeue 1 time:
front -> [B] -> [C] <- rear
*/


// Creates and initializes an empty queue
QueueStruct *Create_Queue();

// Creates a new queue node containing a pointer to a tree node
QueueNode *Create_qNode(TreeNode *nodeptr);

// Checks if the queue is empty (returns 1 if empty, 0 otherwise)
int IsEmpty(QueueStruct *queueptr);

// Adds a tree node to the end of the queue (rear)
void EnqueueNode(QueueStruct *queueptr, TreeNode *treeptr);

// Removes and returns the tree node from the front of the queue
TreeNode *DequeueNode(QueueStruct *queueptr);

// Frees all nodes in the queue and the queue structure itself
void Free_Queue(QueueStruct *queueptr);

// Prints an error message and exits if memory allocation fails
void fatalAlloc(const char *Funcname);

#endif
