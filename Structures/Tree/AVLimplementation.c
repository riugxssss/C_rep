#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
    int height;
}node;

node *create_node(int data){
    node *newn = malloc(sizeof(*newn));
    if (!newn){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    newn->left = newn->right = NULL;
    newn->val = data;
    newn->height = 0;
    return newn;
}

void print_all(node *root){
    if (!root) return;
    print_all(root->left);
    printf("%d\n", root->val);
    print_all(root->right);
}

void free_all(node *root){
    if (!root) return;
    free_all(root->left);
    free_all(root->right);
    free(root);
}

//Find height of the tree
int ht(node *ptr){
    if (!ptr) return -1;
    return ptr->height;
}


node *rotate_right(node *y){
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2; //in case there is a subtree in x
    
    //update height of the old and new root
    y->height = 1 + (ht(y->left) > ht(y->right) ? ht(y->left) : ht(y->right));
    x->height = 1 + (ht(x->left) > ht(x->right) ? ht(x->left) : ht(x->right));

    return x;
}


node *rotate_left(node *y){
    node *x = y->right;
    node *T2 = x->left;

    x->left = y; //x > y so left child of x become y
    y->right = T2;

    //update height of the old and new root
    y->height = 1 + (ht(y->left) > ht(y->right) ? ht(y->left) : ht(y->right));
    x->height = 1 + (ht(x->left) > ht(x->right) ? ht(x->left) : ht(x->right));
    return x;
}


int balance_factor(node *ptr){
    if (!ptr) return 0;
    return ht(ptr->left) - ht(ptr->right);
}
node *insert_node(node *ptr, int data){
    if (!ptr) return create_node(data);
    if (ptr->val > data){
        ptr->left = insert_node(ptr->left, data);
    }else if(ptr->val < data) {
        ptr->right = insert_node(ptr->right, data);
    }else return ptr;

    ptr->height = 1 + (ht(ptr->left) > ht(ptr->right) ? ht(ptr->left) : ht(ptr->right));


    int bf = balance_factor(ptr);
    //LL
    if (bf > 1 && data < ptr->left->val){
        return rotate_right(ptr);
    }
    //RR
    if (bf < -1 && data > ptr->right->val){
        return rotate_left(ptr);
    }
    //LR
    if (bf > 1 && data > ptr->left->val){
        ptr->left = rotate_left(ptr->left);
        return rotate_right(ptr);
    }
    //RL
    if (bf < -1 && data < ptr->right->val){
        ptr->right = rotate_right(ptr->right);
        return rotate_left(ptr);
    }
    return ptr;
}

int main(void){

    node *ptr = NULL;
    ptr = insert_node(ptr, 3);
    ptr = insert_node(ptr, 5);
    ptr = insert_node(ptr, 7);
    ptr = insert_node(ptr, 1);
    print_all(ptr);
    free_all(ptr);


    return 0;
}
