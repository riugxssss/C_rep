#ifndef STACKUTILS_H
#define STACKUTILS_H
#include <stdbool.h>

//Fast macro
#define $i int
#define $s stack_t
#define $sp stack_t *

//Size macros
#define EMPTY 1
#define FULL 0
#define DEFAULTSIZE 10
#define EXPANDSIZE 8

typedef struct Stack{
    int elementsize;
    int *block;
    int container; 
}stack_t;

//Static linkage
#define hidden __attribute__((visibility("hidden")))

stack_t *AllocDyn(int containersize);
bool empty(stack_t *ptrstruct);
bool full(stack_t *ptrstruct);
void freeall(stack_t *ptrstruct);
int push(stack_t *ptrstruct, int n);
int pop(stack_t *ptrstruct, int n);
void peekall(stack_t *ptrstruct);
void dam(stack_t *ptrstruct, int expand);

#endif
