#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode
{
	struct tagNode* Prev;
	struct tagNode* Next;
	int Data;
} Node;

typedef struct tagList
{
	Node* Head;
	Node* Tail;
	int Count;
} DoublyLinkList;

void DL_Create_List(DoublyLinkList** List);
void DL_Destroy_List(DoublyLinkList* List);
Node* DL_Create_Node(int New_Data);
void DL_Destroy_Node(Node* Node);
void DL_Append_Node(DoublyLinkList* List, Node* New_Node);
void DL_Insert_After(DoublyLinkList* List, Node* Target, Node* New_Node);
void DL_Insert_Before(DoublyLinkList* List, Node* Target, Node* New_Node);
void DL_Remove_Node(DoublyLinkList* List, Node* Target);
void DL_Print_List(DoublyLinkList* List);
void DL_Insertion_Sort(DoublyLinkList* List);