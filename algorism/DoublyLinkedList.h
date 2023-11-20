#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode
{
	struct tagNode* Prev;
	struct tagNode* Next;
	int Data;
} DL_Node;

typedef struct tagList
{
	DL_Node* Head;
	DL_Node* Tail;
	int Count;
} DoublyLinkList;

void DL_Create_List(DoublyLinkList** List);
void DL_Destroy_List(DoublyLinkList* List);
DL_Node* DL_Create_Node(int New_Data);
void DL_Destroy_Node(DL_Node* Node);
void DL_Append_Node(DoublyLinkList* List, DL_Node* New_Node);
void DL_Insert_After(DoublyLinkList* List, DL_Node* Target, DL_Node* New_Node);
void DL_Insert_Before(DoublyLinkList* List, DL_Node* Target, DL_Node* New_Node);
void DL_Remove_Node(DoublyLinkList* List, DL_Node* Target);
void DL_Print_List(DoublyLinkList* List);
void DL_Insertion_Sort(DoublyLinkList* List);