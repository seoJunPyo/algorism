#include "sort.h"
#include "stack.h"
#include <stdio.h>
void Swap(int* A, int* B);
int Partition(int Data_Set[], int Left, int Right);
void print_arr(int arr[], int len);

void Bubble_Sort(int Data_Set[], int len)
{
	int temp;
	int is_Sorted = 1;

	for (int i = 0; i < len - 1; i++)
		if (Data_Set[i] > Data_Set[i + 1])
		{
			is_Sorted = 0;
			break;
		}

	if (is_Sorted)
		return;
	
	for (int i = 0; i < len - 1; i++)
		for (int j = 0; j < len - 1 - i; j++)
			if (Data_Set[j] > Data_Set[j + 1])
			{
				temp = Data_Set[j];
				Data_Set[j] = Data_Set[j + 1];
				Data_Set[j + 1] = temp;
			}
}

void Insertion_Sort(int Data_Set[], int len)
{
	int temp;

	for (int i = 1; i < len; i++)
	{
		if (Data_Set[i - 1] <= Data_Set[i])
			continue;
		
		temp = Data_Set[i];
		for (int j = 0; j < i; j++)
			if (Data_Set[j] > temp)
			{
				memmove(&Data_Set[j + 1], &Data_Set[j], sizeof(Data_Set[0]) * (i - j));
				Data_Set[j] = temp;
				break;
			}
	}
}

void Quick_Sort(int Data_Set[], int Left, int Right)
{
	if (Left < Right)
	{
		int idx = Partition(Data_Set, Left, Right);

		Quick_Sort(Data_Set, Left, idx - 1);
		Quick_Sort(Data_Set, idx + 1, Right);
	}
}
void Quick_Sort_Stack(int Data_Set[], int Left, int Right)
{
	Stack* Idx_Stack;
	Create_Stack(&Idx_Stack, 4);

	Push(Idx_Stack, Left);
	Push(Idx_Stack, Right);

	while (!IsEmpty(Idx_Stack))
	{
		Left = Pop(Idx_Stack);
		Right = Pop(Idx_Stack);

		if (Left < Right)
		{
			int idx = Partition(Data_Set, Left, Right);

			Push(Idx_Stack, Left);
			Push(Idx_Stack, idx - 1);
			Push(Idx_Stack, idx + 1);
			Push(Idx_Stack, Right);
		}
	}
}



static void Swap(int* A, int* B)
{
	int temp = *A;
	*A = *B;
	*B = temp;
}

static int get_middle_num_idx(int Data_Set[], int i)
{
	int temp;
	struct el
	{
		int idx;
		int num;
	};
	struct el el[3] = { {i, Data_Set[i]} , {i + 1, Data_Set[i + 1]} , {i + 2, Data_Set[i + 2]}};

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2 - i; j++)
			if (el[j].num > el[j + 1].num)
			{
				temp = el[j].num;
				el[j].num = el[j + 1].num;
				el[j + 1].num = temp;
			}
	
	return el[1].idx;
}

static int Partition(int Data_Set[], int Left, int Right)
{
	int Pivot_Idx = Left - Right > 1 ? get_middle_num_idx(Data_Set, Left) : Left;
	int Pivot = Data_Set[Pivot_Idx];

	if (Left != Pivot_Idx)
		Left++;

	while (Left < Right)
	{
		while (Data_Set[Left] <= Pivot && Left < Right)
			Left++;

		while (Data_Set[Right] >= Pivot && Left <= Right)
			Right--;

		if (Left < Right)
			Swap(&Data_Set[Left], &Data_Set[Right]);
		else
			break;
	}

	Swap(&Data_Set[Pivot_Idx], &Data_Set[Right]);

	return Right;
}

static void print_arr(int arr[], int len)
{
	for (int i = 0; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}