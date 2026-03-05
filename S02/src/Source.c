#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Student.h"
#pragma pack(1) //needed for avoiding padding (2 bytes), packing the memory used to 10 bytes


#define LINE_BUFFER 256 //buffer for reading lines from the file with max length of 256




int main() {

	FILE* fp = fopen("data.txt", "r");

	if (fp != NULL) {
		char line[LINE_BUFFER];
		
		char* delimiter = ","; //delimiter definition 1
		//char token[] = {',' , '\0'}; //definition 2, equal to definition 1
		unsigned int regNo;
		short int groupNo;
		char* token = NULL;
		char* context = NULL;
		while (fgets(line, LINE_BUFFER, fp)) {
			token = strtok_s(line, delimiter, &context); //context is char*, function asks for char**
			//for this to work we pass the address of the pointer to a char, written as &context = & char* = char**
			regNo = atoi(token);
			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token);
			token = strtok_s(NULL, delimiter, &context);
			Student* stud = createStudent(regNo, groupNo, token);
			//arrayStatic[1] = *stud;
			//*(arrayStatic + 1) = *stud;
			//(arrayStatic + 1)[0] = *stud; //re-basing the array


			printStudent(stud);
			deleteStudent(stud);
		}
		
		
		//token[0] = '4';

	}


}


