#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define P1_START 6 // personal
//#define P1_START 4 // test
#define P2_START 8

#define DEBUG 0

typedef struct Player {
	int pos;
	int score;
} Player;

int dice_state = 100;
int nb_dice_rolls = 0;

int rolldice () {
	nb_dice_rolls ++;
	dice_state ++;
	if (dice_state > 100)
		dice_state = 1;
	return dice_state;
}

void pb1 () {
	// initialisation
	Player players[2];
	players[0].pos   = P1_START; // player 1
	players[0].score = 0;
	players[1].pos   = P2_START; // player 2
	players[1].score = 0;

	
	// Problem 1

	int turnTo = 0; // player 1 starts
	int dice_res;
	bool have_win = false;
	while (! have_win) {
		dice_res = rolldice() + rolldice() + rolldice();
		//players[turnTo].pos = (players[turnTo].pos + dice_res - 1) % 9 + 1;
		
		players[turnTo].pos += dice_res;
		while (players[turnTo].pos > 10)
			players[turnTo].pos -= 10;
		
		players[turnTo].score += players[turnTo].pos;
		if (players[turnTo].score >= 1000)
			have_win = true;
		
		printf("player %i : score =%3i   pos =%3i   dice =%3i   dice_state =%3i\n", turnTo+1, players[turnTo].score, players[turnTo].pos, dice_res, dice_state);
		turnTo = !turnTo;
	}
	
	printf("player %i won, with %i at %i; player %i lose with %i at %i ; after %i rolls\n",
		!turnTo, players[!turnTo].score, players[!turnTo].pos,
		 turnTo, players[ turnTo].score, players[ turnTo].pos, nb_dice_rolls);

	long int res1 = players[turnTo].score * nb_dice_rolls;

	// Problem 2

	printf("Résultat pb1 : %i * %i = %li\n",players[turnTo].score, nb_dice_rolls, res1);
}

int main () {
	pb1();
	return 0;
}