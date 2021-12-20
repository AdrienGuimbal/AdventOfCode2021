#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define DEBUG 0

typedef struct {
	int x1;
	int x2;
	int y1;
	int y2;
} Target;

bool in_target (int x, int y, Target target) {
	return x >= target.x1 && x <= target.x2 && y >= target.y1 && y <= target.y2;
}

bool passed_target (int x, int y, Target target) {
	return x > target.x2 || y < target.y1;
}

void step (int* x, int* y, int* vx, int* vy) {
	*x += *vx;
	*y += *vy;
	*vx -= (*vx == 0) ? 0 : (*vx > 0) ? 1 : -1;
	*vy -= 1;
}

void pb1et2 () {
	// Problem 1 & 2
	Target target1 = {269, 292, -68, -44};
	int x, y, vx, vy, apogee, max_y = 0;
	// apogee is for one shot, max_y if in general

	int nb_in = 0; // number of succesful shots 

	for (int vx0 = 0 ; vx0 < 1000 ; vx0++) {         // Yes it's brutforce, but for one time that using C 
		for (int vy0 = -1000 ; vy0 < 2000 ; vy0++) { // is an advantage I won't waste it for optimisation sake
			x = y = apogee = 0;
			vx = vx0;
			vy = vy0;
			while (!passed_target(x, y, target1) && !in_target(x, y, target1)) {
				step(&x, &y, &vx, &vy);
				if (y > apogee)
					apogee = y;
			}
			if (in_target(x, y, target1)) {
				nb_in++;
				if (apogee > max_y)
					max_y = apogee;
			} else {
				assert(passed_target(x, y, target1));
			}
		}
	}

	printf("Résultat pb1 : %i\n", max_y);
	printf("Résultat pb2 : %i\n", nb_in);
}

int main () {
	pb1et2();
	return 0;
}