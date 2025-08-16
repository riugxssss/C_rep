#ifndef TREES_UTILS_H
#define TREES_UTILS_H

#include <stddef.h>

// Definition of a single tree node
typedef struct TreeNode {
    struct TreeNode *left;   // Pointer to left child
    struct TreeNode *right;  // Pointer to right child
    int data;                // Value stored in the node
} TreeNode;

// Definition of the entire tree structure
typedef struct TreeStruct {
    size_t totnode;          // Total number of nodes in the tree
    struct TreeNode *root;   // Pointer to the root node
} TreeStruct;

// General macros for common values and boolean flags
typedef enum GeneralMacros {
    EMPTY = -1,              // Represents an empty value
    INITVAR = 666,           // Initial/default variable value
    TRUE = 1,                // Boolean true
    FALSE = 0                // Boolean false
} GeneralMacros;

// Private function attribute for internal use
#define Private __attribute__((visibility("hidden")))

// Color macros for terminal output
#define RED "\033[1;31m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"

// Function prototypes

// Tree creation
TreeStruct *Create_Tree(void);      // Create an empty tree
TreeNode *Create_tNode(int val);    // Create a new tree node with value

// BST operations
void insertTreeNode(TreeStruct *stree, int data); // Insert value into BST
TreeNode *SearchNode(TreeNode *root, int data);   // Search for a node
TreeNode *Delete_Node(TreeNode *root, int data); // Delete a node
void Modify_Value(TreeNode *root);                // Modify a node's value

// Tree printing / traversal
void Print_Tree(TreeNode *root);                 // Print tree inorder
void Depth_PreOrder(TreeNode *root);            // Preorder traversal
void Depth_InOrder(TreeNode *root);             // Inorder traversal
void Depth_PostOrder(TreeNode *root);           // Postorder traversal
void Level_Order_Traversal(TreeStruct *treeptr);// Breadth-first traversal

// Memory management
void Free_Tree(TreeNode *root);                 // Free tree recursively
void Free_TreeNoRec(TreeNode *root);           // Free tree iteratively

// Tree queries
int Find_hTree(TreeNode *root);                 // Find tree height
TreeNode *Find_Max(TreeNode *root);            // Find maximum value node
TreeNode *Find_Min(TreeNode *root);            // Find minimum value node

// BST validation
Private int CheckTheTree(TreeNode *root, int *prev); // Internal inorder check
int IsaBSTInOrder(TreeNode *root);                  // Check if tree is BST (inorder)
Private int MinMaxCheck(TreeNode *root, int min, int max); // Internal min/max check
int IsaBSTMinMax(TreeNode *root);                  // Check if tree is BST (min/max)

#endif
