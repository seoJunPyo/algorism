#include <stdio.h>
#include "sort.h"
#include "DoublyLinkedList.h"
#include "LinkedLIst.h"
#include "Search_Array.h"
#include "BinaryTree.h"
#include "RedBlackTree.h"

RBT_Node* Nil;

int main(void)
{
	RBT_Node* Tree = NULL;
	RBT_Node* Node = NULL;

	Nil = RBT_Create_Node(0);
	Nil->Color = BLACK;

	while (1)
	{
		int cmd = 0;
		int param = 0;
		char buffer[10];

		printf("Enter command number : \n");
		printf("(1) Create a node, (2) Remove a node, (3)Search a Node\n");
		printf("(4)Display Tree, (5)quit.\n");
		printf("command number : ");

		fgets(buffer, sizeof(buffer) - 1, stdin);
		sscanf_s(buffer, "%d", &cmd);

		if (cmd < 1 || cmd > 5)
		{
			printf("Invaild command number.\n");
			continue;
		}

		else if (cmd == 4)
		{
			RBT_Print_Tree(Tree, 0, 0);
			continue;
		}
		else if (cmd == 5)
			break;

		printf("Enter parmeter (1-200) : \n");

		fgets(buffer, sizeof(buffer) - 1, stdin);
		sscanf_s(buffer, "%d", &param);

		if (param < 1 || param > 200)
		{
			printf("Invaild parameter %d\n", param);
			continue;
		}

		switch (cmd)
		{
		case 1 :
			RBT_Insert_Node(&Tree, RBT_Create_Node(param));
			break;
		case 2 : 
			Node = RBT_Remove_Node(&Tree, param);

			if (Node == NULL)
				printf("Not Found node to delete \n");
			else
				RBT_Destroy_Node(Node);

			break;
		case 3 :
			Node = RBT_Search_Node(Tree, param);

			if (Node == NULL)
				printf("Not Found node %d\n", param);
			else
				printf("Found node : %d(Color : %s)\n", Node->Data, Node->Color == RED ? "RED" : "BLACK");
			break;
		}

		printf("\n");
	}

	RBT_Destroy_Tree(Tree);
	return 0;
}

