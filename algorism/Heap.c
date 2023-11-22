#include "Heap.h"

Heap* HEAP_Creat(int Capacity)
{
	Heap* New_Heap = (Heap*)malloc(sizeof(Heap));
	if (New_Heap != NULL)
	{
		New_Heap->Nodes = (Heap_Node*)malloc(sizeof(Heap_Node) * Capacity);
		New_Heap->Capacity = Capacity;
		New_Heap->UsedSize = 0;
	}

	return New_Heap;
}

void HEAP_Destroy(Heap* H)
{
	free(H->Nodes);
	free(H);
}

int HEAP_GetParent(int Pos)
{
	return (Pos - 1) / 2;
}

int HEAP_Get_Left_Child(int Pos)
{
	return Pos * 2 + 1;
}

void HEAP_Swap_Node(Heap* H, int Pos1, int Pos2)
{
	int Copy_Size = sizeof(Heap_Node);
	Heap_Node* Temp = (Heap_Node*)malloc(sizeof(Heap_Node));

	if (Temp != NULL)
	{
		memcpy(Temp, &H->Nodes[Pos1], Copy_Size);
		memcpy(&H->Nodes[Pos1], &H->Nodes[Pos2], Copy_Size);
		memcpy(&H->Nodes[Pos2], Temp, Copy_Size);
	}

	free(Temp);
}

void HEAP_Insert(Heap* H, int New_Data)
{
	int Current_Pos = H->UsedSize;
	int Parant_Pos = HEAP_GetParent(Current_Pos);
	Heap_Node* Temp;

	if (H->UsedSize == H->Capacity)
	{
		H->Capacity *= 2;
		Temp = (Heap_Node*)realloc(H->Nodes, sizeof(Heap_Node) * H->Capacity);
		if (Temp != NULL)
			H->Nodes = Temp;
	}

	H->Nodes[Current_Pos].Data = New_Data;

	while (Current_Pos > 0 && H->Nodes[Current_Pos].Data < H->Nodes[Parant_Pos].Data)
	{
		HEAP_Swap_Node(H, Current_Pos, Parant_Pos);
		Current_Pos = Parant_Pos;
		Parant_Pos = HEAP_GetParent(Current_Pos);
	}

	H->UsedSize++;
}

void HEAP_Delete_Min(Heap* H, Heap_Node* Root)
{
	int Parant_Pos = 0;
	int Left_Pos = 0;
	int Right_Pos = 0;

	memcpy(Root, &H->Nodes[0], sizeof(Heap_Node));
	memset(&H->Nodes[0], 0, sizeof(Heap_Node));

	H->UsedSize--;
	HEAP_Swap_Node(H, 0, H->UsedSize);

	Left_Pos = HEAP_Get_Left_Child(0);
	Right_Pos = Left_Pos + 1;

	while (1)
	{
		int Selected_Child = 0;

		if (Left_Pos >= H->UsedSize)
			break;

		if (Right_Pos >= H->UsedSize)
			Selected_Child = Left_Pos;
		else
		{
			if (H->Nodes[Left_Pos].Data > H->Nodes[Right_Pos].Data)
				Selected_Child = Right_Pos;
			else
				Selected_Child = Left_Pos;
		}

		if (H->Nodes[Selected_Child].Data < H->Nodes[Parant_Pos].Data)
		{
			HEAP_Swap_Node(H, Selected_Child, Parant_Pos);
			Parant_Pos = Selected_Child;
		}
		else
			break;

		Left_Pos = HEAP_Get_Left_Child(Parant_Pos);
		Right_Pos = Left_Pos + 1;
	}

	if (H->UsedSize < (H->Capacity / 2))
	{
		Heap_Node* Temp;
		H->Capacity /= 2;
		Temp = (Heap_Node*)realloc(H->Nodes, sizeof(Heap_Node) * H->Capacity);
		if (Temp != NULL)
			H->Nodes = Temp;
	}
}

void HEAP_Print_Nodes(Heap* H)
{
	for (int i = 0; i < H->UsedSize; i++)
		printf("%d ", H->Nodes[i].Data);

	printf("\n");
}