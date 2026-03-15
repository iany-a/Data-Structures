#pragma once

typedef struct Student { //use typedef struct for cleaner code
	unsigned int regNumber;
	short int groupNumber;
	char* name;
} Student, * PStudent; //this is the typedef, we can declare multiple types

//Student* createStudent(unsigned int regNo, short int groupNo, const char* name);
Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
//void printStudent(Student* pStud);
//void deleteStudent(Student* pStud);