#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define foor(var, MIN, MAX) for(int var = (MIN); var < (MAX); var++)

//#define INPUT_FILE "input_test.txt" 
//#define SIZE 5
//#define MARGIN 60

#define INPUT_FILE "input.txt" 
#define SIZE 100
#define MARGIN 60

#define DEBUG 0

void parsefile (bool image[SIZE+2*MARGIN][SIZE+2*MARGIN], bool correction_table[512]) {
	FILE* file = fopen(INPUT_FILE, "r");
	char firstline[512];
	fscanf(file, "%s", firstline);
	
	foor (i, 0, 512) {
		correction_table[i] = firstline[i] == '#';
	}

	char line[SIZE+1];
	int line_num = 0;
	while (fscanf(file, "%s\n", line)!= EOF) {	
		foor (i, 0, SIZE) {
			image[MARGIN + line_num][MARGIN + i] = line[i] == '#';
		}
		line_num++;
	}
	assert(line_num == SIZE);
	fclose(file);
}

void print_image(bool image[SIZE+2*MARGIN][SIZE+2*MARGIN]) {
	foor (i, 0, SIZE+2*MARGIN) {
		foor (j, 0, SIZE+2*MARGIN) {
			putchar(image[i][j] ? '#' : '.');
		}
		putchar('\n');
	}
}

int n_value (int x, int y, bool image[SIZE+2*MARGIN][SIZE+2*MARGIN]) {
	return image[x-1][y-1] * 256 +
		   image[x-1][ y ] * 128 +
		   image[x-1][y+1] *  64 +
		   image[ x ][y-1] *  32 +
		   image[ x ][ y ] *  16 +
		   image[ x ][y+1] *   8 +
		   image[x+1][y-1] *   4 +
		   image[x+1][ y ] *   2 +
		   image[x+1][y+1] *   1 ;
}

void enhance (bool image[SIZE+2*MARGIN][SIZE+2*MARGIN], bool correction_table[512]) {
	static bool newimg [SIZE+2*MARGIN][SIZE+2*MARGIN];
	foor (i, 0, SIZE+2*MARGIN) {
		newimg[i][0] = correction_table[0] ^ image[i][0];
		newimg[0][i] = correction_table[0] ^ image[0][i];
		newimg[i][SIZE+2*MARGIN-1] = correction_table[0] ^ image[i][SIZE+2*MARGIN-1];
		newimg[SIZE+2*MARGIN-1][i] = correction_table[0] ^ image[SIZE+2*MARGIN-1][i];
	}

	foor (i, 1, SIZE+2*MARGIN - 1) {
		foor (j, 1, SIZE+2*MARGIN - 1) {
			newimg[i][j] = correction_table[n_value(i, j, image)];
		}
	}

	foor (i, 0, SIZE+2*MARGIN) {
		foor (j, 0, SIZE+2*MARGIN) {
			image[i][j] = newimg[i][j];
			newimg[i][j] = 0; // au cas où
		}
	}
}

int sum_all (bool image[SIZE+2*MARGIN][SIZE+2*MARGIN]) {
	int sum = 0;
	foor (i, 0, SIZE+2*MARGIN) {
		foor (j, 0, SIZE+2*MARGIN) {
			sum += image[i][j];
		}
	}
	return sum;
}

void pb1et2 () {
	// initialisation
	static bool correction_table[512];
	static bool image[SIZE+2*MARGIN][SIZE+2*MARGIN] = {0};

	parsefile(image, correction_table);
	
	if (DEBUG) print_image(image);

	// Problem 1
	
	enhance(image, correction_table);
	if (DEBUG) print_image(image);
	enhance(image, correction_table);
	if (DEBUG) print_image(image);

	int res1 = sum_all(image);

	// Problem 2

	foor (x, 2, 50) {
		enhance(image, correction_table);
	}

	int res2 = sum_all(image);

	printf("Résultat pb1 : %i\n", res1);
	printf("Résultat pb2 : %i\n", res2);
}

int main () {
	pb1et2();
	return 0;
}