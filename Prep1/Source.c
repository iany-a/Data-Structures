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

Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);

int main()
{
	FILE* fp = fopen("Data.txt", "r");

	if (fp != NULL)
	{
		char line[LINE_BUFFER];
		//char* delimiter = ",";
		char delimiter[] = {',', '\n', '\0'}; //, is the first delimiter
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
			printStudent(stud);
			deleteStudent(stud);
		}
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
	if(pStud != NULL)
		printf("RegNo = %d, GroupNo = %d, Name = %s\n", 
			pStud->regNo, 
			pStud->groupNo, 
			pStud->name);
}

Student* createStudent(unsigned int regNo, 
						short int groupNo, 
						const char* name)
{	
	if (name == NULL || strlen(name) == 0){
		printf("Invalid student entry found: Invalid Name. Skipping line.\n______________________________\n");
		return NULL;
	}
	
	Student* pStud = (Student*)malloc(sizeof(Student));
	//this is the equivalent of Student* pStud = new Student(); in C++
	if (pStud != NULL) //if-else statement for defensive programming ensures that the
	//memory was correctly allocated before proceeding with assignment of struct members
	{
		pStud->regNo = regNo;
		pStud->groupNo = groupNo;
		pStud->name = (char*)malloc(strlen(name) + 1);
		//struct requires 2 allocations, one for the structure itself, one for the array of chars
		if (pStud->name != NULL){ //defensive programming as stated above
			strcpy_s(pStud->name, strlen(name) + 1, name);
			printf("Succesfully created student with name: %s\n", pStud->name);
		}
		else{
			free(pStud);
			pStud = NULL;
		}
	}
	return pStud;
}