#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define INPUT_FILE "input_test.txt" 

#define INPUT_FILE "input.txt" 

#define DEBUG 0

void parsefile (long int popul[9]) {
	FILE* file = fopen(INPUT_FILE, "r");
	int val;
	while (fscanf(file, "%i,", &val)!= EOF) {	
		popul[val]++;
	}
	
	fclose(file);
}

void pb1et2 () {
	// initialisation

	long int popul[9] = {0};
	parsefile(popul);
	
	// Problem 1

	for (int t = 0 ; t < 80 ; t++) {
		long int copul = popul[0];
		for (int i = 0 ; i < 8 ; i++ ) {
			popul[i] = popul[i+1];
		}
		popul[6]+= copul;
		popul[8] = copul;
	}

	long int day80 = 0;
	for (int i = 0 ; i < 9 ; i++ ) {
		day80 += popul[i];
	}
	
	// Problem 2

	for (int t = 80 ; t < 256 ; t++) {
		long int copul = popul[0];
		for (int i = 0 ; i < 8 ; i++ ) {
			popul[i] = popul[i+1];
		}
		popul[6]+= copul;
		popul[8] = copul;
	}

	long int day256 = 0;
	for (int i = 0 ; i < 9 ; i++ ) {
		day256 += popul[i];
	}

	printf("Résultat pb1 : %li\n", day80);
	printf("Résultat pb2 : %li\n", day256);
}

int main () {
	pb1et2();
	return 0;
}