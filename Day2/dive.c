#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const char* filename = "input.txt";

void pb1 () {
	FILE* file = fopen(filename, "r");
	assert(file!=NULL);

	char instruc[10];
	int nb, horiz=0, depth=0;
	while (fscanf(file, "%s %i", instruc, &nb) != EOF) {
		if (strcmp(instruc, "forward")==0) {
			horiz += nb;
		} else if (strcmp(instruc, "down")==0) {
			depth += nb;
		} else if (strcmp(instruc, "up")==0) {
			depth -= nb;			
		}
	}


	printf("Résultat pb1 : %i\n", horiz*depth);
	fclose(file);
}

void pb2 () {
	FILE* file = fopen(filename, "r");
	assert(file!=NULL);

	char instruc[10];
	int nb, horiz=0, depth=0, aim=0;
	while (fscanf(file, "%s %i", instruc, &nb) != EOF) {
		if (strcmp(instruc, "forward")==0) {
			horiz += nb;
			depth += nb*aim;
		} else if (strcmp(instruc, "down")==0) {
			aim += nb;
		} else if (strcmp(instruc, "up")==0) {
			aim -= nb;			
		}
	}

	printf("Résultat pb2 : %i\n", horiz*depth);
	fclose(file);
}

int main () {
	pb1();
	pb2();
	return 0;
}