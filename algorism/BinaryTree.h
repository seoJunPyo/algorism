#include <stdio.h>
#include <stdlib.h>

typedef struct tagTreeNode
{
	int Data;
	struct tagTreeNode* Left;
	struct tagTreeNode* Right;
} BST_Node;


BST_Node* BST_Create_Node(int Data);
void BST_Destroy_Node(BST_Node* Node);
void BST_Destroy_Tree(BST_Node* Node);
BST_Node* BST_Search_Node(BST_Node* Tree, int Target);
void BST_Insert_Node(BST_Node* Tree, BST_Node* Child);
BST_Node* BST_Search_Min_Node(BST_Node* Tree);
BST_Node* BST_Remove_Node(BST_Node* Tree, BST_Node* Parent, int Target);
void BST_Inorder_Print_Tree(BST_Node* Tree);