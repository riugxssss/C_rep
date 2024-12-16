//BST tree project by riugxs 'BASIC'

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree
{
    int value;
    struct tree *left;
    struct tree *right;
}tree;

tree *func(int value){
    tree *root = malloc(sizeof(tree));
    if (root == NULL){
        fprintf(stderr, "[!] ERROR WITH THE ALLOCATION");
        exit(EXIT_FAILURE);
    }
    root->left = NULL;
    root->right = NULL;
    root->value =value;
    return root;
}
void dest(tree *root){
    if (root == NULL) return;
    dest(root->left);
    dest(root->right);
    free(root);
}
void tab(int tab_number){
    for (int i = 0; i<tab_number;i++){
        putchar('\t');
    }
}
void print_tree(tree *root, int value){
    if (root==NULL){
        tab(value);
        printf("EMPTY\n");
        return;
    }
    tab(value);
    printf("LEFT LEAF\n");
    print_tree(root->left, value+1);
    tab(value);
    printf("Value L: %d\n", root->value);
    tab(value);
    printf("RIGHT LEAF\n");
    print_tree(root->right, value +1);
    tab(value);
    printf("Value R: %d\n", root->value);

    tab(value);
    printf("DONE\n");
}
void printnorec(tree *root){
    print_tree(root, 0);
}
bool find(tree *root, int value){
    if (root==NULL){
        return false;
    }
    if (root->value == value){
        return true;
    }
    if (value < root->value){
        return find(root->left,value);
    } else {
        return find(root->right, value);
    }
}
bool insert_number(tree **root, int value){
    tree *r1 = *root;
    if (r1 == NULL){
        (*root) = func(value);
        return true;
    }
    if (r1->value == value){
        return false;
    }
    if (value < r1->value){
        return insert_number(&(r1->left), value);
    } else {
        return insert_number(&(r1->right), value);
    }

}
int main(){

    tree *t1 = NULL;
    insert_number(&t1, 16);
    insert_number(&t1, 12);
    insert_number(&t1, 1);
    insert_number(&t1, 30);
    insert_number(&t1, 19);
    
    printnorec(t1);
    if (find(t1, 16)){
        printf("Number founded in the tree.");
    } else printf("Number not in the tree.");
    dest(t1);
    return 0;
}

//Pretty basic example BST tree with all func. 
