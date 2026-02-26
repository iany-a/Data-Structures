#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1) //needed for avoiding padding (2 bytes), packing the memory used to 10 bytes
//unsigned int + short int + char* = 4B+2B+4B = 10B
//unsigned int + short int + padding + char* = 4B+2B+2B+4B = 12B

typedef struct Student { //use typedef struct for cleaner code
	unsigned int regNumber;
	short int groupNumber;
	char* name;
} Student, *PStudent; //this is the typedef, we can declare multiple types

//typedef struct Student Student; option 2

#define LINE_BUFFER 256 //buffer for reading lines from the file with max length of 256

Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);


int main() {
	//struct Student stud; working but annoying to write struct everytime
	//Student* stud1 = NULL; //this works after we setup the typedef
	//PStudent stud2 = NULL;
	//printf("sizeof(Student)=%d\n", sizeof(Student));

	//1. open file
	//2. read line 1 as char*
	//3. split the char* into multiple smaller char* using the delimiter
	FILE* fp = fopen("data.txt", "r");
	//Student* array = NULL;
	//Student arrayStatic[6];

	//printf("sizeof(array)=%d\n", sizeof(array));
	//printf("array=%p\n", array);
	//printf("&array=%p\n", &array);

	//printf("sizeof(array)=%d\n", sizeof(arrayStatic));
	//printf("array+1=%p\n", arrayStatic+1);
	//printf("&array+!=%p\n", &arrayStatic+1);


	

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



//malloc:
// does not know the data type you allocate the memory for, hence it returns a pointer to void
// that is why we need to tell malloc what type of data we need to return

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
			return NULL;
		}
	}
	return pStud;
}
