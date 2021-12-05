#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define NB_VENT 10
//#define INPUT_FILE "input_test.txt" 
//#define MAX_CORD 10

#define NB_VENT 500
#define INPUT_FILE "input.txt" 
#define MAX_CORD 1000

#define DEBUG 0

#define abs(i) ((i)<0? -(i) : (i))

typedef struct {
	short int x1;
	short int y1;
	
	short int x2;
	short int y2;
} ventpair;


void parsefile (ventpair vents[NB_VENT]) {
	FILE* file = fopen(INPUT_FILE, "r");
	int i = 0;
	while (
		fscanf(file,"%hi,%hi -> %hi,%hi"
		     , &vents[i].x1, &vents[i].y1
			 , &vents[i].x2, &vents[i].y2)!= EOF
		) {	
		i++;
	}
	
	fclose(file);
}

void swap (short int* a, short int* b) {
	short int temp = *a;
	*a = *b;
	*b = temp;
}

void add_straight_vent (ventpair ch, short int map[MAX_CORD][MAX_CORD]) {
	if (ch.x1 != ch.x2 && ch.y1 != ch.y2) return;

	if (ch.y1 > ch.y2)
		swap(&ch.y1, &ch.y2);
	if (ch.x1 > ch.x2)
		swap(&ch.x1, &ch.x2);
	
	for (int i = ch.x1; i <= ch.x2  ; i++) {
		for (int j = ch.y1 ; j <= ch.y2 ; j++) {
			map[i][j] ++;
		}
	} 
}

void add_diag_vent (ventpair ch, short int map[MAX_CORD][MAX_CORD]) {
	if (ch.x1 == ch.x2 || ch.y1 == ch.y2) return;
	if (abs(ch.x2 - ch.x1) != abs(ch.y2 - ch.y1)) return;

	if (ch.x1 > ch.x2) {
		//printf("Swap\n");
		swap(&ch.x1, &ch.x2);
 		swap(&ch.y1, &ch.y2);
	}
	if (ch.y1 < ch.y2) {
		for (int i = 0 ; i <= ch.x2 - ch.x1 ; i++) {
			map[ch.x1+i][ch.y1+i] ++;
		}
	} else if (ch.y1 > ch.y2) {
		for (int i = 0 ; i <= ch.x2 - ch.x1 ; i++) {
			//printf("%i %i", ch.x1+i, ch.y1-i);
			map[ch.x1+i][ch.y1-i] ++;
		}
	}
}

void printmap (short int map[MAX_CORD][MAX_CORD]) {
	for (int j = 0 ; j < MAX_CORD ; j++) {
		for (int i = 0 ; i < MAX_CORD ; i++) {
			if (map[i][j]==0) printf(".");
			else printf("%i", map[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
}

void pb1et2 () {
	// initialisation
	ventpair vents[NB_VENT];
	parsefile(vents);

	short int map[MAX_CORD][MAX_CORD];
	for (int i = 0 ; i < MAX_CORD ; i++) for (int j = 0 ; j < MAX_CORD ; j++) {
		map[i][j] = 0;
	}
	
	// Problem 1
	for (int i = 0 ; i < NB_VENT ; i++) {
		add_straight_vent(vents[i], map);
	}

	if (DEBUG) printmap(map);

	int danger_zones1 = 0;
	for (int i = 0 ; i < MAX_CORD ; i++) for (int j = 0 ; j < MAX_CORD ; j++) {
		danger_zones1 += (int) map[i][j] >= 2;
	}

	// Problem 2

	for (int i = 0 ; i < NB_VENT ; i++) {
		//printf("turn %i\n", i);
		add_diag_vent(vents[i], map);
	}

	int danger_zones2 = 0;
	for (int i = 0 ; i < MAX_CORD ; i++) for (int j = 0 ; j < MAX_CORD ; j++) {
		danger_zones2 += (int) map[i][j] >= 2;
	}

	printf("Résultat pb1 : %i\n", danger_zones1);
	printf("Résultat pb2 : %i\n", danger_zones2);
}

int main () {
	pb1et2();
	return 0;
}