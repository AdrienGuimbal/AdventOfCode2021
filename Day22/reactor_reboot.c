#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

//#define INPUT_FILE "input_test.txt" 
//#define NB_SECTORS 22

#define INPUT_FILE "input.txt" 
#define NB_SECTORS 420


#define REACTOR_SIZE 101
#define OFSET 50
#define DEBUG 0
#define foor(x, MIN, MAX) for (int (x) = (MIN); (x) < (MAX) ; (x)++)

typedef struct {
	bool consigne; // true->ON  false->OFF
	int x1;
	int x2;
	int y1;
	int y2;
	int z1;
	int z2;
} range;

void parsefile (range sector[NB_SECTORS]) {
	FILE* file = fopen(INPUT_FILE, "r");
	
	int i = 0;
	char instruc[4];
	// on x=38105..56989,y=-77417..-49521,z=-9791..7967
	while (fscanf(file, "%s x=%i..%i,y=%i..%i,z=%i..%i\n", instruc,
		&sector[i].x1, &sector[i].x2,
		&sector[i].y1, &sector[i].y2,
		&sector[i].z1, &sector[i].z2)!= EOF)
	{
		assert(instruc[0] == 'o' && (instruc[1] == 'f' || instruc[1] == 'n') && (instruc[2] == 'f' || instruc[2] == '\0'));
		sector[i].consigne = instruc[1] == 'n';
		i++;
	}
	
	fclose(file);
}

bool in_heart(range r){
	return r.x1 >= -50 && r.x2 <=50 &&  r.y1 >= -50 && r.y2 <=50 && r.z1 >= -50 && r.z2 <=50; 
}

void apply_instruc(range instruc, bool reactor[REACTOR_SIZE][REACTOR_SIZE][REACTOR_SIZE]) {
	printf("%i..%i, %i..%i, %i..%i\n", instruc.x1, instruc.x2, instruc.y1, instruc.y2, instruc.z1, instruc.z2);
	foor (i, instruc.x1, instruc.x2+1) {
		foor (j, instruc.y1, instruc.y2+1) {
			foor (k, instruc.z1, instruc.z2+1) {
				reactor[OFSET+i][OFSET+j][OFSET+k] = instruc.consigne;
			}
		}
	}
}

int sum_all (bool reactor[REACTOR_SIZE][REACTOR_SIZE][REACTOR_SIZE]) {
	int sum = 0;
	foor (i, 0, REACTOR_SIZE) {
		foor (j, 0, REACTOR_SIZE) {
			foor (k, 0, REACTOR_SIZE) {
				sum += reactor[i][j][k];
			}
		}
	}
	return sum;
}

void pb1et2 () {
	// initialisation
	static range sector[NB_SECTORS];
	parsefile(sector);
	
	static bool reactor[REACTOR_SIZE][REACTOR_SIZE][REACTOR_SIZE] = {0};
	// Problem 1
	for (int i = 0 ; i < NB_SECTORS ; i++) {
		if (in_heart(sector[i])) {
			apply_instruc(sector[i], reactor);
		}
	}

	int res1 = sum_all(reactor);
	
	// Problem 2

	printf("Résultat pb1 : %i\n", res1);
	printf("Résultat pb2 : %i\n", 0);
}

int main () {
	pb1et2();
	return 0;
}