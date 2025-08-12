#include <stdio.h>
#include <stdlib.h>

typedef struct st {
    int sizearr;
    char *arr;
    int top;
}st;

st *create(int val){
    st *newn = malloc(sizeof(*newn));
    if (!newn){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    newn->arr = (char *) malloc(val * sizeof(*newn->arr));
    if (!newn->arr){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }

    newn->sizearr = val;
    newn->top = -1;

    return newn;
}

int isempty(st *ptr){
    return ptr->top == -1;
}
int isfull(st *ptr){
    return ptr->top + 1 == ptr->sizearr;
}

void push(st *ptr, char val){
    if (isfull(ptr)) return;
    ptr->arr[++ptr->top] = val;
}


char top(st *ptr){
    if (isempty(ptr)) return 0;
    return ptr->arr[ptr->top];
}
int pop(st *ptr){
    if (isempty(ptr)) return -1;
    return ptr->arr[ptr->top--];
}

void free_all(st *ptr){
    free(ptr->arr);
    free(ptr);
}

static int check_parenthesis(char left, char right){
    if (left == '(' && right == ')' ||
        left == '[' && right == ']' ||
        left == '{' && right == '}'){
            return 1;
        }
    return 0;
}

int check_balance(const char *buffer){
    st *stack = create(10);
    for (int i = 0; buffer[i] != '\0';i++){
        char ch1 = buffer[i];
        if (ch1 == '(' || ch1 == '[' || ch1 == '{'){
            push(stack, ch1);
        }else if (ch1 == ')' || ch1 == ']' || ch1 == '}'){
            if (isempty(stack)){
                free_all(stack);
                return 0;
            }
            else {
                char ch2 = top(stack);
                if (check_parenthesis(ch2, ch1)){
                    pop(stack);
                }else {
                    free_all(stack);
                    return 0;
                }
            }
        }
    }
    int balanced = isempty(stack);
    free_all(stack);
    return  balanced ? 1 : 0;
}

int main(void){

    char buffer[] = "[()]";
    if (check_balance(buffer)){
        printf("Balanced\n");
    }else printf("Unbalanced\n");

    return 0;
}
