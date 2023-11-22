#include "HashTable.h"

// Simple Hash Table
Simple_Hash_Table* SHT_Create_Table(int Table_Size)
{
	Simple_Hash_Table* New_SHT = (Simple_Hash_Table*)malloc(sizeof(Simple_Hash_Table));
	if (New_SHT != NULL)
	{
		New_SHT->Table = (SHT_Node*)malloc(sizeof(SHT_Node) * Table_Size);
		New_SHT->Table_Size = Table_Size;
	}

	return New_SHT;
}

void SHT_Set(Simple_Hash_Table* SHT, int Key, int Value)
{
	int Address = SHT_Hash(Key, SHT->Table_Size);

	SHT->Table[Address].Key = Key;
	SHT->Table[Address].Value = Value;
}

int SHT_Get(Simple_Hash_Table* SHT, int Key)
{
	int Address = SHT_Hash(Key, SHT->Table_Size);

	return SHT->Table[Address].Value;
}

void SHT_Destroy_Table(Simple_Hash_Table* SHT)
{
	free(SHT->Table);
	free(SHT);
}

int SHT_Hash(int Key, int Table_Size)
{
	return Key % Table_Size;
}

// Chaning Hash Table
Chaining_Hash_Table* CHT_Create_Table(int Table_Size)
{
	Chaining_Hash_Table* New_CHT = (Chaining_Hash_Table*)malloc(sizeof(Chaining_Hash_Table));
	if (New_CHT != NULL)
	{
		New_CHT->Table = (L_List*)malloc(sizeof(LL_Node) * Table_Size);
		if (New_CHT->Table != NULL)
			memset(New_CHT->Table, 0, sizeof(LL_Node) * Table_Size);

		New_CHT->Table_Size = Table_Size;
	}

	return New_CHT;
}

LL_Node* CHT_Create_Node(char* Key, char* Value)
{
	LL_Node* New_Node = (LL_Node*)malloc(sizeof(LL_Node));
	if (New_Node != NULL)
	{
		New_Node->Key = (char*)malloc(strlen(Key) + 1);
		if (New_Node->Key != NULL)
			strcpy_s(New_Node->Key, strlen(Key) + 1,  Key);

		New_Node->Value = (char*)malloc(strlen(Value) + 1);
		if (New_Node->Value != NULL)
			strcpy_s(New_Node->Value, strlen(Value) + 1, Value);

		New_Node->Next = NULL;
	}

	return New_Node;
}

void CHT_Set(Chaining_Hash_Table* CHT, char* Key, char* Value)
{
	LL_Node* New_Node = CHT_Create_Node(Key, Value);
	int Address = CHT_Hash(Key, (int)strlen(Key), CHT->Table_Size);

	if (CHT->Table[Address] == NULL)
		CHT->Table[Address] = New_Node;
	else
	{
		New_Node->Next = CHT->Table[Address];
		CHT->Table[Address] = New_Node;
	}
}

char* CHT_Get(Chaining_Hash_Table* CHT, char* Key)
{
	int Address = CHT_Hash(Key, (int)strlen(Key), CHT->Table_Size);
	L_List List = CHT->Table[Address];
	LL_Node* Target = NULL;

	if (List == NULL)
		return NULL;

	while (1)
	{
		if (strcmp(List->Key, Key) == 0)
		{
			Target = List;
			break;
		}

		if (List->Next == NULL)
			return NULL;
		else
			List = List->Next;
	}

	return Target->Value;
}

void CHT_Destroy_Node(LL_Node* Node)
{
	free(Node->Key);
	free(Node->Value);
	free(Node);
}

void CHT_Destroy_List(L_List List)
{
	if (List == NULL)
		return;

	while (List->Next != NULL)
		CHT_Destroy_List(List->Next);

	CHT_Destroy_List(List);
}

void CHT_Destroy_Table(Chaining_Hash_Table* CHT)
{
	for (int i = 0; i < CHT->Table_Size; i++)
		CHT_Destroy_List(CHT->Table[i]);

	free(CHT->Table);
	free(CHT);
}

int CHT_Hash(char* Key, int Key_Len, int Table_Size)
{
	int Hash_Value = 0;

	for (int i = 0; i < Key_Len; i++)
		Hash_Value = (Hash_Value << 3) + Key[i];

	Hash_Value %= Table_Size;

	return Hash_Value;
}

void Test_CHT(void)
{
	Chaining_Hash_Table* CHT = CHT_Create_Table(12289);

	CHT_Set(CHT, "MSFT", "Microsoft Corporation");
	CHT_Set(CHT, "JAVA", "Sun Microsystems");
	CHT_Set(CHT, "REDH", "Red Hat Linux");
	CHT_Set(CHT, "APAC", "Apache Org");
	CHT_Set(CHT, "ZYMZZ", "Unisys Ops Check");
	CHT_Set(CHT, "IBM", "IBM Ltd");
	CHT_Set(CHT, "ORCL", "Oracle Corporation");
	CHT_Set(CHT, "CSSO", "Cisco Systems Inc.");
	CHT_Set(CHT, "GOOG", "Google Inc.");
	CHT_Set(CHT, "YHOO", "Yahoo! Inc.");
	CHT_Set(CHT, "NOVL", "Novell Inc.");

	printf("\n");
	printf("Key : %s, Value : %s\n", "MSFT", CHT_Get(CHT, "MSFT"));
	printf("Key : %s, Value : %s\n", "JAVA", CHT_Get(CHT, "JAVA"));
	printf("Key : %s, Value : %s\n", "REDH", CHT_Get(CHT, "REDH"));
	printf("Key : %s, Value : %s\n", "APAC", CHT_Get(CHT, "APAC"));
	printf("Key : %s, Value : %s\n", "ZYMZZ", CHT_Get(CHT, "ZYMZZ"));
	printf("Key : %s, Value : %s\n", "IBM", CHT_Get(CHT, "IBM"));
	printf("Key : %s, Value : %s\n", "ORCL", CHT_Get(CHT, "ORCL"));
	printf("Key : %s, Value : %s\n", "CSSO", CHT_Get(CHT, "CSSO"));
	printf("Key : %s, Value : %s\n", "GOOG", CHT_Get(CHT, "GOOG"));
	printf("Key : %s, Value : %s\n", "YHOO", CHT_Get(CHT, "YHOO"));
	printf("Key : %s, Value : %s\n", "NOVL", CHT_Get(CHT, "NOVL"));

	CHT_Destroy_Table(CHT);
}

// Binary Hash Table
Binary_Hash_Table* BHT_Create_Table(int Table_Size)
{
	Binary_Hash_Table *New_BHT = (Binary_Hash_Table*)malloc(sizeof(Binary_Hash_Table));
	if (New_BHT != NULL)
	{
		New_BHT->Table = (B_Tree*)malloc(sizeof(B_Tree) * Table_Size);
		if (New_BHT->Table != NULL)
			memset(New_BHT->Table, 0, sizeof(B_Tree) * Table_Size);
		New_BHT->Table_Size = Table_Size;
	}

	return New_BHT;
}

B_Node* BHT_Create_Node(char* Key, char* Value)
{
	B_Node* New_Node = (B_Node*)malloc(sizeof(B_Node));
	if (New_Node != NULL)
	{
		New_Node->Key = (char*)malloc(strlen(Key) + 1);
		if (New_Node->Key != NULL)
			strcpy_s(New_Node->Key, strlen(Key) + 1, Key);

		New_Node->Value = (char*)malloc(strlen(Value) + 1);
		if (New_Node->Value != NULL)
			strcpy_s(New_Node->Value, strlen(Value) + 1, Value);

		New_Node->Left = NULL;
		New_Node->Right = NULL;
	}

	return New_Node;
}

void BHT_Destroy_Node(B_Node* Node)
{
	free(Node);
}

void BHT_Destroy_Tree(B_Tree Tree)
{
	if (Tree->Left != NULL)
		BHT_Destroy_Tree(Tree->Left);

	if (Tree->Right != NULL)
		BHT_Destroy_Tree(Tree->Right);

	free(Tree->Key);
	free(Tree->Value);
	free(Tree);
}

void BHT_Set(Binary_Hash_Table* BHT, char* Key, char* Value)
{
	int Address = BHT_Hash(Key, (int)strlen(Key), BHT->Table_Size);
	B_Node* New_Node = BHT_Create_Node(Key, Value);

	BHT_Insert_Node(BHT->Table[Address], New_Node);
}

char* BHT_Get(Binary_Hash_Table* BHT, char* Key)
{
	int Address = BHT_Hash(Key, (int)strlen(Key), BHT->Table_Size);
	B_Node* Target = BHT_Search_Node(BHT->Table[Address], Key);

	return Target->Value;
}

int BHT_Hash(char* Key, int Key_Len, int Table_Size)
{
	int Hash_Value = 0;

	for (int i = 0; i < Key_Len; i++)
		Hash_Value = (Hash_Value << 3) + Key[i];

	Hash_Value %= Table_Size;

	return Hash_Value;
}

int BHT_Key_Sum(char* Key, int Key_Len)
{
	int result = 0;

	for (int i = 0; i < Key_Len; i++)
		result = Key[i];

	return result;
}

void BHT_Insert_Node(B_Tree Tree, B_Node* New_Node)
{
	if (Tree == NULL)
		Tree = New_Node;
	else
	{
		if (BHT_Key_Sum(Tree->Key, (int)strlen(Tree->Key)) < BHT_Key_Sum(New_Node->Key, (int)strlen(New_Node->Key)))
			BHT_Insert_Node(Tree->Right, New_Node);
		else
			BHT_Insert_Node(Tree->Left, New_Node);
	}
}

B_Node* BHT_Search_Node(B_Tree Tree, char* Key)
{
	if (Tree == NULL)
		return NULL;
	else
	{
		if (strcmp(Tree->Key, Key) == 0)
			return Tree;
		else if (BHT_Key_Sum(Tree->Key, (int)strlen(Tree->Key)) < BHT_Key_Sum(Key, (int)strlen(Key)))
			return BHT_Search_Node(Tree->Right, Key);
		else
			return BHT_Search_Node(Tree->Left, Key);
	}
}

// Open Address Hash Table
Open_Address_Hash_Table* OAHT_Create_Table(int Table_Size)
{
	Open_Address_Hash_Table* New_OAHT = (Open_Address_Hash_Table*)malloc(sizeof(Open_Address_Hash_Table));
	if (New_OAHT != NULL)
	{
		New_OAHT->Table = (Element_Type*)malloc(sizeof(Element_Type) * Table_Size);
		if (New_OAHT != NULL)
			memset(New_OAHT->Table, 0, sizeof(Element_Type) * Table_Size);

		New_OAHT->Table_Size = Table_Size;
		New_OAHT->Occupied_Count = 0;
	}

	return New_OAHT;
}

void OAHT_Set(Open_Address_Hash_Table** OAHT, char* Key, char* Value)
{
	int Key_Len, Address, Step_Size;
	double Usage;

	Usage = (double)(*OAHT)->Occupied_Count / (*OAHT)->Table_Size;

	if (Usage > 0.5)
		OAHT_Rehash(OAHT);

	Key_Len = (int)strlen(Key);
	Address = OAHT_Hash(Key, Key_Len, (*OAHT)->Table_Size);
	Step_Size = OAHT_Hash2(Key, Key_Len, (*OAHT)->Table_Size);

	while ((*OAHT)->Table[Address].Status != EMPTY && strcmp((*OAHT)->Table[Address].Key, Key) != 0)
		Address = (Address + Step_Size) % (*OAHT)->Table_Size;

	(*OAHT)->Table[Address].Key = (char*)malloc(sizeof(char) * (Key_Len + 1));
	strcpy_s((*OAHT)->Table[Address].Key, Key_Len + 1, Key);

	(*OAHT)->Table[Address].Value = (char*)malloc(sizeof(char) * (strlen(Value) + 1));
	strcpy_s((*OAHT)->Table[Address].Value, strlen(Value) + 1, Key);

	(*OAHT)->Table[Address].Status = 1;
	(*OAHT)->Occupied_Count++;
}

char* OAHT_Get(Open_Address_Hash_Table* OAHT, char* Key)
{
	int Key_Len = (int)strlen(Key);
	int Address = OAHT_Hash(Key, Key_Len, OAHT->Table_Size);
	int Step_Size = OAHT_Hash2(Key, Key_Len, OAHT->Table_Size);

	while (OAHT->Table[Address].Status != EMPTY && strcmp(OAHT->Table[Address].Key, Key) != 0)
		Address = (Address + Step_Size) % OAHT->Table_Size;

	return OAHT->Table[Address].Value;
}

void OAHT_Clear_Element(Element_Type* El)
{
	if (El->Status == EMPTY)
		return;

	free(El->Key);
	free(El->Value);
}

void OAHT_Destroy_Table(Open_Address_Hash_Table* OAHT)
{
	for (int i = 0; i < OAHT->Table_Size; i++)
		OAHT_Clear_Element(&OAHT->Table[i]);

	free(OAHT->Table);
	free(OAHT);
}

int OAHT_Hash(char* Key, int Key_Len, int Table_Size)
{
	int Hash_Value = 0;

	for (int i = 0; i < Key_Len; i++)
		Hash_Value = (Hash_Value << 3) + Key[i];

	Hash_Value %= Table_Size;

	return Hash_Value;
}

int OAHT_Hash2(char* Key, int Key_Len, int Table_Size)
{
	int Hash_Value = 0;

	for (int i = 0; i < Key_Len; i++)
		Hash_Value = (Hash_Value << 2) + Key[i];

	Hash_Value %= (Table_Size - 3);

	return Hash_Value + 1;
}

void OAHT_Rehash(Open_Address_Hash_Table** OAHT)
{
	Element_Type* Old_Table = (*OAHT)->Table;

	Open_Address_Hash_Table* New_OAHT = OAHT_Create_Table((*OAHT)->Table_Size * 2);

	for (int i = 0; i < (*OAHT)->Table_Size; i++)
	{
		if (Old_Table[i].Status == OCCUPIED)
			OAHT_Set(&New_OAHT, Old_Table[i].Key, Old_Table[i].Value);
	}

	OAHT_Destroy_Table(*OAHT);
	*OAHT = New_OAHT;
}