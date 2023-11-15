#include "stack.h"

void Create_Stack(Stack** St, int Capacity)
{
	(*St) = (Stack*)malloc(sizeof(Stack));

	if (*St != NULL)
	{
		(*St)->Nodes = (S_Node*)malloc(sizeof(S_Node) * Capacity);
		(*St)->Capacity = Capacity;
		(*St)->Top = -1;
	}
}

void Destroy_Stack(Stack* St)
{
	free(St->Nodes);
	free(St);
}

void Push(Stack * St, int New_Data)
{
	St->Top++;
	St->Nodes[St->Top].Data = New_Data;
}

int Pop(Stack* St)
{
	int Popped = St->Nodes[0].Data;
	St->Nodes++;
	St->Top--;

	return Popped;
}

void Print_Stack(Stack* St)
{
	for (int i = 0; i <= St->Top; i++)
	{
		printf("%d ", St->Nodes[i].Data);
	}
}

int IsEmpty(Stack* St)
{
	return St->Top == -1;
}