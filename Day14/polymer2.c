#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INPUT_FILE "input.txt" 
#define NB_REAC 100
#define FIRST_POLY_SIZE 20

//#define INPUT_FILE "input_test.txt" 
//#define NB_REAC 16
//#define FIRST_POLY_SIZE 5

#define DEBUG 0

typedef struct {
	int patern;
	int liaison1;
	int liaison2;
} reaction;

// BCFHKNOPSV
int  char_to_index(char c) {
	switch (c) {
		case 'B': return 0; break;
		case 'C': return 1; break;
		case 'F': return 2; break;
		case 'H': return 3; break;
		case 'K': return 4; break;
		case 'N': return 5; break;
		case 'O': return 6; break;
		case 'P': return 7; break;
		case 'S': return 8; break;
		case 'V': return 9; break;
		default:
			printf("YOO %c %hhu\n",c,c);
			assert(false);
			break;
	}
}
char halfindex_to_char(int i) {
	switch (i) {
		case 0 : return 'B'; break;
		case 1 : return 'C'; break;
		case 2 : return 'F'; break;
		case 3 : return 'H'; break;
		case 4 : return 'K'; break;
		case 5 : return 'N'; break;
		case 6 : return 'O'; break;
		case 7 : return 'P'; break;
		case 8 : return 'S'; break;
		case 9 : return 'V'; break;
		default:
			printf("YOO %i\n",i);
			assert(false);
			break;
	}
}

void print_polymer (long int polymer[100]) {
	for (int i = 0 ; i < 100 ; i++) {
		if (polymer[i]!=0)
			printf("%c%c : %li\n", halfindex_to_char(i/10), halfindex_to_char(i%10), polymer[i]);
	}
}

void debug_polymer (long int polymer[100]) {
	for (int i = 0 ; i < 10 ; i++) {
		for (int j = 0 ; j < 10 ; j++) {
			printf("%c%c:%li  ", halfindex_to_char(i), halfindex_to_char(j), polymer[i*10+j]);
		}
		putchar('\n');
	}
}


void print_reactions (reaction reactions[NB_REAC]) {
	for (int i = 0 ; i < NB_REAC ; i++) {
		printf("%c%c -> %c%c %c%c\n",
			halfindex_to_char(reactions[i].patern / 10)  , halfindex_to_char(reactions[i].patern % 10),
			halfindex_to_char(reactions[i].liaison1 / 10), halfindex_to_char(reactions[i].liaison1 % 10),
			halfindex_to_char(reactions[i].liaison2 / 10), halfindex_to_char(reactions[i].liaison2 % 10));
	}
}

void parsefile (reaction reactions[NB_REAC], long int polymer[100], int* last) {
	FILE* file = fopen(INPUT_FILE, "r");

	char firstline[FIRST_POLY_SIZE];
	fscanf(file, "%s", firstline);
	
	for (char *c = firstline; c[1] ; c++) {
		polymer[ char_to_index(c[0]) * 10 + char_to_index(c[1]) ] ++;
		*last = char_to_index(c[1]);
	}


	char p1, p2, r;
	int i = 0;
	while (fscanf(file, "\n%c%c -> %c", &p1, &p2, &r)!= EOF) {	
		//printf("%c%c -> %c\n", p1, p2, r);
		reactions[i] = (reaction)
			{char_to_index(p1)*10 + char_to_index(p2),
		     char_to_index(p1)*10 + char_to_index( r),
		     char_to_index( r)*10 + char_to_index(p2)};
		i++;
	}
	fclose(file);
}

void polymerize (long int polymer[100], reaction reactions[NB_REAC]) {
	static long int nv_poly[100];
	
	for (int i = 0 ; i < 100 ; i++) {
		nv_poly[i] = 0;
	}
	
	for (int i = 0 ; i < 100 ; i++) {
		if (polymer[i] == 0) continue;
		bool reacted = false;
		
		for (int j = 0 ; j < NB_REAC ; j++) {
			if (reactions[j].patern == i) {
				nv_poly[reactions[j].liaison1] += polymer[i];
				nv_poly[reactions[j].liaison2] += polymer[i];
				reacted = true; break;
			}
		}
		if (!reacted) {
			printf("norecat");
			nv_poly[i] += polymer[i];
		}
	}
	for (int i = 0 ; i < 100 ; i++) {
		polymer[i] = nv_poly[i];
	}
}

int poly_length(long int polymer[100]) {
	long int s = 0;
	for (int i = 0 ; i < 100 ; i++ ) {
		s += polymer[i];
	}
	return s - 1;
}

long int getres (long int polymer[100], int last) {
	long int atoms[10] = {0};
	for (int i = 0 ; i < 100 ; i++ ) {
		//printf("%li ",polymer[i]);
		atoms[i/10] += polymer[i];
	}
	atoms[last]++;

	long int min = 0;
	long int max = 0;
	for (int i = 0 ;  i < 10 ; i++) {
		if (DEBUG) printf("%li - ", atoms[i]);
		if (min == 0) {
			min = atoms[i];
			max = atoms[i];
		} else if (atoms[i] != 0) {
			if (atoms[i] > max) {
				max = atoms[i];
			}
			if (atoms[i] < min) {
				min = atoms[i];
			}
		}
	}

	printf("\nmin : %li  ;  max : %li\n", min, max);
	return max - min;
}

void pb1et2 () {
	// initialisation
	static long int polymer[10 * 10];
	reaction reactions[NB_REAC];
	int last;

	parsefile(reactions, polymer, &last);

	//print_reactions(reactions);

	// Problem 1
	for (int i = 0 ; i < 10 ; i++) {
		polymerize(polymer, reactions);
		//printf("----- step %i , len = %li\n", i+1, poly_length(polymer));
		//print_polymer(polymer);
	}
	//print_polymer(polymer);

	long int res1 = getres(polymer, last);

	printf("Résultat pb1 : %li\n", res1);
	// Problem 2

	for (int i = 10 ; i < 40 ; i++) {
		polymerize(polymer, reactions);
	}
	print_polymer(polymer);

	long int res2 = getres(polymer, last);

	printf("Résultat pb2 : %li\n", res2);
}

int main () {
	pb1et2();
	return 0;
}