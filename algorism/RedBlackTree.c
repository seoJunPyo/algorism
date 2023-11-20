#include "RedBlackTree.h"

void RBT_Insert_Node_Helper(RBT_Node** Tree, RBT_Node* New_Node);
void RBT_Rebuild_After_Insert(RBT_Node** Root, RBT_Node* X);
void RBT_Rebuild_After_Remove(RBT_Node** Root, RBT_Node* Successor);
void RBT_Rotate_Right(RBT_Node** Root, RBT_Node* Parent);
void RBT_Rotate_Left(RBT_Node** Root, RBT_Node* Parent);
RBT_Node* RBT_Search_Min_Node(RBT_Node* Tree);

extern RBT_Node* Nil;

RBT_Node* RBT_Create_Node(int Data)
{
	RBT_Node* New_Node = (RBT_Node*)malloc(sizeof(RBT_Node));
	if (New_Node != NULL)
	{
		New_Node->Data = Data;
		New_Node->Parent = NULL;
		New_Node->Right = NULL;
		New_Node->Left = NULL;
		New_Node->Color = BLACK;
	}

	return New_Node;
}

void RBT_Destroy_Node(RBT_Node* Node)
{
	free(Node);
}

void RBT_Destroy_Tree(RBT_Node* Root)
{
	if (Root->Left != Nil)
		RBT_Destroy_Tree(Root->Left);

	if (Root->Right != Nil)
		RBT_Destroy_Node(Root->Right);

	Root->Right = Nil;
	Root->Left = Nil;

	RBT_Destroy_Node(Root);
}

void RBT_Rotate_Right(RBT_Node** Root, RBT_Node* Parent)
{	
	RBT_Node* Left_Child = Parent->Left;

	Parent->Left = Left_Child->Right;

	if (Left_Child->Right != Nil)
		Left_Child->Right->Parent = Parent;

	Left_Child->Parent = Parent->Parent;

	if (Parent == (*Root))
		(*Root) = Left_Child;
	else
	{
		if (Parent->Parent->Left == Parent)
			Parent->Parent->Left = Left_Child;
		else
			Parent->Parent->Right = Left_Child;
	}

	Left_Child->Right = Parent;
	Parent->Parent = Left_Child;
}

void RBT_Rotate_Left(RBT_Node** Root, RBT_Node* Parent)
{
	RBT_Node* Right_Child = Parent->Right;

	Parent->Right = Right_Child->Left;

	if (Right_Child->Left != Nil)
		Right_Child->Left->Parent = Parent;

	Right_Child->Parent = Parent->Parent;

	if (Parent == (*Root))
		(*Root) = Right_Child;
	else
	{
		if (Parent->Parent->Left == Parent)
			Parent->Parent->Left = Right_Child;
		else
			Parent->Parent->Right = Right_Child;
	}

	Right_Child->Left = Parent;
	Parent->Parent = Right_Child;
}

RBT_Node* RBT_Search_Node(RBT_Node* Root, int Target)
{
	if (Root == Nil)
		return  NULL;

	if (Root->Data > Target)
		return RBT_Search_Node(Root->Left, Target);

	else if (Root->Data < Target)
		return RBT_Search_Node(Root->Right, Target);

	else
		return Root;
}

RBT_Node* RBT_Search_Min_Node(RBT_Node* Tree)
{
	if (Tree == Nil)
		return NULL;

	if (Tree->Left != Nil)
		return RBT_Search_Min_Node(Tree->Left);
	else
		return Tree;
}

void RBT_Insert_Node_Helper(RBT_Node** Tree, RBT_Node* New_Node)
{
	if ((*Tree) == NULL)
		(*Tree) = New_Node;

	if ((*Tree)->Data > New_Node->Data)
	{
		if ((*Tree)->Left == Nil)
		{
			(*Tree)->Left = New_Node;
			New_Node->Parent = (*Tree);
		}
		else
			RBT_Insert_Node_Helper(&(*Tree)->Left, New_Node);
	}
	else if ((*Tree)->Data < New_Node->Data)
	{
		if ((*Tree)->Right == Nil)
		{
			(*Tree)->Right = New_Node;
			New_Node->Parent = (*Tree);
		}
		else
			RBT_Insert_Node_Helper(&(*Tree)->Right, New_Node);
	}
}

void RBT_Insert_Node(RBT_Node** Tree, RBT_Node* New_Node)
{
	RBT_Insert_Node_Helper(Tree, New_Node);

	New_Node->Color = RED;
	New_Node->Left = Nil;
	New_Node->Right = Nil;

	RBT_Rebuild_After_Insert(Tree, New_Node);
}

void RBT_Rebuild_After_Insert(RBT_Node** Root, RBT_Node* X)
{
	while (X != (*Root) && X->Parent->Color == RED)
	{
		if (X->Parent = X->Parent->Parent->Left)
		{
			RBT_Node* Uncle = X->Parent->Parent->Right;
			if (Uncle->Color == RED)
			{
				X->Parent->Color = BLACK;
				Uncle->Color = BLACK;
				X->Parent->Parent->Color = RED;

				X = X->Parent->Parent;
			}
			else
			{
				if (X = X->Parent->Right)
				{
					X = X->Parent;
					RBT_Rotate_Left(Root, X);
				}

				X->Parent->Color = BLACK;
				X->Parent->Parent->Color = RED;
				RBT_Rotate_Right(Root, X->Parent->Parent);
			}
		}
		else
		{
			RBT_Node* Uncle = X->Parent->Parent->Left;
			if (Uncle->Color == RED)
			{
				X->Parent->Color = BLACK;
				Uncle->Color = BLACK;
				X->Parent->Parent->Color = RED;

				X = X->Parent->Parent;
			}
			else
			{
				if (X = X->Parent->Left)
				{
					X = X->Parent;
					RBT_Rotate_Right(Root, X);
				}

				X->Parent->Color = BLACK;
				X->Parent->Parent->Color = RED;
				RBT_Rotate_Left(Root, X->Parent->Parent);
			}

		}
	}

	(*Root)->Color = BLACK;
}

void RBT_Rebuild_After_Remove(RBT_Node** Root, RBT_Node* Successor)
{
	RBT_Node* Sibling = NULL;

	while (Successor->Parent != NULL && Successor->Color == BLACK)
	{
		if (Successor == Successor->Parent->Left)
		{
			Sibling = Successor->Parent->Right;
			if (Sibling->Color == RED)
			{
				Sibling->Color = BLACK;
				Successor->Parent->Color = RED;
				RBT_Rotate_Left(Root, Successor->Parent);
			}
			else
			{
				if (Sibling->Left->Color == BLACK && Sibling->Right->Color == BLACK)
				{
					Sibling->Color = RED;
					Successor = Successor->Parent;
				}
				else
				{
					if (Sibling->Left->Color == RED)
					{
						Sibling->Left->Color = BLACK;
						Sibling->Color = RED;

						RBT_Rotate_Right(Root, Sibling);
						Sibling = Successor->Parent->Right;
					}

					Sibling->Color = Successor->Parent->Color;
					Successor->Parent->Color = BLACK;
					Sibling->Right->Color = BLACK;
					RBT_Rotate_Left(Root, Successor->Parent);
					Successor = (*Root);
				}
			}
		}
		else
		{
			Sibling = Successor->Parent->Left;
			if (Sibling->Color == RED)
			{
				Sibling->Color = BLACK;
				Successor->Parent->Color = RED;
				RBT_Rotate_Right(Root, Successor->Parent);
			}
			else
			{
				if (Sibling->Right->Color == BLACK && Sibling->Left->Color == BLACK)
				{
					Sibling->Color = RED;
					Successor = Successor->Parent;
				}
				else
				{
					if (Sibling->Right->Color == RED)
					{
						Sibling->Right->Color = BLACK;
						Sibling->Color = RED;

						RBT_Rotate_Left(Root, Sibling);
						Sibling = Successor->Parent->Left;
					}

					Sibling->Color = Successor->Parent->Color;
					Successor->Parent->Color = BLACK;
					Sibling->Left->Color = BLACK;
					RBT_Rotate_Right(Root, Successor->Parent);
					Successor = (*Root);
				}
			}
		}
	}

	Successor->Color = BLACK;
}

RBT_Node* RBT_Remove_Node(RBT_Node** Root, int Target)
{
	RBT_Node* Removed = NULL;
	RBT_Node* Successor = NULL;
	RBT_Node* Target_Node = RBT_Search_Node((*Root), Target);

	if (Target_Node == NULL)
		return NULL;

	if (Target_Node->Left == Nil || Target_Node->Right == Nil)
		Removed = Target_Node;
	else
	{
		Removed = RBT_Search_Min_Node(Target_Node->Right);
		Target_Node->Data = Removed->Data;
	}

	if (Removed->Left != Nil)
		Successor = Removed->Left;
	else
		Successor = Removed->Right;

	Successor->Parent = Removed->Parent;

	if (Removed->Parent = NULL)
		(*Root) = Successor;
	else
	{
		if (Removed == Removed->Parent->Left)
			Removed->Parent->Left = Successor;
		else
			Removed->Parent->Right = Successor;
	}

	if (Removed->Color == BLACK)
		RBT_Rebuild_After_Remove(Root, Successor);

	return Removed;
}

void RBT_Print_Tree(RBT_Node* Tree, int Depth, int Black_Count)
{
	int i = 0;
	char c = 'X';
	int v = -1;
	char cnt[100];

	if (Tree == NULL || Tree == Nil)
		return;

	if (Tree->Color == BLACK)
		Black_Count++;

	if (Tree->Parent != NULL)
	{
		v = Tree->Parent->Data;

		if (Tree->Parent->Left == Tree)
			c = 'L';
		else
			c = 'R';
	}

	if (Tree->Left == Nil && Tree->Right == Nil)
		sprintf_s(cnt, sizeof(cnt), "------------%d", Black_Count);
	else
		strncpy_s(cnt, 1, "", sizeof(cnt));

	for (i = 0; i < Depth; i++)
		printf(" ");

	printf("%d %s [%c %d] %s\n", Tree->Data, Tree->Color == RED ? "RED" : "BLACK", c, v, cnt);

	RBT_Print_Tree(Tree->Left, Depth + 1, Black_Count);
	RBT_Print_Tree(Tree->Right, Depth + 1, Black_Count);
}