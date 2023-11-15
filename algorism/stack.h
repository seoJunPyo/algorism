#include <stdlib.h>
#include <stdio.h>

typedef struct Stack_Node
{
	int Data;
} S_Node;

typedef struct Stack
{
	int Capacity;
	int Top;
	S_Node* Nodes;
} Stack;

void Create_Stack(Stack** St, int Capacity);
void Push(Stack* St, int New_Data);
int Pop(Stack* St);
void Print_Stack(Stack* St);
int IsEmpty(Stack* st);
