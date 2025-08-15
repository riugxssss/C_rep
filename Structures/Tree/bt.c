#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *left;
    struct node *right;
    int data;
}node;

typedef struct tree {
    size_t totnode;
    struct node *root;
}tree;

tree *create_tree(){
    tree *newtree = malloc(sizeof(*newtree));
    if (!newtree){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }

    newtree->root = NULL;
    newtree->totnode = 0;
    return newtree;
}


node *create_node (int val){
    node *newn = malloc(sizeof(*newn));
    if (!newn){
        fprintf(stderr, "[!] Out of memory\n");
        exit(EXIT_FAILURE);
    }

    newn->left = newn->right = NULL;
    newn->data = val;

    return newn;
}

void insert(tree *stree, int data){
    if (!stree->root){
        stree->root = create_node(data);
        stree->totnode++;
        return;
    }
    node *curr = stree->root;
    while (1){
        if (data > curr->data){
            if (!curr->right){
                curr->right = create_node(data);
                stree->totnode++;
                break;
            }
            curr = curr->right;
        }else if (data < curr->data){
            if (!curr->left){
                curr->left = create_node(data);
                stree->totnode++;
                break;
            }
            curr = curr->left;
        }else break;
    }
}

int search(node *root, int data){
    if (!root) return 0;
    if (root->data == data) return 1;
    else if (data < root->data) return search(root->left, data);
    else return search(root->right, data);
}

void print_all(node *root){
    if (!root) return;
    print_all(root->left);
    printf("%d\n", root->data);
    print_all(root->right);
}

void free_tree(node *root){
    if (!root){
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);

}

int find_treeh(node *root){
    if (!root) return -1; //empty tree;
    int left_h = find_treeh(root->left);
    int right_t = find_treeh(root->right);
    return 1 + (left_h > right_t ? left_h : right_t);
}

int find_max(node *root){   
    if (!root){
        return -1;
    }
    while (root->right){
        root = root->right;
    }
    return root->data;
}

int find_min(node *root){
    if (!root){
        return -1;
    }
    while (root->left){
        root = root->left;
    }
    return root->data;
}

void depth_preorder(node *root){
    if (!root) return;
    printf("%d\n", root->data);
    depth_preorder(root->left);
    depth_preorder(root->right);
}
void depth_inorder(node *root){
     if (!root) return;
    depth_inorder(root->left);
    printf("%d\n", root->data);
    depth_inorder(root->right);
}
void depth_postorder(node *root){
    if (!root) return;
    depth_postorder(root->left);
    depth_postorder(root->right);
    printf("%d\n", root->data);
}

int main(void){

    tree *stree = create_tree();
    insert(stree, 67);
    insert(stree, 3);
    insert(stree, 87);
    insert(stree, 85);
    insert(stree, 7);
    insert(stree, 1);

    depth_preorder(stree->root);
    free_tree(stree->root);
    free(stree);

    return 0;
}
