#include "DoublyLinkedList.h"

void DL_Create_List(DoublyLinkList** List)
{
	*List = (DoublyLinkList*)malloc(sizeof(DoublyLinkList));
	if (*List != NULL)
	{
		(*List)->Head = NULL;
		(*List)->Tail = NULL;
		(*List)->Count = 0;
	}
}

void DL_Destroy_List(DoublyLinkList* List)
{
	DL_Node* Current = List->Head;

	while (Current != NULL)
	{
		Current = Current->Next;
		DL_Destroy_Node(Current->Prev);
	}

	free(List);
}

DL_Node* DL_Create_Node(int New_Data)
{
	DL_Node* New_Node = (DL_Node*)malloc(sizeof(DL_Node));
	if (New_Node != NULL)
	{
		New_Node->Data = New_Data;
		New_Node->Next = NULL;
		New_Node->Prev = NULL;
	}

	return New_Node;
}

void DL_Destroy_Node(DL_Node* DL_Node)
{
	free(DL_Node);
}

void DL_Append_Node(DoublyLinkList* List, DL_Node* New_Node)
{
	if (List->Head == NULL)
	{
		List->Head = New_Node;
		List->Tail = New_Node;
	}
	else
	{
		New_Node->Prev = List->Tail;

		List->Tail->Next = New_Node;
		List->Tail = New_Node;
	}

	List->Count++;
}

void DL_Insert_After(DoublyLinkList* List, DL_Node* Target, DL_Node* New_Node)
{
	if (List->Head == Target)
	{
		New_Node->Prev = Target;
		New_Node->Next = Target->Next;

		Target->Next->Prev = New_Node;
		Target->Next = New_Node;

		List->Count++;
	}
	
	else if (List->Tail == Target)
		DL_Append_Node(List, New_Node);
	
	else
	{
		DL_Node* Current = List->Head;

		while (Current != Target && Current != NULL)
			Current = Current->Next;

		if (Current == NULL)
		{
			printf("타겟 노드가 존재하지 않습니다.\n");
			return;
		}

		New_Node->Prev = Current;
		New_Node->Next = Current->Next;

		Current->Next->Prev = New_Node;
		Current->Next = New_Node;

		List->Count++;
	}
}

void DL_Insert_Before(DoublyLinkList* List, DL_Node* Target, DL_Node* New_Node)
{
	if (List->Head == Target)
	{
		New_Node->Next = Target;
		Target->Prev = New_Node;
		List->Head = New_Node;
	}

	else
	{
		DL_Node* Current = List->Head;

		while (Current != Target && Current != NULL)
			Current = Current->Next;

		if (Current == NULL)
		{
			printf("타겟 노드가 존재하지 않습니다.\n");
			return;
		}

		New_Node->Next = Current;
		New_Node->Prev = Current->Prev;

		Current->Prev->Next= New_Node;
		Current->Prev = New_Node;
	}

	List->Count++;
}

void DL_Remove_Node(DoublyLinkList* List, DL_Node* Target)
{
	if (Target == List->Head)
	{
		List->Head = Target->Next;
		Target->Next->Prev = NULL;
	}
	else if (Target == List->Tail)
	{
		List->Tail = Target->Prev;
		Target->Prev->Next = NULL;
	}
	else
	{
		DL_Node* Current = List->Head;

		while (Current != Target && Current != NULL)
			Current = Current->Next;

		if (Current == NULL)
		{
			printf("삭제 타겟 노드가 존재하지 않습니다.\n");
			return;
		}

		Current->Prev->Next = Target->Next;
		Target->Next->Prev = Current->Prev;
	}

	Target->Next = NULL;
	Target->Prev = NULL;

	List->Count--;
}

void DL_Print_List(DoublyLinkList* List)
{
	DL_Node* Current = List->Head;

	while (Current != NULL)
	{
		if (Current->Next == NULL)
			printf("%d", Current->Data);
		else 
			printf("%d -> ", Current->Data);

		Current = Current->Next;
	}


	printf("\n");
}

void DL_Insertion_Sort(DoublyLinkList* List)
{
	DL_Node* Current = List->Head;
	int i = 0;

	while (Current != List->Tail)
	{
		if (Current->Data < Current->Next->Data)
		{
			Current = Current->Next;
			continue;
		}

		DL_Node* Compare = List->Head;
		DL_Node* Temp = Current->Next;

		while (Compare != Temp)
		{
			if (Compare->Data > Temp->Data)
			{
				DL_Remove_Node(List, Temp);
				DL_Insert_Before(List, Compare, Temp);
				break;
			}
			Compare = Compare->Next;
		}
		Current = Temp->Next;
	}
}