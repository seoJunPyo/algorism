#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct tagePQNode
{
	int Priorty;
	void* Data;
} PQ_Node;

typedef struct tagPQ
{
	PQ_Node* Nodes;
	int Capacity;
	int Used_Size;
} Priority_Queue;

Priority_Queue* PQ_Create(int Capacity);
void PQ_Destory(Priority_Queue* PQ);
void PQ_Enqueue(Priority_Queue* PQ, PQ_Node New_Node);
int PQ_Get_Parant_Pos(int Pos);
int PQ_Get_Left_Child(int Pos);
void PQ_Swap_Node(Priority_Queue* PQ, int Pos1, int Pos2);
void PQ_Dequeue(Priority_Queue* PQ, PQ_Node* Root);
int PQ_IsEmpty(Priority_Queue* PQ);
void Test_PQ(void);