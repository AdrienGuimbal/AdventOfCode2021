#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define INPUT_FILE "input.txt" 
//#define NB_PATERN 100
//#define FIRST_POLY_SIZE 20

#define INPUT_FILE "input_test.txt" 
#define NB_PATERN 16
#define FIRST_POLY_SIZE 5

#define DEBUG 0

typedef struct {
	char p1;
	char p2;
	char insert;
} patern;

typedef struct _p {
	char atom;
	struct _p* next;
} poly;

typedef struct _i{
	char to_insert;
	poly* at;
	struct _i* prev;
} instruction_stack;

void print_polymer (poly pol) {
	for(poly* tdl = &pol ; tdl != NULL ; tdl = tdl->next) {
		putchar(tdl->atom);
	}
	putchar('\n');
}

void print_patern (patern ptr) {
	printf("%c%c -> %c\n", ptr.p1, ptr.p2, ptr.insert);
}

void print_stack (instruction_stack* stack) {
	while (stack != NULL) {
		printf("insert %c between %c-%c\n", stack->to_insert, stack->at->atom, stack->at->next->atom);
		stack = stack->prev;
	}
}

void parsefile (patern paterns[NB_PATERN], poly* polymer) {
	FILE* file = fopen(INPUT_FILE, "r");

	char firstline[FIRST_POLY_SIZE];
	fscanf(file, "%s", firstline);
	
	*polymer = (poly) { firstline[0], NULL};

	poly* tdl = polymer; // tete de lecture
	
	for (char *c = firstline+1 ; *c ; c++ ) {
		tdl->next = malloc(sizeof(poly));
		tdl = tdl->next;
		tdl->atom = *c;
	}
	tdl->next = NULL;

	char p1, p2, r;
	int i = 0;
	while (fscanf(file, "\n%c%c -> %c", &p1, &p2, &r)!= EOF) {	
		paterns[i] = (patern) {p1, p2, r};
		i++;
	}
	fclose(file);
}

/*void polymerize(poly* polymer, patern paterns[NB_PATERN]) {
	instruction_stack* stack = NULL;
	instruction_stack* prevstack;
	for (poly *tdl = polymer ; tdl->next != NULL ; tdl = tdl->next) {
		//for (patern* pt = paterns ; pt < paterns + NB_PATERN ; pt++) {
		for (int i = 0 ; i < NB_PATERN ; i++) {
			if (paterns[i].p1 == tdl->atom && paterns[i].p2 == tdl->next->atom) {
				prevstack = stack;
				stack = malloc(sizeof(instruction_stack));
				stack->prev      = prevstack;
				stack->to_insert = paterns[i].insert;
				stack->at        = tdl;
			}
		}
	}

	if (DEBUG) print_stack(stack);

	for (instruction_stack* instruc = stack ; instruc != NULL ; instruc = prevstack) {
		poly* nv = malloc(sizeof(poly));
		nv->atom = instruc->to_insert;
		nv->next = instruc->at->next;
		instruc->at->next = nv;

		prevstack = instruc->prev;
		free(instruc);
	}
}*/

void polymerize(poly* polymer, patern paterns[NB_PATERN]) {
	for (poly *tdl = polymer ; tdl->next != NULL ; tdl = tdl->next) {
		for (int i = 0 ; i < NB_PATERN ; i++) {
			if (paterns[i].p1 == tdl->atom && paterns[i].p2 == tdl->next->atom) {
				poly* nv = malloc(sizeof(poly));
				nv->atom = paterns[i].insert;
				nv->next = tdl->next;
				tdl->next = nv;
				
				tdl = tdl->next; // go forwar to skip new
				i = NB_PATERN;
				//continue;
			}
		}
	}
}

int getres(poly polymer) {
	static int atom[26];
	for(poly* tdl = &polymer ; tdl != NULL ; tdl = tdl->next) {
		atom[tdl->atom - 'A'] ++;
	}
	int min = 0;
	int max = 0;
	for (int i = 0 ;  i < 26 ; i++) {
		if (DEBUG) printf("%i - ", atom[i]);
		if (min == 0) {
			min = atom[i];
			max = atom[i];
		} else if (atom[i] != 0) {
			if (atom[i] > max) {
				max = atom[i];
			}
			if (atom[i] < min) {
				min = atom[i];
			}
		}
	}
	if (DEBUG) printf("\nmin : %i  ;  max : %i\n", min, max);
	return max - min;
}

void pb1et2 () {
	// initialisation
	poly polymer;
	patern paterns[NB_PATERN];

	parsefile(paterns, &polymer);

	if (DEBUG) {
		print_polymer(polymer);
		for (int i = 0 ; i < NB_PATERN ;  i++) {
			print_patern(paterns[i]);
		}
	}

	// Problem 1
	if (DEBUG) print_polymer(polymer);
	for (int i = 0 ; i < 10 ; i++) {
		polymerize(&polymer, paterns);
		if (DEBUG) print_polymer(polymer);
	}

	int res1 = getres(polymer);

	printf("Résultat pb1 : %i\n", res1);
	// Problem 2

	if (DEBUG) print_polymer(polymer);
	for (int i = 10 ; i < 40 ; i++) {
		polymerize(&polymer, paterns);
		if (DEBUG) print_polymer(polymer);
	}

	int res2 = getres(polymer);


	printf("Résultat pb2 : %i\n", res2);
}

int main () {
	pb1et2();
	return 0;
}