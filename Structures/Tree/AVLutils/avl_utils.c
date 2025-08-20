#include <stdio.h>
#include <stdlib.h>
#include "avl_utils.h"

typedef struct node {
    int height;
    int data;
    struct node *left;
    struct node *right;
}node;

typedef enum Macros {
    INITVAR = 666,
    TRUE = 1,
    FALSE = 0,
    EMPTY = -1
}macro_t;

node *create_node(int data){
    node *newn = malloc(sizeof(*newn));
    if (!newn){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }
    newn->data = data;
    newn->height = INITVAR;
    newn->left = newn->right = NULL;
    return newn;
}

private void print_tree(node *root){
    if (!root) return;
    print_tree(root->left);
    printf("%d\n", root->data);
    print_tree(root->right);
}

void print_AVL(node *root){
    if (!root){
        printf("No nodes created\n");
        return;
    }
    printf("START {\n");
    print_tree(root);
    printf("} END\n");
}

void free_tree(node *root){
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int ht(node *root){
    if (!root) return EMPTY;
    return root->height;
}
int bf(node *root){
    if (!root) return EMPTY;
    return ht(root->left) - ht(root->right);
}

private node *rotate_right(node *y){
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;


    //Node y
    int left_height = ht(y->left);
    int right_height = ht(y->right);

    y->height = 1 + (left_height > right_height ? left_height : right_height);


    //Node x
    left_height = ht(x->left);
    right_height = ht(x->right);

    x->height = 1 + (left_height > right_height ? left_height : right_height);

    return x;
}

private node *rotate_left(node *y){
    node *x = y->right;
    node *T2 = x->left;

    x->left = y;
    y->right = T2;

    //Node y
    int left_height = ht(y->left);
    int right_height = ht(y->right);

    y->height = 1 + (left_height > right_height ? left_height : right_height);


    //Node x
    left_height = ht(x->left);
    right_height = ht(x->right);

    x->height = 1 + (left_height > right_height ? left_height : right_height);

    return x;
}

node *insert_node(node *root, int data){
    if (!root) return create_node(data);
    if (root->data > data){
        root->left = insert_node(root->left, data);
    }else if (root->data < data){
        root->right = insert_node(root->right, data);
    }else return root;

    //Height variable
    int left_h = ht(root->left);
    int right_h = ht(root->right);

    root->height = 1 + (left_h > right_h ? left_h : right_h);

    int balance_factor = bf(root);

    //4 Cases.

    //LL 
    if (balance_factor > 1 && data < root->left->data){
        return rotate_right(root);
    }

    //RR
    if (balance_factor < -1 && data > root->right->data){
        return rotate_left(root);
    }

    //LR
    if (balance_factor > 1 && data > root->left->data){
        root->left = rotate_left(root->left);
        return rotate_right(root); //Double rotation, first rotation it tranform LR case in LL
    }

    //RL
    if (balance_factor < -1 && data < root->right->data){
        root->right = rotate_right(root->right);
        return rotate_left(root); //Double rotation, first rotation it tranform RL case in RR
    }

    return root;
}

node *find_min(node *root){
    if (!root) return NULL;
    while (root->left){
        root = root->left;
    }
    return root;
}

node *search_node(node *root, int data){
    if (!root) return NULL;
    if (root->data == data) return root;
    else if (root->data < data){
        return search_node(root->left, data);
    }else {
        return search_node(root->right, data);
    }
}

node *getsuccessor(node *root, int data){
    node *currnode = search_node(root, data);
    if (!currnode){
        return NULL;
    }
    if (currnode->right){ //First cases, if the node have a right subtree we have the successorr
        return find_min(currnode->right);
    }else { //If he don't have it we need to find the first ancestor that have the node in left subtree
            //I'll show to make it clear.
            node *ancestor = root; //Start from root
            node *successor = NULL; //Final result
            while (ancestor != currnode){
                if (currnode->data < ancestor->data){ //If the val of the currnode is lesser that means
                                                      //currnode is in left subtree
                    successor = ancestor; //We assign value (in case is the successor)
                    ancestor = ancestor->left; //and go on and check until the while continue
                }else {
                    ancestor = ancestor->right; //if is not don't do anything in case no left subtree
                                               //or if the currnode have the highest value in the tree (NULL successor)
                }
            }   
            return successor;
        }
}

//Delete a node (Optional)

node *delete_node(node *root, int data){ 
    if (!root) return root;
    if (root->data > data){
        root->left = delete_node(root->left, data);
    }else if (root->data < data){
        root->right = delete_node(root->right, data);
    //We assign recursion to the right and left to not lose the link from the rest of the tree
    //Need to be catious when we remove nodes from the tree or we can mess up
    }else { //3 Cases
        if (!root->left || !root->right){
            node *tmp = root->left ? root->left : root->right;
            if (!tmp){ //If tmp is NULL that means no left or right child
                tmp = root;
                root = NULL;
            }else { //We have 1 child (2 case)
                *root = *tmp;
            }
            free(tmp);
        }else { //We have 2 child (3 case)
            node *tmp = getsuccessor(root, data); //We get successor of our node
            root->data = tmp->data; //Successor value in root
            root->right = delete_node(root->right, data); //Delete the ridondant node
        }
    }

    if (!root) return root; //If the root is NULL case


    //Height variable
    int left_h = ht(root->left);
    int right_h = ht(root->right);

    root->height = 1 + (left_h > right_h ? left_h : right_h);

    int balance_factor = bf(root);

    //4 Cases.

    //LL 
    if (balance_factor > 1 && data < root->left->data){
        return rotate_right(root);
    }

    //RR
    if (balance_factor < -1 && data > root->left->data){
        return rotate_left(root);
    }

    //LR
    if (balance_factor > 1 && data > root->left->data){
        root->left = rotate_left(root->left);
        return rotate_right(root); //Double rotation, first rotation it tranform LR case in LL
    }

    //RL
    if (balance_factor < -1 && data < root->right->data){
        root->right = rotate_right(root->right);
        return rotate_left(root); //Double rotation, first rotation it tranform RL case in RR
    }

    return root;
}

//Other functions like modify specific value (with the right code to not break the bst)
//2 Fondamental algorithms like MinMax check if the bst is a bst or use the inorder algorithm
