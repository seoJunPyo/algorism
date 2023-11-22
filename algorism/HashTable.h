#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagSHTNode
{
	int Key;
	int Value;
} SHT_Node;

typedef struct tagSHT
{
	SHT_Node* Table;
	int Table_Size;
} Simple_Hash_Table;

typedef struct tagHLLNode
{
	char* Key;
	char* Value;
	struct tagHLLNode* Next;
} LL_Node;

typedef LL_Node* L_List;

typedef struct tagCHT
{
	int Table_Size;
	L_List* Table;
} Chaining_Hash_Table;

typedef struct tagBLLNode
{
	char* Key;
	char* Value;
	struct tagBLLNode* Left;
	struct tagBLLNode* Right;
} B_Node;

typedef B_Node* B_Tree;

typedef struct tagBHT
{
	int Table_Size;
	B_Tree* Table;
} Binary_Hash_Table;

enum Element_Status
{
	EMPTY = 0,
	OCCUPIED = 1
};

typedef struct tagElementType
{
	char* Key;
	char* Value;
	enum Element_Status Status;
} Element_Type;

typedef struct tagOAHT
{
	int Occupied_Count;
	int Table_Size;
	Element_Type* Table;
} Open_Address_Hash_Table;

Simple_Hash_Table* SHT_Create_Table(int Table_Size);
void SHT_Destroy_Table(Simple_Hash_Table* SHT);
void SHT_Set(Simple_Hash_Table* SHT, int Key, int Value);
int SHT_Get(Simple_Hash_Table* SHT, int Key);
int SHT_Hash(int Key, int Table_Size);

Chaining_Hash_Table* CHT_Create_Table(int Table_Size);
LL_Node* CHT_Create_Node(char* Key, char* Value);
void CHT_Set(Chaining_Hash_Table* CHT, char* Key, char* Value);
char* CHT_Get(Chaining_Hash_Table* CHT, char* Key);
void CHT_Destroy_Node(LL_Node* Node);
void CHT_Destroy_List(L_List List);
void CHT_Destroy_Table(Chaining_Hash_Table* CHT);
int CHT_Hash(char* Key, int Key_Len, int Table_Size);
void Test_CHT(void);

Binary_Hash_Table* BHT_Create_Table(int Table_Size);
B_Node* BHT_Create_Node(char* Key, char* Value);
void BHT_Destroy_Node(B_Node* Node);
void BHT_Destroy_Tree(B_Tree Tree);
void BHT_Set(Binary_Hash_Table* BHT, char* Key, char* Value);
char* BHT_Get(Binary_Hash_Table* BHT, char* Key);
int BHT_Hash(char* Key, int Key_Len, int Table_Size);
int BHT_Key_Sum(char* Key, int Key_Len);
void BHT_Insert_Node(B_Tree Tree, B_Node* New_Node);
B_Node* BHT_Search_Node(B_Tree Tree, char* Key);



Open_Address_Hash_Table* OAHT_Create_Table(int Table_Size);
void OAHT_Set(Open_Address_Hash_Table** OAHT, char* Key, char* Value);
char* OAHT_Get(Open_Address_Hash_Table* OAHT, char* Key);
void OAHT_Clear_Element(Element_Type* El);
void OAHT_Destroy_Table(Open_Address_Hash_Table* OAHT);
int OAHT_Hash(char* Key, int Key_Len, int Table_Size);
int OAHT_Hash2(char* Key, int Key_Len, int Table_Size);
void OAHT_Rehash(Open_Address_Hash_Table** OAHT);