#include <stdio.h>
#include <stdlib.h>
#include "queue_utils.h"

// Prints error message and exits program if memory allocation fails
void fatalAlloc(const char *Funcname){
    fprintf(stderr, "[!] The allocation failed in '%s'\n", Funcname);
    exit(EXIT_FAILURE);
}

// Create and initialize an empty queue
QueueStruct *Create_Queue(){
    QueueStruct *newptr = (QueueStruct *) malloc(sizeof(*newptr));
    if (!newptr){
        fatalAlloc("create_queue"); // Handle allocation failure
    }
    newptr->front = newptr->rear = NULL; // Initialize pointers to NULL
    return newptr;
}

// Create a new queue node containing a pointer to a tree node
QueueNode *Create_qNode(TreeNode *nodeptr){
    QueueNode *newnode = (QueueNode *) malloc(sizeof(*newnode));
    if (!newnode){
        fatalAlloc("create_qNode"); // Handle allocation failure
    }
    newnode->node = nodeptr; // Store tree node pointer
    newnode->next = NULL;    // Next pointer is NULL initially
    return newnode;
}

// Check if the queue is empty
int IsEmpty(QueueStruct *queueptr){
    return queueptr->front == NULL;
}

// Add a tree node to the end of the queue
void EnqueueNode(QueueStruct *queueptr, TreeNode *treeptr){
    QueueNode *queuenode = Create_qNode(treeptr);
    if (IsEmpty(queueptr)){
        queueptr->front = queueptr->rear = queuenode; // First node in queue
        return;
    }
    queueptr->rear->next = queuenode; // Link new node at the end
    queueptr->rear = queuenode;       // Update rear pointer
}

// Remove and return the tree node from the front of the queue
TreeNode *DequeueNode(QueueStruct *queueptr){
    if (IsEmpty(queueptr)){
        return NULL; // Nothing to dequeue
    }
    QueueNode *tmp = queueptr->front;           // Store front node temporarily
    queueptr->front = queueptr->front->next;   // Move front pointer forward
    if (IsEmpty(queueptr)){
        queueptr->rear = NULL; // Queue is now empty
    }
    TreeNode *returnNode = tmp->node; // Retrieve tree node
    free(tmp);                        // Free queue node
    return returnNode;
}

// Free all nodes in the queue and the queue itself
void Free_Queue(QueueStruct* queueptr){
    QueueNode *tmp;
    while (queueptr->front){             // Loop through all nodes
        tmp = queueptr->front;
        queueptr->front = queueptr->front->next;
        free(tmp);                       // Free each queue node
    }
    free(queueptr);                      // Free the queue structure
}
