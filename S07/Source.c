//#define _CRT_SECURE_NO_WARNINGS
//HASH TABLE implementation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)
typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name;
} Student, * PStudent;
//typedef struct Student Student;
#define LINE_BUFFER 256
#define HT_INITIAL_SIZE 3

typedef struct DoubleLinkedList {
	Student* info;
	struct DoubleLinkedList* next;
	struct DoubleLinkedList* prev;
}DoubleLinkedList;

typedef struct HT {
	DoubleLinkedList** items;
	int size;
}HashTable;


Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
void putStudent(HashTable*, Student*); 
DoubleLinkedList* insertCircleDoubleLinkedList(DoubleLinkedList*, Student*);
void printHashTable(HashTable);

int main()
{
	HashTable hashTable = { .items=NULL, .size=0 }; //init hashtable



	FILE* fp = fopen("Data.txt", "r");

	if (fp != NULL)
	{
		char line[LINE_BUFFER];
		//char* delimiter = ",";
		char delimiter[] = { ',','\n','\0' };
		unsigned int regNo;
		short int groupNo;
		char* token = NULL;
		char* context = NULL;



		while (fgets(line, LINE_BUFFER, fp))
		{
			token = strtok_s(line, delimiter, &context);
			regNo = atoi(token);

			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token);

			token = strtok_s(NULL, delimiter, &context);

			Student* stud = createStudent(regNo, groupNo, token);
			//printStudent(stud);

			putStudent(&hashTable, stud); //pass HT by reference



		}
		printHashTable(hashTable);

		//to be implemented
		//deleteStudent(hashTable, 1070, "Popescu Ion");
	}
	else printf("Can not read data file.");
}
void deleteStudent(Student* pStud)
{
	if (pStud != NULL)
	{
		if (pStud->name != NULL)
			free(pStud->name);
		free(pStud);
	}
}
void printStudent(Student* pStud)
{
	if (pStud != NULL)
		printf("RegNo=%d, GroupNo=%d, Name=%s\n",
			pStud->regNo,
			pStud->groupNo,
			pStud->name);
}

Student* createStudent(unsigned int regNo,
	short int groupNo,
	const char* name)
{
	Student* pStud = (Student*)malloc(sizeof(Student));
	if (pStud != NULL)
	{
		pStud->regNo = regNo;
		pStud->groupNo = groupNo;
		pStud->name = (char*)malloc(strlen(name) + 1);
		if (pStud->name != NULL)
		{
			strcpy_s(pStud->name, strlen(name) + 1, name);
		}
		else
		{
			free(pStud);
			pStud = NULL;
		}
	}
	return pStud;
}


//this function returns always data in the array [0; size-1]
static int fhash(int key, int size) {
	return key % size;
}

//circular linked list
DoubleLinkedList* insertCircleDoubleLinkedList(DoubleLinkedList* dll, Student* stud) {
	
	//alloc memory for 1 node
	DoubleLinkedList* node = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
	if (node) {
		node->info = stud;
		node->next = NULL;
		node->prev = NULL;

		if (!dll) {
			dll = node;
			dll->next = dll;
			//dll->info already has the info from node
			dll->prev = dll;
		}
		else {
			//node = dll;
			node->next = dll;
			node->prev = dll->prev;
			dll->prev = node;
			//dll->next = (node->prev)->next;
			node->prev->next = node;
		}
	}

	return dll;
}



void printHashTable(HashTable hashTable) {
	for (int i = 0; i < hashTable.size; i++) {
		printf("Bucket: %d\n", i);
		
		if (hashTable.items[i]) {
			DoubleLinkedList* iterator = hashTable.items[i];
			do {
				printStudent(iterator->info);
				iterator = iterator->next;
			} while (iterator != hashTable.items[i]);
		}
	}
}


void putStudent(HashTable* hashTable, Student* stud) {
	if (hashTable->size == 0 || (!hashTable->items)) {
		hashTable->size = HT_INITIAL_SIZE;
		hashTable->items = (DoubleLinkedList**)malloc(HT_INITIAL_SIZE * sizeof(DoubleLinkedList*));
		memset(hashTable->items, NULL, HT_INITIAL_SIZE * sizeof(DoubleLinkedList*));
	}
	//choose data from Data.txt, in this case group number
	int index = fhash(stud->groupNo, hashTable->size);
	hashTable->items[index] = insertCircleDoubleLinkedList(hashTable->items[index], stud);

}

