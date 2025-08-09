#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
}node;

void insert_node(node **head, int val){
    node *newn = malloc(sizeof(*newn));
    if (!newn){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    newn->val = val;
    newn->next = NULL;

    if (*head) newn->next = *head;
    *head = newn;
}


void reverse_list(node **head){
    node *tmp = *head;
    node *prev = NULL;
    node *next;
    while (tmp){
        next = tmp->next;
        tmp->next = prev;
        prev = tmp;
        tmp = next;
    }
    *head = prev;
}

void reverse_recursive(node **head){
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    node *rest = (*head)->next;
    reverse_recursive(&rest);
    (*head)->next->next = *head; //es head 7, 7->next(5)->next = 7, 5->7
    (*head)->next = NULL; //5->7->NULL but the head is still 7
    *head = rest; //update the head using rest ptr pointing to 5
}

void print_recursion(node *head){
    if (!head){
        putchar('\n');
        return;
    }
    printf("%d ", head->val);
    print_recursion(head->next);
}

void printback_recursion(node *head){
    if (head == NULL){
        return; 
    }
    printback_recursion(head->next);
    printf("%d ", head->val);
    putchar('\n');
}

void insertnth(node **head, int val, int n){
    node *newn = malloc(sizeof(*newn));
    node *ptr = *head;
    if (!newn){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    newn->val = val;
    if (n == 1){
        newn->next = ptr; 
        ptr = newn;
        return;
    }
    for (int i = 0;i< n - 2;i++){
        ptr = ptr->next;
    }
    newn->next = ptr->next;    
    ptr->next = newn;
}

void deletenth(node **head, int n){
    if (*head == NULL) return;
    node *tmp = *head;
    if (n == 1){
        *head = tmp->next;
        free(tmp);
        return;
    }

    for (int i = 0;i<n - 2;i++){
        if (tmp->next == NULL) return;
        tmp = tmp->next; //nth - 1
    }
    if (tmp->next == NULL) return;
    node *tmp2 = tmp->next;
    tmp->next = tmp2->next;
    free(tmp2);
}

void print_list(node *head){
    while (head){
        printf("%d ", head->val);
        head = head->next;
    }
    putchar('\n');
}

void free_list(node *head){
    node *tmp;
    while (head){
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
void free_recursive(node *head){
    if (!head) return;
    free_recursive(head->next);
    free(head);
}

int main(void){

    node *head = NULL;
    int n;
    int number;
    int pos;
    printf("Enter the number of list: ");
    scanf("%d", &n);
    for (int i = 0;i<n;i++){
        printf("Enter the number: ");
        scanf("%d", &number);
        insert_node(&head, number);
        print_list(head);
    }
    // other functions.....

    free_list(head);

    return 0;
}
