#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define SIDE 5
#define NB_NUMBS 100
#define NB_BINGOS 100

#define DEBUG 0

typedef struct {
	short int value;
	bool isset : 1;
} cell;


typedef struct {
	cell board[SIDE][SIDE];
} bingo;

void parsefile (int numbers[NB_NUMBS], bingo bingos[NB_BINGOS]) {
	FILE* file = fopen("input.txt", "r");
	
	// parsig first line
	char firstline[300];
	char* read = firstline;
	char* nextnum;
	fscanf(file, "%s", firstline);

	for (int i = 0 ; i < NB_NUMBS ; i++) {
		numbers[i] = (int) strtol(read, &nextnum, 10);
		read = nextnum + 1;
	}

	// parsing bingos
	for (int i = 0 ; i < NB_BINGOS ; i++) {
		for (int j = 0 ; j < SIDE ; j++) {
			for (int k = 0 ; k < SIDE ; k++) {
				assert(
					fscanf(file, "%hi",
						&(bingos[i].board[j][k].value))
					!= EOF
				);
				bingos[i].board[j][k].isset = false;	
			}
			if (DEBUG) {
				for (int k = 0 ; k < SIDE ; k++) {
					printf("%2hi ", bingos[i].board[j][k].value);
				}
				putchar('\n');
			}
		}
		if (DEBUG) putchar('\n');
	}
	
	fclose(file);
}

bool have_won (bingo b) {
	int nb_col;
	for (int i = 0 ; i < SIDE ; i++) {
		nb_col = 0;
		for (int j = 0 ; j < SIDE ; j++) {
			nb_col += (int) b.board[i][j].isset;
		}
		if (nb_col == SIDE) return true;
	}

	int nb_row;
	for (int i = 0 ; i < SIDE ; i++) {
		nb_row = 0;
		for (int j = 0 ; j < SIDE ; j++) {
			nb_row += (int) b.board[j][i].isset;
		}
		if (nb_row == SIDE) return true;
	}
	return false;
}

void place_number (int num, bingo bingos[NB_BINGOS], int winners[NB_BINGOS], int winning_number[NB_BINGOS]) {
	bool had_new = false;
	if (DEBUG) printf("call %i\n", num);
	for (int i = 0 ; i < NB_BINGOS ; i++) {
		if (DEBUG) printf("placing in %i\n", i);

		// filtering already finished
		int index;
		bool already = false;
		for (index = 0 ; winners[index] >= 0 && index < NB_BINGOS ; index++) {
			if (winners[index] == i) {
				already = true;
				if (DEBUG) printf("%i viens d'etre recalé a l'entrée\n", i);
			}
		}
		if (already) continue;

		for (int j = 0 ; j < SIDE ; j++) {
			for (int k = 0 ; k < SIDE ; k++) {
				if (bingos[i].board[j][k].value == num) {
					bingos[i].board[j][k].isset = true;
					had_new = true;
				}
			}
		}
		if (had_new) {
			if (have_won(bingos[i])) {
				if (DEBUG) printf("Bingo ! n°%i won in %ith place with %i\n", i, index, num);
				winners[index] = i;
				winning_number[index] = num;
			}
		}
		had_new = false;
	}
}

int sum_no_placed (bingo b) {
	int sum = 0;

	for (int i = 0 ; i < SIDE ; i++) {
		for (int j = 0 ; j < SIDE ; j++) {
			 if (! b.board[i][j].isset) {
				 sum += b.board[i][j].value;
			 }
		}
	}
	return sum;
}

void pb1et2 () {
	/*******************\
	|*     PARSING     *|
	\*******************/
	int numbers[NB_NUMBS];
	bingo bingos[NB_BINGOS];
	parsefile(numbers, bingos);

	/***********************\
	|*    Problem 1 & 2    *|
	\***********************/

	int winners[NB_BINGOS];
	int winning_number[NB_BINGOS];
	for (int i = 0 ; i < NB_BINGOS ; i++) {
		winners[i] = -1;
	}

	for (int i = 0 ; i < NB_NUMBS && winners[NB_BINGOS-1] < 0; i++) {
		place_number(numbers[i] , bingos, winners, winning_number);
	}

	int sum_first_winner = sum_no_placed(bingos[winners[0]]);
	int sum_last_winner = sum_no_placed(bingos[winners[NB_BINGOS-1]]);

	if (DEBUG) {
		for (int i = 0 ; i < NB_BINGOS ; i++) {
			printf(" %i : %i |", winners[i], winning_number[i]);
		}
		putchar(10);
	}

	printf("Résultat pb1 : %i * %i = %i\n"
	      , winning_number[0], sum_first_winner
		  , winning_number[0]*sum_first_winner);
	printf("Résultat pb2 : %i * %i = %i\n"
	      , winning_number[NB_BINGOS-1], sum_last_winner
		  , winning_number[NB_BINGOS-1] *sum_last_winner);
}

int main () {
	pb1et2();
	return 0;
}