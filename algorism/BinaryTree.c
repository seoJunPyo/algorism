#include "BinaryTree.h"

BST_Node* BST_Create_Node(int Data)
{
	BST_Node* New_Node = (BST_Node*)malloc(sizeof(BST_Node));
	if (New_Node != NULL)
	{
		New_Node->Data = Data;
		New_Node->Left = NULL;
		New_Node->Right = NULL;
	}

	return New_Node;
}

void BST_Destroy_Node(BST_Node* Node)
{
	free(Node);
}


void BST_Destroy_Tree(BST_Node* Tree)
{
	if (Tree->Left != NULL)
		BST_Destroy_Tree(Tree->Left);

	if (Tree->Right != NULL)
		BST_Destroy_Tree(Tree->Right);

	Tree->Right = NULL;
	Tree->Left = NULL;

	BST_Destroy_Node(Tree);
}

BST_Node* BST_Search_Node(BST_Node* Tree, int Target)
{
	if (Tree == NULL)
		return NULL;

	if (Tree->Data > Target)
		return BST_Search_Node(Tree->Left, Target);
	else if (Tree->Data < Target)
		return BST_Search_Node(Tree->Right, Target);
	else
		return Tree;
}

void BST_Insert_Node(BST_Node* Tree, BST_Node* Child)
{
	if (Tree->Data > Child->Data)
	{
		if (Tree->Left == NULL)
			Tree->Left = Child;
		else
			BST_Insert_Node(Tree->Left, Child);
	}

	if (Tree->Data < Child->Data)
	{
		if (Tree->Right == NULL)
			Tree->Right = Child;
		else
			BST_Insert_Node(Tree->Right, Child);
	}
}

BST_Node* BST_Search_Min_Node(BST_Node* Tree)
{
	if (Tree == NULL)
		return NULL;

	if (Tree->Left == NULL)
		return Tree;
	else
		return BST_Search_Min_Node(Tree->Left);
}

BST_Node* BST_Remove_Node(BST_Node* Tree, BST_Node * Parent, int Target)
{
	BST_Node* Removed = NULL;

	if (Tree == NULL)
		return NULL;
		
	if (Tree->Data > Target)
		BST_Remove_Node(Tree->Left, Tree, Target);
	else if (Tree->Data < Target)
		BST_Remove_Node(Tree->Right, Tree, Target);
	else
	{
		Removed = Tree;

		if (Tree->Left == NULL && Tree->Right == NULL)
		{
			if (Parent->Left == Tree)
				Parent->Left = NULL;
			else
				Parent->Right = NULL;
		}

		else
		{
			if (Tree->Left != NULL && Tree->Right != NULL)
			{
				BST_Node* Min_Node = BST_Search_Min_Node(Tree->Right);
				Min_Node = BST_Remove_Node(Tree, NULL, Min_Node->Data);
				Tree->Data = Min_Node->Data;
			}
			else
			{
				BST_Node* Temp = NULL;
				Temp = Tree->Left != NULL ? Tree->Left : Tree->Right;

				if (Parent->Left == Tree)
					Parent->Left = Temp;
				else
					Parent->Right = Temp;
			}
		}
	}

	return Removed;
}

void BST_Inorder_Print_Tree(BST_Node* Tree)
{
	if (Tree == NULL)
		return;

	BST_Inorder_Print_Tree(Tree->Left);
	printf("%d ", Tree->Data);
	BST_Inorder_Print_Tree(Tree->Right);
}