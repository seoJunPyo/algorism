#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct tagHeapNode
{
	int Data;
} Heap_Node;

typedef struct tagHeep
{
	Heap_Node* Nodes;
	int Capacity;
	int UsedSize;
} Heap;