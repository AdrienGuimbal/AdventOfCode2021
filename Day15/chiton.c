#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define INPUT_FILE "input_test.txt" 
//#define NB 10

#define INPUT_FILE "input.txt" 
#define NB 100

#define forRange(x, max) for (int (x) = 0 ; (x) < (max) ; (x)++)

#define DEBUG 0

void parsefile (char map[NB][NB]) {
	FILE* file = fopen(INPUT_FILE, "r");
	int i = 0;
	while (fscanf(file, "%s", map[i])!= EOF) {	
		//for(int j = 0 ; j < NB ; j++) {
		forRange(j, NB) {
			map[i][j] -= '0';
			//printf("%hhi ", map[i][j]);
		}
		i++;
	}

	fclose(file);
}


int min (int a, int b) {
	return (a > b) ? b : a;
}

int brute_solve(int x, int y, int len, char map[len][len], int visited_path[len][len]) {
	if (visited_path[x][y] != 0) {
		return visited_path[x][y];
	}
	
	if (x == len-1 && y == len-1) {
		return map[x][y];
	}
	if (x < 0 || x == len || y < 0 || y == len ) {
		return 1e9;
	}

	int res = map[x][y] + min(brute_solve(x+1, y, len, map, visited_path), brute_solve(x, y+1, len, map, visited_path));
	visited_path[x][y] = res;
	return res;
}

void init_new_map(char new_map[5*NB][5*NB], char map[NB][NB]) {
	for (int i = 0 ; i < 5*NB ; i++) {
		for (int j = 0 ; j < 5*NB ; j++) {
			new_map[i][j] = (i/NB + j/NB + map[i%NB][j%NB] -1) %9 + 1;
		}
	}
}

void pb1et2 () {
	// initialisation

	static char map[NB][NB];
	parsefile(map);

	int res1, res2;
	// Problem 1
	{
		static int visited_path[NB][NB] = {0};
		res1 = brute_solve(0, 0, NB, map, visited_path) - map[0][0];
	}
	/*{
		static char new_map[NB*5][NB*5];
		init_new_map(new_map, map);
		
		static int visited_path[NB*5][NB*5] = {0};
		res2 = brute_solve(0, 0, 5*NB, new_map, visited_path) - map[0][0];
	}*/

	printf("Résultat pb1 : %i\n", res1);
	printf("Résultat pb2 : %i\n", res2);
}

int main () {
	pb1et2();
	return 0;
}
