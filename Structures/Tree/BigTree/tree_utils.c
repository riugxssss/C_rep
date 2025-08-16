#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "tree_utils.h"
#include "queue_utils.h"


TreeStruct *Create_Tree(){
    TreeStruct *newtree = malloc(sizeof(*newtree));
    if (!newtree){
        fatalAlloc("Create_Tree"); // handle memory allocation failure
    }

    newtree->root = NULL; // initially tree is empty
    newtree->totnode = INITVAR; // set total node count
    return newtree;
}


TreeNode *Create_tNode (int val){
    TreeNode *newn = malloc(sizeof(*newn));
    if (!newn){
        fatalAlloc("Create_tNode"); // handle memory allocation failure
    }

    newn->left = newn->right = NULL; // new node has no children
    newn->data = val;

    return newn;
}

void insertTreeNode(TreeStruct *stree, int data){
    if (!stree->root){
        stree->root = Create_tNode(data); // first node becomes root
        stree->totnode++;
        return;
    }

    TreeNode *curr = stree->root;
    while (TRUE){
        if (data > curr->data){
            if (!curr->right){
                curr->right = Create_tNode(data); // insert to the right
                stree->totnode++;
                break;
            }
            curr = curr->right;
        } else if (data < curr->data){
            if (!curr->left){
                curr->left = Create_tNode(data); // insert to the left
                stree->totnode++;
                break;
            }
            curr = curr->left;
        } else break; // duplicate value, do nothing
    }
    printf("Value inserted successfully\n");
}

TreeNode *SearchNode(TreeNode *root, int data){
    if (!root) return NULL;
    if (root->data == data) return root; // found the node
    else if (data < root->data) return SearchNode(root->left, data); // search left subtree
    else return SearchNode(root->right, data); // search right subtree
}

void Print_Tree(TreeNode *root){
    if (!root){
        printf("\nThe Tree is empty\n\n");
        return;
    }
    Print_Tree(root->left); // visit left subtree
    printf("%d\n", root->data); // print current node
    Print_Tree(root->right); // visit right subtree
}

void Free_Tree(TreeNode *root){
    if (!root){
        return;
    }
    Free_Tree(root->left);
    Free_Tree(root->right);
    free(root); // recursively free all nodes
}

void Free_TreeNoRec(TreeNode *root){
    if (!root){
        printf(RED"\nThe Tree is empty\n" RESET);
        return;
    }

    QueueStruct *queueptr = Create_Queue();
    EnqueueNode(queueptr, root); // start BFS

    while (!IsEmpty(queueptr)){
        TreeNode *curr = DequeueNode(queueptr);
        if (curr->left) EnqueueNode(queueptr, curr->left);
        if (curr->right) EnqueueNode(queueptr, curr->right);
        free(curr); // free node after visiting
    }

    Free_Queue(queueptr);
}

int Find_hTree(TreeNode *root){
    if (!root) return EMPTY; // empty tree
    int left_h = Find_hTree(root->left);
    int right_t = Find_hTree(root->right);
    return 1 + (left_h > right_t ? left_h : right_t); // height = 1 + max(left, right)
}

TreeNode *Find_Max(TreeNode *root){   
    if (!root){
        return NULL;
    }
    while (root->right){ // go as far right as possible
        root = root->right;
    }
    return root;
}

TreeNode *Find_Min(TreeNode *root){
    if (!root){
        return NULL;
    }
    while (root->left){ // go as far left as possible
        root = root->left;
    }
    return root;
}

void Depth_PreOrder(TreeNode *root){
    if (!root){
        return;
    }
    printf("%d\n", root->data); // visit root
    Depth_PreOrder(root->left); // visit left subtree
    Depth_PreOrder(root->right); // visit right subtree
}

void Depth_InOrder(TreeNode *root){
    if (!root){
        return;
    }
    Depth_InOrder(root->left);
    printf("%d\n", root->data); // visit root
    Depth_InOrder(root->right);
}

void Depth_PostOrder(TreeNode *root){
    if (!root){
        return;
    }
    Depth_PostOrder(root->left);
    Depth_PostOrder(root->right);
    printf("%d\n", root->data); // visit root last
}

//Inorder check, is a bst check that act like an Inorder print
// <L> <D> <R> a depth first strategies
Private int CheckTheTree(TreeNode *root, int *prev){
    if (!root) return TRUE;
    if (!CheckTheTree(root->left, prev)) return FALSE;
    if (root->data < *prev) return FALSE; // violates BST property
    *prev = root->data;
    return CheckTheTree(root->right, prev);
}

int IsaBSTInOrder(TreeNode *root){
    int prev = INT_MIN;
    return CheckTheTree(root, &prev);
}

//Min Max check if the tree is a bst or not
//using 2 local var like min and max to check every node with a confront
Private int MinMaxCheck(TreeNode *root, int min, int max){
    if (!root) return TRUE;
    if (root->data < min || root->data > max) return FALSE; // violates BST property
    return MinMaxCheck(root->left, min, root->data) &&
           MinMaxCheck(root->right, root->data, max);
}

int IsaBSTMinMax(TreeNode *root){
    return MinMaxCheck(root, INT_MIN, INT_MAX);
}

TreeNode *GetSuccessor(TreeNode *root, int data){
    //Search the node O(h)
    TreeNode *curr = SearchNode(root, data);
    if (!curr) return NULL;
    if (curr->right){
        return Find_Min(curr->right); //Case 1 node has the right subtree
    
    }else { //Case 2 no right subtree
        TreeNode *ancestor = root;
        TreeNode *successor = NULL;
        while (ancestor != curr){
            if (curr->data < ancestor->data){
                successor = ancestor;
                ancestor = ancestor->left;
            }else {
                ancestor = ancestor->right; //if the curr->node is greater than root the node is in the
                                            //root right subtree
            } 
        }
        return successor;
    }
}

// Delete a node from BST
TreeNode *Delete_Node(TreeNode *root, int data){
    if (!root) return root;

    if (data < root->data) root->left = Delete_Node(root->left, data);
    else if (data > root->data) root->right = Delete_Node(root->right, data);
    else { // node found
        TreeNode *tmp;
        if (!root->left && !root->right){ // leaf node
            free(root);
            root = NULL;
        } else if (!root->left){ // only right child
            tmp = root;
            root = root->right;
            free(tmp);
        } else if (!root->right){ // only left child
            tmp = root;
            root = root->left;
            free(tmp);
        } else { // two children
            tmp = GetSuccessor(root, root->data);
            root->data = tmp->data; // replace data
            root->right = Delete_Node(root->right, tmp->data); // delete successor
        }
    }
    printf("Node deleted with success\n");
    return root;
}

// Modify node value safely
void Modify_Value(TreeNode *root){
    int dataTosearch = INITVAR;
    printf("Enter the node value you want to search: ");
    int check = scanf("%d", &dataTosearch);
    if (!check){
        fprintf(stderr, "[Error Msg] The value you entered is not a integer\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    TreeNode *tmp = SearchNode(root, dataTosearch);
    if (!tmp){
        printf("The value is not in the tree..\n");
        return;
    }

    int saved = tmp->data;
    int newvalue = INITVAR;

    printf("The node with that value exits\n");
    printf("Enter the new value: ");
    int check2 = scanf("%d", &newvalue);
    if (!check2){
        fprintf(stderr, "[Error Msg] The value you entered is not a integer\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    tmp->data = newvalue;
    if (!IsaBSTInOrder(root)){ // check if BST property is maintained
        fprintf(stderr, "[Error Msg] The value you entered break the BST\n");
        tmp->data = saved; // revert if violated
        return;
    }
    printf("Value updated succesfully!\n");
}

// Level order traversal (BFS)
void Level_Order_Traversal(TreeStruct *treeptr){
    if (!treeptr || !treeptr->root){
        printf("EMPTY ROOT / TREE STRUCT\n");
        return;
    }
    int count = INITVAR;
    QueueStruct *queueptr = Create_Queue();
    EnqueueNode(queueptr, treeptr->root); // start BFS

    while(!IsEmpty(queueptr)){
        TreeNode *tmp = DequeueNode(queueptr);
        printf("Node value N[%d]: %d\n", count++, tmp->data);
        if (tmp->left) EnqueueNode(queueptr, tmp->left);
        if (tmp->right) EnqueueNode(queueptr, tmp->right);
    }
    Free_Queue(queueptr); // free queue after use
}
