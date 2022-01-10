extern long long int MONAD(int input[14]) {
	long long int w=0, x=0, y=0, z=0, i=0;

	z = input[i++] + 14;

	z *= 26;
	z += input[i++] + 8;

	z *= 26;
	z += input[i++] + 5;

	w = input[i++];
	x = z % 26 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 4;
	}

	z *= 26;
	z += input[i++] + 10;

	w = input[i++];
	x = z % 26 - 13 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 13;
	}

	z *= 26;
	z += input[i++] + 16;

	w = input[i++];
	x = z % 26 - 9 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 5;
	}

	z *= 26;
	z += input[i++] + 6;

	z *= 26;
	z += input[i++] + 13;

	w = input[i++];
	x = z % 26 - 14 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 6;
	}

	w = input[i++];
	x = z % 26 - 3 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 7;
	}

	w = input[i++];
	x = z % 26 - 2 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 13;
	}

	w = input[i++];
	x = z % 26 - 14 != w;
	z /= 26;
	if (x) {
		z *= 26;
		z += w + 3;
	}
	return z;
}