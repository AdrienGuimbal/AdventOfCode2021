#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const char* filename = "input.txt";

int next_int (FILE* file) {
	int res;
	if (fscanf(file, "%i", &res) == EOF) return -1;
	return res;
}

void pb1 () {
	FILE* file = fopen(filename, "r");
	assert(file!=NULL);
	int prev = next_int(file);
	int res = 0;
	for (int i = next_int(file) ; i!=-1 ; i = next_int(file)) {
		if (i > prev) res++;
		prev = i;
	}
	printf("Résultat pb1 : %i\n", res);
	fclose(file);
}

void pb2 () {
	FILE* file = fopen(filename, "r");
	assert(file!=NULL);
	
	int A = next_int(file);
	int B = next_int(file);
	int C = next_int(file);
	B += C;
	A += B;

	int res = 0;
	for (int i = next_int(file) ; i!=-1 ; i = next_int(file)) {
		if (B+i > A) res++;
		A = B + i;
		B = C + i;
		C = i;
	}
	printf("Résultat pb2 : %i\n", res);
	fclose(file);
}

int main () {
	pb1();
	pb2();
	return 0;
}