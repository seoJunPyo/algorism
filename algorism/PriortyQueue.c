#include "PriortyQueue.h"

Priority_Queue* PQ_Create(int Capacity)
{
	Priority_Queue* New_PQ = (Priority_Queue*)malloc(sizeof(Priority_Queue));
	if (New_PQ != NULL)
	{
		New_PQ->Nodes = (PQ_Node*)malloc(sizeof(PQ_Node) * Capacity);
		New_PQ->Capacity = Capacity;
		New_PQ->Used_Size = 0;
	}

	return New_PQ;
}

void PQ_Destory(Priority_Queue* PQ)
{
	free(PQ->Nodes);
	free(PQ);
}

void PQ_Enqueue(Priority_Queue* PQ, PQ_Node New_Node)
{
	int Current_Pos = PQ->Used_Size;
	int Parent_Pos = PQ_Get_Parant_Pos(Current_Pos);

	if (PQ->Used_Size == PQ->Capacity)
	{
		PQ_Node* Temp;

		if (PQ->Capacity == 0)
			PQ->Capacity = 1;

		PQ->Capacity *= 2;
		Temp = (PQ_Node *)realloc(PQ->Nodes, sizeof(PQ_Node) * PQ->Capacity);
		if (Temp != NULL)
			PQ->Nodes = Temp;
	}

	PQ->Nodes[Current_Pos] = New_Node;

	while (Current_Pos > 0 && PQ->Nodes[Current_Pos].Priorty < PQ->Nodes[Parent_Pos].Priorty)
	{
		PQ_Swap_Node(PQ, Current_Pos, Parent_Pos);
		Current_Pos = Parent_Pos;
		Parent_Pos = PQ_Get_Parant_Pos(Current_Pos);
	}

	PQ->Used_Size++;
}

int PQ_Get_Parant_Pos(int Pos)
{
	return (Pos - 1) / 2;
}

int PQ_Get_Left_Child(int Pos)
{
	return (Pos * 2) + 1;
}

void PQ_Swap_Node(Priority_Queue* PQ, int Pos1, int Pos2)
{
	int Copy_Size = sizeof(PQ_Node);
	PQ_Node *Temp = (PQ_Node*)malloc(Copy_Size);

	if (Temp != NULL)
	{
		memcpy(Temp, &PQ->Nodes[Pos1], Copy_Size);
		memcpy(&PQ->Nodes[Pos1], &PQ->Nodes[Pos2], Copy_Size);
		memcpy(&PQ->Nodes[Pos2], Temp, Copy_Size);
	}

	free(Temp);
}

void PQ_Dequeue(Priority_Queue* PQ, PQ_Node* Root)
{
	int Parant_Pos = 0;
	int Left_Pos = 0;
	int Right_Pos = 0;

	memcpy(Root, &PQ->Nodes[0], sizeof(PQ_Node));
	memset(&PQ->Nodes[0], 0, sizeof(PQ_Node));

	PQ->Used_Size--;
	PQ_Swap_Node(PQ, 0, PQ->Used_Size);

	Left_Pos = PQ_Get_Left_Child(0);
	Right_Pos = Left_Pos + 1;

	while (1)
	{
		int Selected_Pos;

		if (Left_Pos >= PQ->Used_Size)
			break;

		if (Right_Pos >= PQ->Used_Size)
			Selected_Pos = Left_Pos;
		else
		{
			if (PQ->Nodes[Left_Pos].Priorty > PQ->Nodes[Right_Pos].Priorty)
				Selected_Pos = Right_Pos;
			else
				Selected_Pos = Left_Pos;
		}

		if (PQ->Nodes[Parant_Pos].Priorty > PQ->Nodes[Selected_Pos].Priorty)
		{
			PQ_Swap_Node(PQ, Parant_Pos, Selected_Pos);
			Parant_Pos = Selected_Pos;
		}
		else
			break;

		Left_Pos = PQ_Get_Left_Child(Parant_Pos);
		Right_Pos = Left_Pos + 1;
	}

	if (PQ->Used_Size < (PQ->Capacity / 2))
	{
		PQ_Node* Temp;
		PQ->Capacity /= 2;
		Temp = (PQ_Node*)realloc(PQ->Nodes, sizeof(PQ_Node) * PQ->Capacity);
		if (Temp != NULL)
			PQ->Nodes = Temp;
	}
}

int PQ_IsEmpty(Priority_Queue* PQ)
{
	return PQ->Used_Size == 0;
}

void Test_PQ(void)
{
	Priority_Queue* PQ = PQ_Create(3);
	PQ_Node Popped;

	PQ_Node Nodes[7] =
	{
		{34, (void*)"코딩"},
		{12, (void*)"고객미팅"},
		{87, (void*)"커피타기"},
		{45, (void*)"문서작성"},
		{35, (void*)"디버깅"},
		{66, (void*)"이닦기"},
	};

	PQ_Enqueue(PQ, Nodes[0]);
	PQ_Enqueue(PQ, Nodes[1]);
	PQ_Enqueue(PQ, Nodes[2]);
	PQ_Enqueue(PQ, Nodes[3]);
	PQ_Enqueue(PQ, Nodes[4]);
	PQ_Enqueue(PQ, Nodes[5]);

	printf("큐에 남아있는 작업 수 : %d\n", PQ->Used_Size);

	while (!PQ_IsEmpty(PQ))
	{
		PQ_Dequeue(PQ, &Popped);
		printf("작업명 : %s (우선순위:%d)\n", (char*)Popped.Data, Popped.Priorty);
	}
}