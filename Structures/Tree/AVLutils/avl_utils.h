#ifndef AVL_UTILS_H
#define AVL_UTILS_H

typedef struct node node;
typedef enum Macros macro_t;

#define private __attribute__((visibility("hidden")))

node *create_node(int data);
void print_AVL(node *root);
void free_tree(node *root);
int ht(node *root);
int balance_factor(node *root);
node *find_min(node *root);
node *getsuccessor(node *root, int data);
node *delete_node(node *root, int data);
node *insert_node(node *root, int data);


#endif
