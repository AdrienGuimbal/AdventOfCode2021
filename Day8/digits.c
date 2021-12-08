#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

//#define INPUT_FILE "input_test.txt" 

#define INPUT_FILE "input.txt" 
#define NB 200
#define adj -'a'
#define DEBUG 0

void parsefile (char input[NB][14][8]) {
	FILE* file = fopen(INPUT_FILE, "r");
	for (int i = 0 ; i < NB ; i++) {
		for (int j = 0 ; j <10 ; j++) {
			fscanf(file, "%s ", input[i][j]);
		}
		fscanf(file, " | ");
		for (int j = 10 ; j < 14 ; j++) {
			fscanf(file, "%s ", input[i][j]);
		}
	}
	
	fclose(file);
}

void removec (char c, char str[7]) {
	int idx = 0;
	for (int i = 0; i < 7 && str[i] !=0 ; i++) {
		str[idx] = str[i];
		if (str[i] != c) idx++;
	}
	str[idx] = 0
}

void leave (char c, char str[8]) {
	int idx = 0;
	for (int i = 0; i < 7 ; i++) {
		str[idx] = str[i];
		if (str[i] == c) idx++;
	}
	str[idx] = 0;
}

void is1 (char ab[2], char possible[7][8]) {
	for (int i=0 ; i<2 ; i++) {
		//leave  (ab[i], possible['c' adj]);
		//leave  (ab[i], possible['f' adj]);

		removec(ab[i], possible['a' adj]);
		removec(ab[i], possible['b' adj]);
		removec(ab[i], possible['d' adj]);
		removec(ab[i], possible['e' adj]);
		removec(ab[i], possible['g' adj]);
	}
}

void is7 (char ab[3], char possible[7][7]) {
	for (int i=0 ; i<3 ; i++) {
		//leave  (ab[i], possible['a' adj]);
		//leave  (ab[i], possible['c' adj]);
		//leave  (ab[i], possible['f' adj]);

		removec(ab[i], possible['b' adj]);
		removec(ab[i], possible['d' adj]);
		removec(ab[i], possible['e' adj]);
		removec(ab[i], possible['g' adj]);
	}
}

void is4 (char ab[4], char possible[7][7]) {
	for (int i=0 ; i<4 ; i++){
		//leave  (ab[i], possible['b' adj]);
		//leave  (ab[i], possible['c' adj]);
		//leave  (ab[i], possible['d' adj]);
		//leave  (ab[i], possible['f' adj]);

		removec(ab[i], possible['a' adj]);
		removec(ab[i], possible['e' adj]);
		removec(ab[i], possible['g' adj]);
	}
}

void decode (char line[14][8]) {
	#define ln "abcdefg"
	char posible[7][8] = {ln,ln,ln,ln,ln,ln,ln};
	
	for (int i = 0 ; i < 14 ; i++) {
		switch (strlen(line[i])) {
		case 2 :
			is1(line[i], posible);
			break;
		case 3 :
			is7(line[i], posible);
			break;
		case 4 :
			is4(line[i], posible);
			break;
		default:
			break;
		}
	}
	for (int i = 0 ; i < 7 ; i++) {
		printf("%c : %s\n", 'a'+i, posible[i]);
	}
}

void pb1et2 () {
	// initialisation

	char input[NB][14][8];

	parsefile(input);
	
	/* for (int i = 0 ; i < NB ; i++) {
		for (int j = 0 ; j < 10 ; j++) {
			printf("%s ", input[i][j]);
		}
		printf("| ");
		for (int j = 10 ; j < 14 ; j++) {
			printf("%s ", input[i][j]);
		}
		putchar('\n');
	} */

	decode(input[0]);

	// Problem 1
	
	// Problem 2

	printf("Résultat pb1 : %i\n", 0);
	printf("Résultat pb2 : %i\n", 0);
}

int main () {
	pb1et2();
	return 0;
}