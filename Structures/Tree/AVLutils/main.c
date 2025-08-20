#include <stdio.h>
#include "avl_utils.h"

int main(void){

    node *root = NULL;
    root = insert_node(root, 3);
    root = insert_node(root, 1);
    root = insert_node(root, 5);
    root = insert_node(root, 7);
    print_AVL(root);
    free_tree(root);

    return 0;
}
