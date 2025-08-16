#include <stdio.h>
#include <stdlib.h>
#include "tree_utils.h"

int main(void){
    TreeStruct *stree = Create_Tree(); // Create an empty BST
    int choice, value;

    while (1){
        // Print menu
        printf(WHITE"\n=== BST Menu ===\n" RESET);
        printf(RED"1. "WHITE"Insert node\n" RESET);
        printf(RED"2. "WHITE"Delete node\n" RESET);
        printf(RED"3. "WHITE"Modify node value\n" RESET);
        printf(RED"4. "WHITE"Search node\n" RESET);
        printf(RED"5. "WHITE"Print Preorder\n" RESET);
        printf(RED"6. "WHITE"Print Inorder\n" RESET);
        printf(RED"7. "WHITE"Print Postorder\n" RESET);
        printf(RED"8. "WHITE"Print all (Inorder)\n" RESET);
        printf(RED"9. "WHITE"Check if BST\n" RESET);
        printf(RED"10. "WHITE"Find min/max\n" RESET);
        printf(RED"11. "WHITE"Tree height\n" RESET);
        printf(RED"12. "WHITE"Level Order\n" RESET);
        printf(RED"0. "WHITE"Exit\n" RESET);
        printf("Choice: ");

        // Validate input
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input\n");
            while(getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                if (scanf("%d", &value) == 1){
                    insertTreeNode(stree, value); // Insert node into BST
                }
                while(getchar() != '\n');
                break;

            case 2:
                printf("Enter value to delete: ");
                if (scanf("%d", &value) == 1){
                    stree->root = Delete_Node(stree->root, value); // Delete node from BST
                }
                while(getchar() != '\n');
                break;

            case 3:
                Modify_Value(stree->root); // Modify a node value
                break;

            case 4:
                printf("Enter value to search: ");
                if (scanf("%d", &value) == 1){
                    TreeNode *res = SearchNode(stree->root, value); // Search node
                    if (res) printf("Found node with value: %d\n", res->data);
                    else printf("Value not found in tree\n");
                }
                while(getchar() != '\n');
                break;

            case 5:
                printf("Preorder traversal:\n");
                Depth_PreOrder(stree->root); // Print nodes in preorder
                break;

            case 6:
                printf("Inorder traversal:\n");
                Depth_InOrder(stree->root); // Print nodes in inorder
                break;

            case 7:
                printf("Postorder traversal:\n");
                Depth_PostOrder(stree->root); // Print nodes in postorder
                break;

            case 8:
                printf("All nodes (Inorder print):\n");
                Print_Tree(stree->root); // Print entire tree
                break;

            case 9:
                printf("BST check: %s\n", IsaBSTMinMax(stree->root) ? "Yes" : "No"); // Validate BST
                break;

            case 10: {
                TreeNode *minNode = Find_Min(stree->root);
                TreeNode *maxNode = Find_Max(stree->root); // Find min and max
                if (minNode) printf("Min: %d\n", minNode->data);
                if (maxNode) printf("Max: %d\n", maxNode->data);
                break;
            }

            case 11:
                printf("Tree height: %d\n", Find_hTree(stree->root)); // Height of tree
                break;

            case 12:
                printf("Breadth-First (Level order): \n");
                Level_Order_Traversal(stree); // Level-order traversal
                break;

            case 0:
                Free_TreeNoRec(stree->root); // Free memory without recursion
                free(stree);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice\n");
                break;
        }
    }
}
