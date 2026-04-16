//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)
#define LINE_BUFFER 256
typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name;
} Student, * PStudent;
//typedef struct Student Student;

typedef struct SLL {
	Student* data;
	struct SLL* next;
}SLL, *pSLL;

//SLL* insertIntoList(SLL* sll, Student* stud) {
//	SLL* newNode = (SLL*)malloc(sizeof(SLL));
//	if (!newNode) { //case A: the newNode memory allocation failed:
//		if (!sll) return NULL; //if the sll input is invalid, return NULL;
//		else return sll; //if the sll input is valid, return it
//	}
//	//case B: the newNode memory allocation finished succesfully:
//	newNode->data = stud; //first thing always assign the student (data) to the new node->data
//	if (!sll) { //Case A: if input list is invalid we return the new node containing that single student
//		newNode->next = newNode; //the new node needs to point to itself 
//		return newNode;
//	}
//	else { //Case B: if the input list is valid:
//		newNode->next = sll->next; // the newNode next points to the head of the list
//		sll->next = newNode; //the head of the list points to the new node
//		return sll; //return the original list with the new node appended
//	}
//}


SLL* insertInList(SLL* sll, Student* s) {
	SLL* newNode = (SLL*)malloc(sizeof(SLL));
	if (newNode) newNode->data = s;
	else return sll;

	if (sll){
		if (newNode) {
			newNode->next = sll->next;
			sll->next = newNode;
		}
		return sll;
	}
	else {
		newNode->next = newNode;
		return newNode;
	}
}




Student* createStudent(
	unsigned int regNo,
	short int groupNo,
	const char* name)
{
	if (name == NULL || strlen(name) == 0) {
		printf("Invalid student entry found: Invalid Name. Skipping line.\n______________________________\n");
		return NULL;
	}
	else {
		Student* pStud = (Student*)malloc(sizeof(Student));
		//this is the equivalent of Student* pStud = new Student(); in C++
		if (pStud != NULL) //if-else statement for defensive programming ensures that the
			//memory was correctly allocated before proceeding with assignment of struct members
		{
			pStud->regNo = regNo;
			pStud->groupNo = groupNo;
			pStud->name = (char*)malloc(strlen(name) + 1);
			//struct requires 2 allocations, one for the structure itself, one for the array of chars
			if (pStud->name != NULL) //defensive programming as stated above
			{
				strcpy_s(pStud->name, strlen(name) + 1, name);
				printf("Succesfully created student with name: %s\n", pStud->name);
			}
			else
			{
				free(pStud);
				pStud = NULL;

			}
		}
		return pStud;
	}
}

void printStudent(Student* pStud)
{
	if (pStud != NULL)
		printf("RegNo = %d, GroupNo = %d, Name = %s\n",
			pStud->regNo,
			pStud->groupNo,
			pStud->name);
}

void deleteStudent(Student* pStud)
{
	if (pStud != NULL)
	{
		if (pStud->name != NULL) {
			printf("Starting char array deletion for student with name: %s\n", pStud->name);
			free(pStud->name);
		}
		free(pStud);
		printf("Memory for student freed.\n______________________________\n");


	}
}

void printList(SLL* sll) {
	if (!sll) return;
	SLL* temp = sll->next; //revert to start of list (or "head")
	do {
		printStudent(temp->data);
		temp = temp->next;
	} while (temp != sll->next);
}

int main()
{
	SLL* sll = NULL;

	FILE* fp = fopen("Data.txt", "r");

	if (fp != NULL)
	{
		char line[LINE_BUFFER];
		//char* delimiter = ",";
		char delimiter[] = { ',', '\n', '\0' }; //, is the first delimiter
		unsigned int regNo;
		short int groupNo;
		char* token = NULL;
		char* context = NULL;
		while (fgets(line, LINE_BUFFER, fp))
		{
			token = strtok_s(line, delimiter, &context);
			regNo = atoi(token); //ASCII to integer

			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token); //ASCII to integer

			token = strtok_s(NULL, delimiter, &context);
			if (token != NULL && token[0] == ' ') token++;

			Student* stud = createStudent(regNo, groupNo, token);
			//token is kept as last field, as declaring a new field for the array is pointless and wastes resources.
			//printStudent(stud);
			//deleteStudent(stud);
			if (stud) sll = insertInList(sll, stud);
			printList(sll);

		}
	}
}
