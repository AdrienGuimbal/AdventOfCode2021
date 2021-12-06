#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define INPUT_FILE "input_test.txt" 

#define INPUT_FILE "input.txt" 

#define DEBUG 0

void parsefile () {
	FILE* file = fopen(INPUT_FILE, "r");
	while (fscanf(file, "", NULL)!= EOF) {	
	}
	
	fclose(file);
}

void pb1et2 () {
	// initialisation

	parsefile();
	
	// Problem 1
	
	// Problem 2

	printf("Résultat pb1 : %i\n", 0);
	printf("Résultat pb2 : %i\n", 0);
}

int main () {
	pb1et2();
	return 0;
}