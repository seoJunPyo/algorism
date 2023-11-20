#include "LinkedLIst.h"

void L_Create_List(LinkedList** List)
{
	*List = (LinkedList*)malloc(sizeof(LinkedList));
	if (*List != NULL)
	{
		(*List)->Head = NULL;
		(*List)->Tail = NULL;
		(*List)->Count = 0;
	}
}

L_Node* L_Create_Node(int New_Data)
{
	L_Node* New_Node = (L_Node*)malloc(sizeof(L_Node));
	if (New_Node != NULL)
	{
		New_Node->Data = New_Data;
		New_Node->Next_Node = NULL;
		New_Node->Search_Count = 0;
	}

	return New_Node;
}

void L_Destroy_Node(L_Node* Node)
{
	free(Node);
}

void L_Destroy_List(LinkedList* List)
{
	L_Node* Current = List->Head;

	while (Current != NULL)
	{
		L_Node* Temp = Current;
		Current = Current->Next_Node;

		free(Temp);
	}

	free(List);
}

void L_Print_List(LinkedList* List)
{
	L_Node* Current = List->Head;

	while (Current != NULL)
	{
		printf("Data : %d, Count : %d\n", Current->Data, Current->Search_Count);
		Current = Current->Next_Node;
	}
}


void L_Append_Node(LinkedList* List, L_Node* New_Node)
{
	if (List->Head == NULL)
	{
		List->Head = New_Node;
		List->Tail = New_Node;
	}
	else
	{
		List->Tail->Next_Node = New_Node;
		List->Tail = New_Node;
	}

	List->Count++;
}

L_Node* L_Remove_Node(LinkedList* List, L_Node* Target)
{
	L_Node* Current = List->Head;
	
	if (Target == List->Head)
	{
		List->Head = Target->Next_Node;

		return Target;
	}

	while (Current->Next_Node != Target && Current->Next_Node != NULL)
		Current = Current->Next_Node;

	Current->Next_Node = Target->Next_Node;

	if (List->Tail == Target)
		List->Tail = Current;

	Target->Next_Node = NULL;

	return Target;
}

L_Node* L_Sequential_Search(LinkedList* List, int Target)
{
	L_Node* Current = List->Head;
	L_Node* Match = NULL;

	while (Current != NULL)
	{
		if (Current->Data == Target)
		{
			Match = Current;
			break;
		}

		Current = Current->Next_Node;
	}

	return Match;
}

L_Node* L_Move_To_Front(LinkedList* List, int Target)
{
	L_Node* Current = List->Head;
	L_Node* Prev = NULL;
	L_Node* Match = NULL;

	while (Current != NULL)
	{
		if (Current->Data == Target)
		{
			Match = Current;

			if (Prev != NULL)
			{
				Prev->Next_Node = Current->Next_Node;
				
				Current->Next_Node = List->Head;
				List->Head = Current;
			}
			break;
		}
		else
		{
			Prev = Current;
			Current = Current->Next_Node;
		}
	}

	return Match;
}

L_Node* L_Transpose(LinkedList* List, int Target)
{
	L_Node* Current = List->Head;
	L_Node* Prev = NULL;
	L_Node* PPrev = NULL;
	L_Node* Match = NULL;

	while (Current != NULL)
	{
		if (Current->Data == Target)
		{
			Match = Current;

			if (Prev != NULL)
			{
				if (PPrev != NULL)
					PPrev->Next_Node = Current;

				else
					List->Head = Current;

				Prev->Next_Node = Current->Next_Node;
				Current->Next_Node = Prev;
			}
			break;
		}

		PPrev = Prev;
		Prev = Current;
		Current = Current->Next_Node;
	}

	return Match;
}

void L_Insert_Sort_Search_Count(LinkedList* List)
{
	L_Node* Prev = NULL;
	L_Node* Current = List->Head;
	printf("%d\n", List->Head->Data);

	while (Current->Next_Node != NULL)
	{
		if (Current->Search_Count > Current->Next_Node->Search_Count)
		{
			Prev = Current;
			Current = Current->Next_Node;
			continue;
		}

		L_Node* Prev_Compare = NULL;
		L_Node* Compare = List->Head;
		L_Node* Temp = Current->Next_Node;
	

		while (Compare != Current)
		{
			if (Compare->Search_Count < Temp->Search_Count)
			{
				L_Remove_Node(List, Temp);
				L_Insert_Before(List, Compare, Temp);
				break;
			}

			Prev_Compare = Compare;
			Compare = Compare->Next_Node;
		}
		Prev = Temp;
		Current = Temp->Next_Node;
	}
}

L_Node* L_Frequecy_Count(LinkedList* List, int Target)
{
	L_Node* Match = L_Sequential_Search(List, Target);

	if (Match != NULL)
	{
		Match->Search_Count++;
		L_Insert_Sort_Search_Count(List);
	}

	return Match;
}

void L_Insert_Before(LinkedList* List, L_Node* Target, L_Node* New_Node)
{
	L_Node* Prev = NULL;
	L_Node* Current = List->Head;

	if (Target == List->Head)
	{
		printf("--------\n");
		New_Node->Next_Node = Target;
		List->Head = New_Node;
	}
	else
	{
		printf("----\n");
		while (Current->Next_Node != Target && Current->Next_Node != NULL)
		{
			Prev = Current;
			Current = Current->Next_Node;
		}

		if (Prev != NULL)
		{
			Prev->Next_Node = New_Node;
			New_Node->Next_Node = Current;
		}
	}
}