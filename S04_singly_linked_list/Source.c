//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)
typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name; 
} Student, *PStudent;
//typedef struct Student Student;
#define LINE_BUFFER 256

//Singly-linked list definition
typedef struct ListNode {
	Student* data;
	struct ListNode* next; //self-referential, always a pointer to the next node
} ListNode, *PListNode;

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
		printf("RegNo=%d, GroupNo=%d, Name=%s",
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

//Logic:
//1.connect the node to the structure
//2.connect struct to node

//checklist for special use-cases:
//list is empty
//list has one element


ListNode* createNode(Student* stud) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode)); //allocation
	if (node!=NULL) {
		node->data = stud; //init
		node->next = NULL; //init
	}
	return node; //return
}


//don't create functions that insert nodes into lists (as "insert node")
void insertStudentToEndList(ListNode** list, Student* stud) {
	ListNode* node = createNode(stud);
	ListNode* temp = *list; //temp copy of list to iterate through
	if (temp != NULL) {
		while (temp->next) { //stop at the last list element
			temp = temp->next;
		}
		temp->next = node;
	}
	else {
		*list = node; //only if temp (initial list) is empty, 
					  //last element will be populated with the passed student parameter
					  //(by calling the createNode function)
	}
}

void printSinglyLinkedList(ListNode* list) {
	//if (list) {
		while (list) {
			printStudent(list->data);
			list = list->next;
		}
	//}
}

void insertStudentToArrayBasedList(ListNode** vector, Student* stud, short *headIndex, short size) {
	ListNode* node = createNode(stud);
	
	//insertion in the list at the beginning
	node->next = vector[*headIndex];

	*headIndex = size;
	vector[*headIndex] = node;

}

//HW: Instead of inserting at the beginning of the list, 
//adapt this function and ask the user after which student (by name) you wish to insert
//if not exist, add to beginning or end (you decide)



//Student* createStudent(unsigned int, short int, const char*);
//void printStudent(Student*);
//void deleteStudent(Student*);


int main()
{
	//Linked List init to NULL (array based)
	ListNode* singlyLinkedList = NULL; //pointer to 1 single node

	ListNode* vector[100]; //static array of 100 pointers to nodes
	memset(vector, 0, sizeof(vector)); //init the 100 pointers with NULL

	

	FILE* fp = fopen("Data.txt", "r");

	if (fp != NULL)
	{
		char line[LINE_BUFFER];
		char* delimiter = ",";
		//char delimiter[] = {',','\0'};
		unsigned int regNo;
		short int groupNo;
		char* token = NULL;
		char* context = NULL;
		short headIndex = 0;
		short size = 0;
		while (fgets(line, LINE_BUFFER, fp))
		{
			token = strtok_s(line, delimiter, &context);
			regNo = atoi(token);
			
			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token);

			token = strtok_s(NULL, delimiter, &context);

			Student* stud = createStudent(regNo, groupNo, token);

			//insertStudentToEndList(&singlyLinkedList, stud);
			insertStudentToArrayBasedList(vector, stud, &headIndex, size++);
			
			printSinglyLinkedList(vector[headIndex]);
			printf("\n------------------------------------------------\n");
			//printStudent(stud);
			//deleteStudent(stud);
		}
	}
}
