#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define INPUT_FILE "input_test.txt" 
#define INPUT_FILE "input.txt" 

#define WHITE "\033[0;0m"
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE  "\033[1;34m"

#define DEBUG 0

void parsefile (int octopus[10][10]) {
	FILE* file = fopen(INPUT_FILE, "r");
	int i = 0;
	char line[11];
	while (fscanf(file, "%s", line)!= EOF) {
		for (int j = 0 ; j < 10 ; j++) {
			octopus[i][j] = line[j] - '0';
		}
		i++;
	}
	fclose(file);
}

void print_octo (int octopus[10][10]) {
	for (int i = 0 ; i < 10 ; i++) {
		for (int j = 0 ; j < 10 ; j++) {
			if (octopus[i][j] == 11) {
				printf(RED "*" WHITE);
			} else {
				printf("%i", octopus[i][j]);
			}
		}
		putchar('\n');
	}
	putchar('\n');
}

int itter_octo(int octopus[10][10]) {
	for (int i = 0 ; i < 10 ; i++) {
		for (int j = 0 ; j < 10 ; j++) {
			octopus[i][j] ++;
		}
	}

	bool new_flash = true;
	while (new_flash) {
		new_flash = false;	
		for (int i = 0 ; i < 10 ; i++) for (int j = 0 ; j < 10 ; j++) {
			if (octopus[i][j] == 10) {
				new_flash = true;
				octopus[i][j] = 11;
				for (int x = -1 ; x <= 1 ; x++) for (int y = -1 ; y <= 1 ; y++) {
					if (x+i >= 0 && x+i < 10 && y+j >= 0 && y+j < 10 && octopus[i+x][j+y] < 10) {
						octopus[i+x][j+y]++;
					}
				}
			}
		}
	}

	if (DEBUG) print_octo(octopus);
	
	int flashes = 0;
	for (int i = 0 ; i < 10 ; i++) for (int j = 0 ; j < 10 ; j++) {
		if (octopus[i][j] == 11) {
			octopus[i][j] = 0;
			flashes++;
		}
	}
	return flashes;
}

void pb1et2 () {
	// initialisation
	static int octopus[10][10];
	parsefile(octopus);
	if (DEBUG) print_octo(octopus);
	
	// Problem 1

	int flashes = 0;
	for (int i = 0 ; i < 100 ; i++) {
		flashes += itter_octo(octopus);
	}
	
	// Problem 2
	int turn = 100;
	int simultaneous = 0;
	while (simultaneous != 100) {
		turn ++;
		simultaneous = itter_octo(octopus);
	}
	
	printf("Résultat pb1 : %i\n", flashes);
	printf("Résultat pb2 : %i\n", turn);
}

int main () {
	pb1et2();
	return 0;
}