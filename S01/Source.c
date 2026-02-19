#include "stdio.h"


void switchValues(int* a, int* b);
//this function switches ONLY the values of two integers, while their address remains the same



void main() {
	//printf("Hello G1067!\n");

	int x = 7;
	int y = 8;

	printf("x = %d, y = %d\n", x, y);
	printf("&x = %p, &y = %p\n", &x, &y);

	switchValues(&x, &y);

	printf("x = %d, y = %d\n", x, y);
	printf("&x = %p, &y = %p\n", &x, &y);

	//this proves that passing by value does not change the alocated memory address
	//for neither variable

}

void switchValues(int* a, int* b) { //REFERENCE PARAMETERS ARE NOT POSSIBLE IN C (&a, &b)
	printf("Inside the function: \n");

	printf("a = %d, b = %d\n", *a, *b);
	printf("&a = %p, &b = %p\n", &a, &b);

	int x = *a;
	*a = *b;
	*b = x;

	printf("a = %d, b = %d\n", *a, *b);
	printf("&a = %p, &b = %p\n", &a, &b);

	// int* a = &x;
	// &a = stack of switchvalue
	// a = content at &a
	// *a = content of pointer address
}


