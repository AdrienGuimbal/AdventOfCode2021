#include <stdio.h>
#include <assert.h>

#define DEBUG 0

void printbin (int x) { // Print a number in 12bit-binary (MSF first)
	for (int i = 12 ; i > 0 ; i--) {
		putchar('0' + ((x >> i) & 1));
	}
	putchar('\n');
}

void pb1 () {
	FILE* file = fopen("input.txt", "r");

	char line[13];     // current line
	int res[12] = {0}; // result
	int len=0;         // len of dataset
	while (fscanf(file, "%s", line) != EOF) {
		for (int i=0; i<12; i++){
			res[i] += line[i]-'0';
		}
		len++;
	}
	fclose(file);

	if (DEBUG) printf("Dataset len : %i\n", len);

	int gamma=0, lambda=0;
	for (int j = 0 ; j < 12 ; j++){
		if (DEBUG) printf("%i", res[j]>len/2);
		gamma += (res[j]>len/2) << (11-j);
	}
	if (DEBUG) putchar('\n');
	
	for (int j = 0 ; j < 12 ; j++){
		if (DEBUG) printf("%i", res[j]<=len/2);
		lambda += (res[j]<=len/2) << (11-j);
	}
	if (DEBUG) {
		putchar('\n');
		printbin(gamma);
		printbin(lambda);
	}
	printf("Résultat pb1 : %i * %i = %i\n", gamma, lambda, gamma*lambda); //4006064
}

int get_most_frequant (char content[12][1000], int col, int len) {
	int buff = 0;
	for (int i = 0 ; i < len ; i++) {
		buff += (content[col][i] == 1) ? 1 : -1;
	}
	return buff >= 0;
}

int get_least_frequant (char content[12][1000], int col, int len) {
	int buff = 0;
	for (int i = 0 ; i < len ; i++) {
		buff += (content[col][i] == 1) ? 1 : -1;
	}
	return buff < 0;
}

int keep_matching (char content[12][1000], int col, int len, int val) {
	int index = 0;
	for (int i = 0 ; i < len ; i++) {
		if (content[col][i] == val) {
			for (int j = 0 ; j < 12 ; j++) {
				content[j][index] = content[j][i];
			}
			index++;
		}
	}
	return index;
}

void pb2 () {
	FILE* file = fopen("input.txt", "r");

	int len = 1000;
	char diag[12][1000];
	char line[12];
	
	int ln = 0;
	while (fscanf(file, "%s", line) != EOF) {
		for (int i=0; i<12; i++){
			diag[i][ln] = line[i] - '0';
		}
		ln++;
	}
	fclose(file);
	assert(len==ln);
	
	if (DEBUG) printf("File parsed\n");

	char oxy[12][1000];
	for (int i = 0 ; i < 1000 ; i++) {
		for (int j = 0 ; j < 12 ; j++) {
			oxy[j][i] = diag[j][i];
		}
	}
	int oxylen = len;
	int oxyrate = 0;
	for (int i = 0 ; i < 12 ; i++) {
		oxylen = keep_matching(oxy, i, oxylen, get_most_frequant(oxy, i, oxylen));
	}
	for (int i = 0 ; i < 12 ; i++) {
		if (DEBUG) printf("%i", oxy[i][0]);
		oxyrate += oxy[i][0] << (11-i);
	}
	if (DEBUG) putchar('\n');
	if (DEBUG) printf("oxylen : %i\nOxyVal : %i\n", oxylen, oxyrate);

	
	char co2[12][1000];
	for (int i = 0 ; i < 1000 ; i++) {
		for (int j = 0 ; j < 12 ; j++) {
			co2[j][i] = diag[j][i];
		}
	}
	int co2len = len;
	int co2rate = 0;
	for (int i = 0 ; i < 12 ; i++) {
		co2len = keep_matching(co2, i, co2len, get_least_frequant(co2, i, co2len));
	}
	for (int i = 0 ; i < 12 ; i++) {
		if (DEBUG) printf("%i", co2[i][0]);
		co2rate += co2[i][0] << (11-i);
	}
	if (DEBUG) putchar('\n');
	if (DEBUG) printf("co2len : %i\nCo2Val : %i\n", co2len, co2rate);

	printf("Résultat pb2 : %i * %i = %i\n", oxyrate, co2rate, oxyrate*co2rate);
}

int main () {
	pb1();
	pb2();
	return 0;
}