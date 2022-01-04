#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define INPUT_FILE "input_test.txt" 
//#define WIDTH 10
//#define HEIGHT 9

#define INPUT_FILE "input.txt" 
#define WIDTH 139
#define HEIGHT 137

#define DEBUG 0
#define foor(x, MIN, MAX) for(int (x) = 0; (x) < (MAX) ; (x)++)

void parsefile (char map[HEIGHT][WIDTH]) {
	FILE* file = fopen(INPUT_FILE, "r");
	
	int i = 0;
	char line[WIDTH+1];
	while (fscanf(file, "%s", line)!= EOF) {	
		foor (j, 0, WIDTH) {
			map[i][j] = line[j];
			assert(line[j] == '.' || line[j] == 'v' || line[j] == '>');
		}
		i++;
	}
	assert(i == HEIGHT);
	fclose(file);
}

void printMap (char map[HEIGHT][WIDTH]) {
	foor(i, 0, HEIGHT) {
		foor(j, 0, WIDTH) {
			putchar(map[i][j]);
		}
		putchar('\n');
	}
}

void copy(char map[HEIGHT][WIDTH], char nmap[HEIGHT][WIDTH]) {
	foor(i, 0, HEIGHT) {
		foor(j, 0, WIDTH) {
			nmap[i][j] = map[i][j];
		}
	}
}

int move (char map[HEIGHT][WIDTH]) {
	static char nmap[HEIGHT][WIDTH];
	copy(map, nmap);

	int moved = 0;


	foor(i, 0, HEIGHT) {
		foor(j, 0, WIDTH) {
			if (map[i][j] == '>' && map[i][(j+1)%WIDTH] == '.') {
				nmap[i][j] = '.';
				nmap[i][(j+1)%WIDTH] = '>';
				//printf("> %i %i\n", i, j);
				moved++;
			}
		}
	}

	copy(nmap, map);


	foor(i, 0, HEIGHT) {
		foor(j, 0, WIDTH) {
			if (map[i][j] == 'v' && map[(i+1)%HEIGHT][j] == '.') {
				nmap[i][j] = '.';
				nmap[(i+1)%HEIGHT][j] = 'v';
				//printf("v %i %i\n", i, j);
				moved++;
			}
		}
	}

	copy(nmap, map);

	return moved;
}


void pb1et2 () {
	// initialisation
	static char map[HEIGHT][WIDTH];
	parsefile(map);
	printMap(map);


	// Problem 1
	
	int turns = 0;
	int moved = 1;
	while (moved != 0) {
		moved = move(map);
		turns++;
		printf("Turn %i ;  moved %i\n", turns, moved);
		printMap(map);
	}

	// Problem 2

	printf("Résultat pb1 : %i\n", turns);
	printf("Résultat pb2 : %i\n", 0);
}

int main () {
	pb1et2();
	return 0;
}