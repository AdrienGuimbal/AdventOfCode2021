#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define INPUT_FILE "input_test.txt" 

#define INPUT_FILE "input.txt" 

#define DEBUG 0

void parsefile (char code[90][120]) {
	FILE* file = fopen(INPUT_FILE, "r");
	int i = 0;
	while (fscanf(file, "%s", code[i])!= EOF) {
		i++;	
	}
	
	fclose(file);
}

void pb1et2 () {
	// initialisation
	static char code[90][120];

	parsefile(code);
	
	for (int i = 0 ; i < 90 ; i++) {
		printf("%s\n", code[i]);
	}

	// Problem 1

	int par, sqr, curl, chev;
	int score = 0;
	for (int i = 0 ; i < 90 ; i++) {
		par = sqr = curl = chev = 0;
			putchar('a');
		for (int j = 0 ; j < 120 ; j++) {
			switch (code[i][j]) {
				case '(': par++; break;
				case ')': par--; break;
				case '[': sqr++; break;
				case ']': sqr--; break;
				case '{': curl++; break;
				case '}': curl--; break;
				case '<': chev++; break;
				case '>': chev--; break;
			}
			if (par < 0) {
				score += 3;
				j = 120;
			} else if (sqr < 0) {
				score += 57;
				j = 120;
			} else if (curl < 0) {
				score += 1197;
				j = 120;
			} else if (chev < 0) {
				score += 25137;
				j =120;
			}
		}
	}
	
	// Problem 2

	printf("Résultat pb1 : %i\n", score);
	printf("Résultat pb2 : %i\n", 0);
}

int main () {
	pb1et2();
	return 0;
}