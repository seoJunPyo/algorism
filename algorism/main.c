#include <stdio.h>
#include "sort.h"
#include "DoublyLinkedList.h"


void print_arr(int arr[], int len);

int main(void)
{
	int nums[] = { 6, 4, 8, 3, 7, 1, 5 ,9};
	int len = sizeof(nums) / sizeof(nums[0]);

	Quick_Sort(nums, 0, len- 1);
	print_arr(nums, len);
}


void print_arr(int arr[], int len)
{
	for (int i = 0; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}