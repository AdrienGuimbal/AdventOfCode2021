#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define INPUT_FILE "input_test.txt" 
//#define NB 10

#define INPUT_FILE "input.txt" 
#define NB 1000

#define abs(b) ((b)>0? (b) : -(b))

#define DEBUG 0

void parsefile (int crab[NB]) {
	FILE* file = fopen(INPUT_FILE, "r");
	int i = 0;
	while (fscanf(file, "%i,", crab+i)!= EOF && i<NB) {
		i++;
	}
	
	fclose(file);
}

void pb1et2 () {
	// initialisation
	int crab[NB];
	parsefile(crab);
	//for (int i = 0 ; i < NB ; i++)
	//	printf("%i\n", crab[i]);
	
	int max = crab[0];
	for (int i = 1 ; i < NB ; i++) {
		if (crab[i]>max)
			max=crab[i];
	}

	// Problem 1
	
	int* fuels  = calloc(max, sizeof(int));
	for (int k = 0 ; k < max ; k++) {
		for (int i = 0 ; i < NB ; i++) {
			fuels[k] += abs(k - crab[i]);
		}
	}

	int min_fuel = fuels[0];
	for (int k = 1 ; k < max ; k++) {
		if (fuels[k]<min_fuel) {
			min_fuel = fuels[k];
		}
	}

	// Problem 2

	int* fuels2  = calloc(max, sizeof(int));
	int n;
	for (int k = 0 ; k < max ; k++) {
		for (int i = 0 ; i < NB ; i++) {
			n = abs(k - crab[i]);
			fuels2[k] += n*(n+1)/2;
		}
	}

	int min_fuel2 = fuels2[0];
	for (int k = 1 ; k < max ; k++) {
		if (fuels2[k]<min_fuel2) {
			min_fuel2 = fuels2[k];
			printf("%i\n", k);
		}
	}

	// Output
	printf("Résultat pb1 : %i\n", min_fuel);
	printf("Résultat pb2 : %i\n", min_fuel2);
}

int main () {
	pb1et2();
	return 0;
}