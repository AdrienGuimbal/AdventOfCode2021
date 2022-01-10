extern long long int MONAD(int input[14]) {
	int w=0, x=0, y=0, i=0;
	long long z = 0;
	w = input[i++];
	if (z % 26 + 13 != w) {
		z *= 26;
		z += w + 14;
	}

	printf("z = %lli  ", z);
	w = input[i++];
	if (z % 26 + 12 != w) {
		z *= 26;
		z += w + 8;
	}

	printf("z = %lli  ", z);
	w = input[i++];
	if (z % 26 + 11 != w) {
		z *= 26;
		z += w + 5;
	}

	printf("z = %lli  ", z);
	w = input[i++];
	x = z % 26 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 4;
	}

	printf("z = %lli  \n", z);
	w = input[i++];
	if (z % 26 + 15 != w) {
		z *= 26;
		z += w + 10;
	}

	printf("z = %lli  \n", z);
	w = input[i++];
	x = z % 26 - 13 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 13;
	}

	printf("z = %lli  \n", z);
	w = input[i++];
	if (z % 26 + 10 != w) {
		z *= 26;
		z += w + 16;
	}

	printf("z = %lli  \n", z);
	w = input[i++];
	x = z % 26 - 9 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 5;
	}

	printf("z = %lli  \n", z);
	w = input[i++];
	if (z % 26 + 11 != w) {
		z *= 26;
		z += w + 6;
	}

	printf("z = %lli  \n", z);
	w = input[i++];
	if (z % 26 + 13 != w) {
		z *= 26;
		z += w + 13;
	}

	printf("z = %lli  \n", z);
	w = input[i++];
	x = z % 26 -14 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 6;
	}

	printf("z = %lli  \n", z);
	w = input[i++];
	x = z % 26 - 3 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 7;
	}

	printf("z = %lli  \n", z);
	w = input[i++];
	x = z % 26 - 2 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 13;
	}

	printf("z = %lli  \n", z);
	w = input[i++];
	x = z % 26 - 14 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 3;
	}
	return z;
}