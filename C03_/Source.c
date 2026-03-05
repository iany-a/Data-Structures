#include <stdio.h>
#include <string.h>

typedef struct BitLetter {
	//in order from least important to most important
	short : 5;
	short sign : 1;
	short : 2;
} BitLetter;


void main() {
	char letter = 'A';
	BitLetter* pLetter = (BitLetter*) & letter;
	printf("Value before = %c\n", letter);
	pLetter->sign = !pLetter->sign;
	printf("Value after = %c\n", letter);


}