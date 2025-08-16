#ifndef TREES_UTILS_H
#define TREES_UTILS_H

#include <stddef.h>

// Definition of a single tree node
typedef struct TreeNode {
    struct TreeNode *left;   
    struct TreeNode *right;  
    int data;                
} TreeNode;

// Definition of the entire tree structure
typedef struct TreeStruct {
    size_t totnode;          
    struct TreeNode *root;   
} TreeStruct;

// General macros for common values and boolean flags
typedef enum GeneralMacros {
    EMPTY = -1,              
    INITVAR = 666,           
    TRUE = 1,                
    FALSE = 0                
} GeneralMacros;

// Private function attribute for internal use
#define Private __attribute__((visibility("hidden")))

// Color macros for terminal output
#define RED "\033[1;31m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"


// Tree creation
TreeStruct *Create_Tree(void);      
TreeNode *Create_tNode(int val);    

// BST operations
void insertTreeNode(TreeStruct *stree, int data); 
TreeNode *SearchNode(TreeNode *root, int data);  
TreeNode *Delete_Node(TreeNode *root, int data);
void Modify_Value(TreeNode *root);              

// Tree printing / traversal
void Print_Tree(TreeNode *root);               
void Depth_PreOrder(TreeNode *root);            
void Depth_InOrder(TreeNode *root);             
void Depth_PostOrder(TreeNode *root);           
void Level_Order_Traversal(TreeStruct *treeptr);
TreeNode *GetSuccessor(TreeNode *root, int data);

// Memory management
void Free_Tree(TreeNode *root);                 
void Free_TreeNoRec(TreeNode *root);           

// Tree queries
int Find_hTree(TreeNode *root);                 
TreeNode *Find_Max(TreeNode *root);            
TreeNode *Find_Min(TreeNode *root);        

// BST validation
Private int CheckTheTree(TreeNode *root, int *prev); 
int IsaBSTInOrder(TreeNode *root);                  
Private int MinMaxCheck(TreeNode *root, int min, int max); 
int IsaBSTMinMax(TreeNode *root);                  

#endif
