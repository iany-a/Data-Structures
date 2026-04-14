#include "Student.h"
#include <stdio.h>

Student* createStudent(unsigned int regNo, short int groupNo, const char* name) { //const needed
	//to prevent modifying the data
	//reading data is done from outer layer Student*, then the inner struct variables e.g. regNo, etc
	Student* pStud = (Student*)malloc(sizeof(Student));
	if (pStud != NULL) {
		pStud->regNumber = regNo;
		pStud->groupNumber = groupNo;
		pStud->name = (char*)malloc(strlen(name) + 1); //+1 for the delimiter
		if (pStud->name != NULL) {
			strcpy_s(pStud->name, strlen(name) + 1, name);
		}
		else {
			free(pStud); //LOGIC: if the student name does not exist, do not create the student
			pStud = NULL; //avoid dangling pointer
		}
	}
	return pStud;
}
void printStudent(Student* pStud) {
	if (pStud != NULL) {
		printf("RegNumber=%d, GroupNumber=%d, name=%s\n",
			pStud->regNumber, pStud->groupNumber, pStud->name);

	}
}

void deleteStudent(Student* pStud) {
	if (pStud != NULL) {
		if (pStud->name != NULL) {
			free(pStud->name);
		}
		free(pStud);
	}
}