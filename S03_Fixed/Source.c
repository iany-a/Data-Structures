#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Student.h"
#pragma pack(1) //needed for avoiding padding (2 bytes), packing the memory used to 10 bytes

#define LINE_BUFFER 256 //buffer for reading lines from the file with max length of 256

// Student ** * is passed with an additional * as the array is being modified in real time
//Student** insertIntoArray(int* size, Student** parray, Student stud) {
//	Student** tmp = parray; //tmp takes address of parray
//	++(*size); //size increase
//	parray = (Student**)malloc((sizeof(Student*)) * (*size)); //realloc parray wrt new size (what happens with old data?)
//	if ((*size - 1) > 0) {
//		for (register int i = 0; i < *size - 1; i++) {
//			parray[i] = tmp[i]; //this copies the initial data into the new location
//		}
//		free(tmp);
//
//	}
//	parray[(*size) - 1] = &stud;
//	return parray;
//}

Student** insertIntoArray(int* size, Student** pArray, Student* pStud) {
	(*size)++; //0 to 1 and so on, each time the method is called
	Student** tmp = (Student**)realloc(pArray, sizeof(Student*) * (*size)); //new array first with upsize
	//NB: Student** tmp = realloc(NULL, size); is the same as malloc(size);.
	if (tmp) { //this checks if tmp was allocated correctly
		pArray = tmp; //assign address of newly created array to the passed array
		pArray[*size - 1] = pStud; //add the current student (counting starts from index 0 always)
	}
	else { //if tmp was not allocated correctly, size goes back to initial value
		(*size)--;
	}

	return pArray;
}



int main() {

	FILE* fp = fopen("data.txt", "r");
	Student array[6];
	//Student* pArray[6]; //static array of 6 pointers

	//Student* array; //ptr  to a Student or an array of elements of type Student
	Student** pArray = NULL; //ptr to an array of Student structs
	int size = 0;

	if (fp != NULL) {
		char line[LINE_BUFFER];

		char* delimiter = ","; //delimiter definition 1
		//char token[] = {',' , '\0'}; //definition 2, equal to definition 1
		unsigned int regNo;
		short int groupNo;
		char* token = NULL;
		char* context = NULL;
		short index = 0;
		while (fgets(line, LINE_BUFFER, fp)) {
			token = strtok_s(line, delimiter, &context); //context is char*, function asks for char**
			//for this to work we pass the address of the pointer to a char, written as &context = & char* = char**
			regNo = atoi(token);
			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token);
			token = strtok_s(NULL, delimiter, &context);
			Student* stud = createStudent(regNo, groupNo, token);

			pArray = insertIntoArray(&size, pArray, stud);
			//pArray = instertIntoArray(&size, parray, stud);

			printStudent(stud);
			deleteStudent(stud);
		}

		
		//token[0] = '4';

	}


}





//HW: process

