#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tagRBTNode
{
	struct tagRBTNode* Parent;
	struct tagRBTNode* Left;
	struct tagRBTNode* Right;

	enum {RED, BLACK} Color;

	int Data;
} RBT_Node;

RBT_Node* RBT_Create_Node(int Data);
void RBT_Destroy_Node(RBT_Node* Node);
void RBT_Destroy_Tree(RBT_Node* Root);
RBT_Node* RBT_Search_Node(RBT_Node* Root, int Target);
void RBT_Insert_Node(RBT_Node** Tree, RBT_Node* New_Node);
RBT_Node* RBT_Remove_Node(RBT_Node** Root, int Target);
void RBT_Print_Tree(RBT_Node* Tree, int Depth, int Black_Count);