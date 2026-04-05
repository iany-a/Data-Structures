//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)
#define LINE_BUFFER 256

//QUEUE data structure
//First In, First Out
//A QueueNode will store data about the current student and the one behind it in the line (queue)
//A Queue will store data about the current student at the beginning of the list (first that will go out)
//and about the current student at the end of the list (the one which will go out the last).
//In between these students, there can be any number of students >=0 (stored in Queue Nodes).
//QUEUE representation:
// Marrie			| John			| Dan			| George			| NULL
//	Marrie.next ->	|	John.next ->|	Dan.next ->	|	George.next ->	|
//
// Marie is a stud which contains its own data. 
// The Queue Node containing Marie (the box) will contain a pointer to her full info,
//as well as a pointer to the next Queue Node (if it exists) in the queue.
// The Queue itself contains just a pointer of the first QueueNode in the list, and the last one.
// The Queue does not care about how long the list is.
// When a new student joins the queue (at the back), it is appended to the list via the Queue put function.


typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name;
} Student, * PStudent;




typedef struct QueueNode {
	Student* info;
	struct QueueNode* next;
}QueueNode;

typedef struct Queue {
	QueueNode* head;
	QueueNode* tail;
}Queue;
Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
Queue put(Queue, Student*);
void deleteQueue(Queue* queue);
Student* get(Queue*);// the head will change, that's why it's by address
// we need to place the define before the structs bc of the pragma
int main()
{

	Queue queue = {
		.head = NULL,
		.tail = NULL
	};
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

			queue = put(queue, stud);
			printStudent(queue.tail->info);
			printStudent(queue.head->info);
			//stud = get(&queue);
			//printStudent(stud);


		}

		deleteQueue(&queue);
	}
}

QueueNode* createNode(Student* stud)
{	
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	
	newNode->info = stud;
	newNode->next = NULL;

	return newNode;
}
// why do we pass it by value
Queue put(Queue queue, Student* stud) {
	QueueNode* queueNode = createNode(stud);
	if (queue.head == NULL && queue.tail == NULL) queue.head = queueNode;
	else queue.tail->next = queueNode;

	queue.tail = queueNode;
	return queue;
}
// when we search for sth we initialize it with NULL
Student* get(Queue* queue) {
	Student* stud = NULL;
	if (queue->head != NULL && queue->tail != NULL)
	{
		stud = queue->head->info;
		QueueNode* tmp = queue->head;
		queue->head = tmp->next;
		if (queue->head == NULL) {
			queue->tail = NULL;
		}
		free(tmp);
	}

	return stud;
}

void deleteQueue(Queue* queue) {
	Student* stud = NULL;
	while ((stud = get(queue)) != NULL)
	{
		printStudent(stud);
		deleteStudent(stud);
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

// getting from the beginning
// we can't get it from the head, we traverse bc we don't know how many elements, for O(1) we need to keep track of the tail
// we use a dummy structure
//we implement arrays at home

//get, put O(1), same complexity
//adt structure which implement insertion and extraction