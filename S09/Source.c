//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)
#define LINE_BUFFER 256
#define PQ_INITIAL_SIZE 3

typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name;
} Student, * PStudent;
//typedef struct Student Student;

typedef struct PQueue {
	Student** items;
	int size;
	int currentPosition;
}PriorityQueue;


Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);


//priority queue implementation is based on the regNo order (lower-higher)



void initPriorityQueue(PriorityQueue* pq) {
	if (pq->items == NULL || pq->size == 0 || pq->currentPosition == 0) {
		pq->items = (Student**)malloc(sizeof(Student*) * PQ_INITIAL_SIZE);
		memset(pq->items, 0, (sizeof(Student*))*PQ_INITIAL_SIZE);
		pq->size = PQ_INITIAL_SIZE;
		pq->currentPosition = 0;
	}
}

void reheapUp(PriorityQueue* pq, int childIndex) {
	int parentIndex = (childIndex - 1) / 2;
	//if (pq->currentPosition == parentIndex) {
	//	pq
	//}
	if (pq->items[parentIndex]->regNo < pq->items[childIndex]->regNo) {
		Student* tmp = pq->items[parentIndex];
		pq->items[parentIndex] = pq->items[childIndex];
		pq->items[childIndex] = tmp;
		reheapUp(pq, parentIndex);
	}
}

void reheapDown(PriorityQueue* pq, int parentIndex) {
	int childIndexLeft = 2 * parentIndex + 1;
	int childIndexRight = 2 * parentIndex + 2;
	int maxIndex = parentIndex;
	if (childIndexLeft < pq->currentPosition) {
		if (pq->items[parentIndex]->regNo < pq->items[childIndexLeft]->regNo) {
			maxIndex = childIndexLeft;
		}
		if ((childIndexRight < pq->currentPosition && pq->items[maxIndex]->regNo < pq->items[childIndexRight]->regNo)) {
			maxIndex = childIndexRight;
		}
		if (parentIndex != maxIndex) {
			Student* tmp = pq->items[maxIndex];
			pq->items[maxIndex] = pq->items[parentIndex];
			pq->items[parentIndex] = tmp;
			reheapDown(pq, maxIndex);
		}
	}
}


void enqueue(PriorityQueue* pq, Student* stud) {
	//check if there are valid positions in current pq
	if (pq && pq->size >= PQ_INITIAL_SIZE) {
		if (pq->currentPosition < pq->size) {
			//the new element will be placed at the end of the array, as this is the next available space
			pq->items[pq->currentPosition] = stud;
			//re-heap up
			reheapUp(pq, pq->currentPosition);
			pq->currentPosition++;
		}
	}
}

Student* dequeue(PriorityQueue* pq) {
	Student* studentResult = NULL;
	if (pq->currentPosition > 0) {
		studentResult = pq->items[0];
		pq->items[0] = pq->items[pq->currentPosition-1];
		pq->currentPosition--;
		reheapDown(pq, 0);
	}

	return studentResult;
}




int main()
{
	FILE* fp = fopen("Data.txt", "r");
	PriorityQueue pq = { .items = NULL, .size = 0, .currentPosition = 0 };
	initPriorityQueue(&pq);

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
			enqueue(&pq, stud);


		}
		Student* stud = dequeue(&pq);
	}
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
void printStudent(Student* pStud)
{
	if (pStud != NULL)
		printf("RegNo = %d, GroupNo = %d, Name = %s\n",
			pStud->regNo,
			pStud->groupNo,
			pStud->name);
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