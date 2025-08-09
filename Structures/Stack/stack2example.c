#include <stdio.h>
#include <stdlib.h>

// Define a stack structure
typedef struct stack_t {
    int *arr;       // Dynamic array to store stack elements
    int top;        // Index of the current top element (-1 means empty)
    int sizearr;    // Current capacity of the stack
} stack_t;

//Using to self explain the program without using "magic numbers"
#define EMPTY -1
//Macro to double the sizearray
#define DOUBLESIZE(arr) ((arr)->sizearr * 2)
// Create a stack with an initial size 'nsize'
stack_t *create_arr(int nsize) {
    // Allocate memory for the stack structure
    stack_t *ptr = malloc(sizeof(*ptr));
    if (!ptr) {
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the internal integer array
    ptr->arr = malloc(nsize * sizeof(*ptr->arr));
    if (!ptr->arr) {
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    } 

    ptr->top = EMPTY;           // Start with stack empty
    ptr->sizearr = nsize;    // Set initial capacity

    return ptr;              // Return pointer to new stack
}

// Check if the stack is empty
int isempty(stack_t *arr) {
    return arr->top == EMPTY;
}

// Check if the stack is full
int isfull(stack_t *arr) {
    return arr->top + 1 == arr->sizearr; /*top + 1 because top start 0 1.. if the arr size is 5
    full top size is 4, + 1 = 5 == 5 -> FULL
    */
}

// Push a new element 'n' onto the stack
// If the stack is full, attempt to double its capacity (up to 30 elements max)
void push(stack_t **arr, int n) {
    if (isfull(*arr)) {
        if ((*arr)->sizearr >= 30) {
            printf("Max limit realloc possible\n");
            return;
        }

        int newsize = DOUBLESIZE(*arr); 
        int *newarr = realloc((*arr)->arr, newsize * sizeof(int));
        if (!newarr) {
            printf("Array full\n [Fail to realloc]\n");
            return;
        }
        (*arr)->arr = newarr;
        (*arr)->sizearr = newsize;  // Update capacity
    }

    // Insert element at top and increment top index
    (*arr)->arr[++(*arr)->top] = n;
}

// Pop the top element from the stack and print it
void pop(stack_t *arr) {
    if (isempty(arr)) {
        printf("Stack is empty\n");
        return;
    }
    int n = arr->arr[arr->top--];
    printf("Popped value: %d\n", n);
}

// Return the top element without removing it
int top(stack_t *arr) {
    if (isempty(arr)) {
        printf("Stack is empty\n");
        return 0; // Return 0 as a default value (could also handle with error code)
    }
    return arr->arr[arr->top];
}

// Free all memory used by the stack
void free_all(stack_t *arr) {
    free(arr->arr);  // Free the internal array
    free(arr);       // Free the stack structure
}

// Print all elements in the stack from bottom to top
void print_all(stack_t *arr) {
    if (isempty(arr)) return;
    for (int i = 0; i <= arr->top; i++) {
        printf("%d ", arr->arr[i]);
    }
    putchar('\n');
}

int main(void) {
    // Create a stack with initial capacity of 5
    stack_t *arr = create_arr(5);

    // Push several elements (stack will grow dynamically when full)
    push(&arr, 6);
    push(&arr, 7);
    push(&arr, 1);
    push(&arr, 7);
    push(&arr, 7);
    push(&arr, 2);

    // Print all elements in the stack
    print_all(arr);

    // Free allocated memory
    free_all(arr);

    return 0;
}
