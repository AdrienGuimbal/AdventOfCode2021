#include <stdio.h>
#include "verif.c"
#include "verif2.c"

unsigned long int to_int(int nb[14]) {
	unsigned long int res = 0;
	for (int i = 0 ; i < 14; i++) {
		res = nb[i] + 10*res;
	}

	return res;
}

int main () {
	int nb[14] = {1,2,3,4,5,6,7,8,9,1,2,3,4,5};
	printf("%lli %lli\n", MONAD(nb), MONAD_OPTI(nb));
	
	int nb2[14] = {2,3,4,5,6,7,8,9,1,2,3,4,5,6};
	printf("%lli %lli\n", MONAD(nb2), MONAD_OPTI(nb2));
	
	int nb3[14] = {2,3,9,5,9,7,8,9,1,2,3,4,5,6};
	printf("%lli %lli\n", MONAD(nb3), MONAD_OPTI(nb3));
	
	int nb4[14] = {1,2,3,8,5,6,7,8,9,1,2,3,4,5};
	printf("%lli %lli\n", MONAD(nb4), MONAD_OPTI(nb4));

	int nb5[14] = {9,3,4,9,9,6,2,9,6,9,8,9,9,9};
	printf("Probable res 1 : %li -> %lli\n", to_int(nb5), MONAD(nb5));

	int nb6[14] = {1,1,1,6,4,1,1,8,1,2,1,4,7,1};
	printf("Probable res 2 : %li -> %lli\n", to_int(nb6), MONAD(nb6));
}
