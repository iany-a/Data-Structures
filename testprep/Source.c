#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#pragma pack(1)

typedef struct Student {
	char* name;
}Student, *pStudent;

typedef struct SLL {
	Student* data;
	struct SLL* next;
}SLL, *pSLL;

typedef struct DLL {
	Student* data;
	struct DLL* prev;
	struct DLL* next;
} DLL, *pDLL;

Student* createStudent(char* name) {
	Student* stud = (Student*)malloc(sizeof(Student));
	if (stud) {
		stud->name = (char*)malloc(strlen(name) + 1);
		if (stud->name) strcpy_s(stud->name, strlen(name) + 1, name);
	}
	return stud;
}

void printStudent(Student* stud) {
	printf("Name: %s\n", stud->name);
}

void deleteStudent(Student* stud) {
	if (stud) {
		if (stud->name) {
			free(stud->name);
			stud->name = NULL;
		}
		free(stud);
		stud = NULL;
	}
}

void insertSingly(SLL** head, Student* s) {
	pSLL sll = (pSLL)malloc(sizeof(SLL));
	if (sll) {
		sll->data = s;
		sll->next = *head;
		*head = sll;
	}
}

void insertDoubly(DLL** head, Student* s) {
	pDLL dll = (pDLL)malloc(sizeof(DLL));
	if (dll) {
		dll->data = s;
		dll->next = *head;
		dll->prev = NULL;
		if (*head) {
			(*head)->prev = dll;
		}
		*head = dll;
	}
}




int main() {
	Student* s1 = createStudent("Jack");
	Student* s2 = createStudent("Marry");
	Student* s3 = createStudent("Dan");
	Student* s4 = createStudent("Wilma");
	Student* s5 = createStudent("Jenny");

	printStudent(s1);
	deleteStudent(s1);






	return 0;
}

