#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define INPUT_FILE "input_test.txt" 
//#define NB 10

#define INPUT_FILE "input.txt" 
#define NB 100

#define foor(x, min, max) for (int (x) = min ; (x) < (max) ; (x)++)
#define BEAUCOUP 99999
#define NB5 5*NB

#define DEBUG 0

void parsefile (char map[NB][NB]) {
	FILE* file = fopen(INPUT_FILE, "r");
	int i = 0;
	while (fscanf(file, "%s", map[i])!= EOF) {	
		//for(int j = 0 ; j < NB ; j++) {
		foor(j, 0, NB) {
			map[i][j] -= '0';
			//printf("%hhi ", map[i][j]);
		}
		i++;
	}

	fclose(file);
}

void init_new_map(char new_map[5*NB][5*NB], char map[NB][NB]) {
	for (int i = 0 ; i < 5*NB ; i++) {
		for (int j = 0 ; j < 5*NB ; j++) {
			new_map[i][j] = (i/NB + j/NB + map[i%NB][j%NB] -1) %9 + 1;
		}
	}
}

void lowest_unvisited (int* x, int* y, int cost[NB5][NB5], bool visited[NB5][NB5]) {
	int min_cost = BEAUCOUP;
	foor (i, 0, NB5) {
		foor (j, 0, NB5) {
			if (!visited[i][j] && cost[i][j] < min_cost) {
				min_cost = cost[i][j];
				*x = i;
				*y = j;
			}
		}
	}
	assert(!visited[*x][*y]);
}

void update_adjacents (int x, int y, int cost[NB5][NB5], char map[NB5][NB5]) {
	if (x > 0     && cost[x][y] + map[x-1][ y ] < cost[x-1][ y ]) cost[x-1][ y ] = cost[x][y] + map[x-1][ y ];
	if (x < NB5-1 && cost[x][y] + map[x+1][ y ] < cost[x+1][ y ]) cost[x+1][ y ] = cost[x][y] + map[x+1][ y ];
	if (y > 0     && cost[x][y] + map[ x ][y-1] < cost[ x ][y-1]) cost[ x ][y-1] = cost[x][y] + map[ x ][y-1];
	if (y < NB5-1 && cost[x][y] + map[ x ][y+1] < cost[ x ][y+1]) cost[ x ][y+1] = cost[x][y] + map[ x ][y+1];
}

void pb1et2 () {
	// initialisation

	static char map[NB][NB];
	parsefile(map);

	int res1, res2;
	// Problem 2

	static char newmap[NB5][NB5];
	init_new_map(newmap, map);

	static int cost[NB5][NB5];
	static bool visited[NB5][NB5];
	foor (i, 0, NB5) {
		foor (j, 0, NB5) {
			cost[i][j] = BEAUCOUP;
			visited[i][j] = false;
		}
	}
	
	int x=0, y=0;
	cost[0][0] = 0;
	while (!visited[NB5-1][NB5-1]) {
		lowest_unvisited(&x, &y, cost, visited);
		//printf("visite %i %i\n", x, y);
		update_adjacents(x, y, cost, newmap);
		visited[x][y] = true;
	}
	res1 = cost[NB-1][NB-1];
	res2 = cost[NB5-1][NB5-1];

	if (DEBUG) {
		foor (i, 0, NB5) {
			foor (j, 0, NB5) {
				if (cost[i][j] < BEAUCOUP)
					printf("%4i ", cost[i][j]);
				else 
					printf(" BPC ");
			}
			putchar('\n');
		}
	}

	printf("Résultat pb1 : %i\n", res1);
	printf("Résultat pb2 : %i\n", res2);
}

int main () {
	pb1et2();
	return 0;
}
