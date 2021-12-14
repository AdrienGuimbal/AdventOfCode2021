#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>

#define WHITE "\033[0;0m"
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE  "\033[1;34m"

//#define INPUT_FILE "input_test.txt" 
//#define NB 10

#define INPUT_FILE "input.txt" 
#define NB 100

#define DEBUG 0

void parsefile (char map[NB][NB]) {
	FILE* file = fopen(INPUT_FILE, "r");
	int i = 0;
	while (fscanf(file, "%s", map[i])!= EOF) {	
		i++;
	}
	
	fclose(file);
}

int contagion (int x, int y, char map[NB][NB], char zone) {
	if (x < 0 || x >= NB || y < 0 || y >= NB) return 0;
	if (map[x][y] >= '9') return 0;
	
	map[x][y] = zone;
	return contagion(x+1,  y , map, zone) +
	       contagion(x-1,  y , map, zone) +
	       contagion( x , y+1, map, zone) +
	       contagion( x , y-1, map, zone) + 1;
	
}

void pb1et2 () {
	// initialisation
	static char map[NB][NB];
	parsefile(map);
	
	// Problem 1
	
	if (DEBUG) {
		for (int i = 0 ; i < NB ; i++) {
			for (int j = 0 ; j < NB ; j++) {
				if (map[i][j] == '9') printf(BLUE);
				printf("%c",  map[i][j]);
				if (map[i][j] == '9') printf(WHITE);
			}
			putchar('\n');
		}
	}

	int danger = 0;
	int nb_danger = 0;
	static int dangers_zones[220][2] = {0};

	for (int i = 0 ; i < NB ; i++) {
		for (int j = 0 ; j < NB ; j++) {
			bool up    = j == 0     || map[i][j] < map[ i ][j-1];
			bool down  = j == NB -1 || map[i][j] < map[ i ][j+1];
			bool left  = i == 0     || map[i][j] < map[i-1][ j ];
			bool right = i == NB -1 || map[i][j] < map[i+1][ j ];
			if (up && down && left && right) {
				danger += map[i][j] - '0' + 1;
				map[i][j] = '*';
				dangers_zones[nb_danger][0] = i;
				dangers_zones[nb_danger][1] = j;
				nb_danger++;
			}
		}
	}
	
	printf("-------------\nnb d :%i\n", nb_danger);

	// Problem 2
	char zone = 'A';
	static int zones_size[220];
	int x, y, nb_zones=0;

	for (int i = 0 ; i < nb_danger ; i++) {
		x = dangers_zones[i][0];
		y = dangers_zones[i][1];
		zones_size[nb_zones] += contagion(x, y, map, zone);
		if (zones_size[nb_zones]) {
			nb_zones++;
			zone++;
			if (zone > 'z') {
				printf("\nletter overflow\n");
				zone = 'A';
			}
		}
		putchar(zone);
	}
	putchar(10);
	
	for (int i = 0 ; i < NB ; i++) {
		for (int j = 0 ; j < NB ; j++) {
			if (map[i][j] > '9') {
				printf("%c",  map[i][j]);
			} else if (map[i][j] > '9') {
				printf(BLUE "%c" WHITE,  map[i][j]);
			} else if (map[i][j] == '*') {
				printf(RED "%c" WHITE,  map[i][j]);
			} else {
				putchar('.');
			}
		}
		putchar('\n');
	}

	int max1 = 0;
	int max2 = 0;
	int max3 = 0;
	for (int i = 1 ; i < nb_zones ; i++) {
		printf("%i ", zones_size[i]);
		if (zones_size[i] > max1) {
			max3 = max2;
			max2 = max1;
			max1 = zones_size[i];
		} else if (zones_size[i] > max2) {
			max3 = max2;
			max2 = zones_size[i];
		} else if (zones_size[i] > max3) {
			max3 = zones_size[i];
		}
	}

	printf("Résultat pb1 : %i\n", danger);
	printf("Résultat pb2 : %i * %i * %i = %i\n", max1, max2, max3, max1 * max2 * max3);
}

int main () {
	pb1et2();
	return 0;
}