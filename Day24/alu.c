#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "verif4.c"

//#define INPUT_FILE "input_test.txt" 

/* #define INPUT_FILE "input.txt" 

#define INP_SIZE 252
#define DEBUG 0
#define streq(s1, s2) (strcmp((s1), (s2))==0)

typedef enum {
	INP,
	ADD,
	MULT,
	DIV,
	MOD,
	EQL
} Operation;

typedef enum {W, X, Y, Z} Registry;

typedef struct {
	Operation op;

	Registry reg1;
	
	bool is_literal;
	union {
		Registry reg2;
		int value2;
	};
} Instruc;


void parsefile (Instruc program[INP_SIZE]) {
	FILE* file = fopen(INPUT_FILE, "r");
	
	int i = 0;

	char op[5], reg, val2[5];
	while (fscanf(file, "%s %c %s", op, &reg, val2)!= EOF) {	
		if (streq(op, "INP" )) program[i].op = INP ;
		if (streq(op, "ADD" )) program[i].op = ADD ; 
		if (streq(op, "MULT")) program[i].op = MULT;
		if (streq(op, "DIV" )) program[i].op = DIV ;
		if (streq(op, "MOD" )) program[i].op = MOD ;
		if (streq(op, "EQL" )) program[i].op = EQL ;
		switch (reg) {
			case 'w': program[i].reg1 = W; break;
			case 'x': program[i].reg1 = X; break;
			case 'y': program[i].reg1 = Y; break;
			case 'z': program[i].reg1 = Z; break;
			default :
				printf("%c not valid for reg\n", reg);
				assert(false);
		}
		program[i].is_literal = false;
		switch (val2[0]) {
			case 'w': program[i].reg2 = W; break;
			case 'x': program[i].reg2 = X; break;
			case 'y': program[i].reg2 = Y; break;
			case 'z': program[i].reg2 = Z; break;
			default :
				program[i].is_literal = true;
				program[i].value2 = atoi(val2);
				break;
		}
		i++;
	}
	
	fclose(file);
} */

void decrement(int nb[14]) {
	int i;
	for (i = 13 ; i >= 0 && nb[i] == 1; i--) {
		nb[i] = 9;
	}
	nb[i] --;
}

unsigned long int to_int(int nb[14]) {
	unsigned long int res = 0;
	for (int i = 0 ; i < 14; i++) {
		res = nb[i] + 10*res;
	}

	return res;
}

void pb1et2 () {
	// initialisation
	
	//Instruc program[INP_SIZE];
	//parsefile(program);
	
	// Problem 1
	int model_nb[14] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9};
	long int int_model_nb = 99999999999999L;
	while (MONAD(model_nb)!=0 && int_model_nb != 11111111111111L) {
		decrement(model_nb);
		if (int_model_nb % 1000000000 == 0) printf("%li\n", int_model_nb);
		int_model_nb --;
	}

	// Problem 2

	printf("Résultat pb1 : %lu\n", to_int(model_nb)); //99345000000000
	printf("Résultat pb2 : %i\n", 0);
}

int main () {
	pb1et2();
	return 0;
}