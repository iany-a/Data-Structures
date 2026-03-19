//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> //for booleans in C
#pragma pack(1)
typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name;
} Student, * PStudent;
//typedef struct Student Student;

typedef struct StackNode {
	Student* data;
	struct StackNode* next;
}StackNode, * PStackNode;


typedef struct DoubleStack {
	StackNode* head1;
	StackNode* head2;
}DoubleStack;

#define LINE_BUFFER 256

Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
bool isEmpty(StackNode*);
//void push(StackNode**, Student*); list approach
//push the useful information
StackNode* push(StackNode*, Student*);
//pop - take the useful information and delete the node
Student* pop(StackNode**);
Student* peek(StackNode*);//look at the element without changing its value

bool isEmpty(StackNode* head) { //sp
	if (head == NULL) return true;
	return false;
}

//insertion at the beginning of the list
StackNode* push(StackNode* head, Student* stud) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode*));
	newNode->data = stud;
	newNode->next = NULL;

	if (!isEmpty(head)) { //if head is not empty
		newNode->next = head;
	}
	return newNode;
}

Student* pop(StackNode** head) {
	if (isEmpty(*head)) return NULL; //IMPORTANT: dereference the head before interogation, otherwise this is always FALSE
	//1.return useful information
	//2.delete the node
	//3.change the head
	Student* stud = (*head)->data; //paranthesis are required to confirm order of operations
	StackNode** tmp = head;
	(*head) = (*head)->next;
	free(tmp);
	return stud;
}

Student* peek(StackNode* head) {
	if (isEmpty(head)) return NULL;
	return head->data;
}

void deleteStack(StackNode**);

int main()
{
	PStackNode stack = NULL; //if the head of the stack is NULL, the stack is empty
	//all structure follow the same principle!

	DoubleStack doubleStack = { .head1 = NULL, .head2 = NULL }; //init double stack

	//HW: work with double stack and implement a function in reverse from head1 to head2
	//catch: do a counter equal to size since this will go on forever if not

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
			stack = push(stack, stud);
			stud = peek(stack);
			printStudent(stud);
		}

		deleteStack(&stack);
	}
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



void deleteStack(StackNode** stack) {

	while (!(isEmpty(*stack))) {
		Student* stud = pop(stack);
		printStudent(stud);
		deleteStudent(stud);
	}
}






