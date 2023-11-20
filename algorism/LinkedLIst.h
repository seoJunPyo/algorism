#include <stdlib.h>
#include <stdio.h>

typedef struct tagLLNode
{
	int Data;
	int Search_Count;
	struct tagLLNode* Next_Node;
} L_Node;

typedef struct tagLL
{
	L_Node* Head;
	L_Node* Tail;
	int Count;
} LinkedList;

void L_Create_List(LinkedList** List);
L_Node* L_Create_Node(int New_Data);
void L_Destroy_Node(L_Node* Node);
void L_Destroy_List(LinkedList* List);
void L_Print_List(LinkedList* List);
void L_Append_Node(LinkedList* List, L_Node* New_Node);
L_Node* L_Remove_Node(LinkedList* List, L_Node* Target);
L_Node* L_Sequential_Search(LinkedList* List, int Target);
L_Node* L_Move_To_Front(LinkedList* List, int Target);
L_Node* L_Transpose(LinkedList* List, int Target);
L_Node* L_Frequecy_Count(LinkedList* List, int Target);
void L_Insert_Before(LinkedList* List, L_Node* Target, L_Node* New_Node);