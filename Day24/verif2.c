extern long long int MONAD_OPTI(int input[14]) {
	long long int w=0, x=0, y=0, i=0;
	long long int z = 0;
	
	long long int n0 = input[0];
	long long int n1 = input[1];
	long long int n2 = input[2];
	long long int n3 = input[3];
	long long int n4 = input[4];

	w = input[i++]; //n0
	y = w + 14;
	z = y;

	// z = n0 + 14 
	printf("z = %lli = %lli  ", z, n0 + 14);

	w = input[i++]; //n1
	z *= 26;
	z += w + 8;
	
	// z = n0*26 + n1 + 14*26 + 8
	printf("z = %lli = %lli  ", z, 26*(n0 +14) + n1 + 8);

	w = input[i++]; //n2
	z *= 26;
	z += w + 5;

	// z = (n0 + 14)*26² + (n1 + 8)*26 + n2 + 5
	printf("z = %lli = %lli  ", z, 676*(n0 +14) + 26*(n1+8) + n2 + 5);

	w = input[i++]; //n3	
	z /= 26; // z = n0*26 + n1 + 15*26 + 8

	if (n2+5 != n3) {
		z *= 26; 
		z += n3 + 4;
	}

	// z if   = (n0 + 14)*26² + (n1 + 8)*26 + n3 + 4
	// z else = z = (n0 + 14)*26 + n1 + 8

	printf("z = %lli  \n", z);
	w = input[i++]; // n4
	x = (z%26 + 15) != w;
	if (x) {
		z *= 26;
		z = w + 10;
	}

	w = input[i++]; // n5
	x = z % 26 - 13;
	z /= 26;
	x = x != w;
	y = 25;
	y *= x;
	y += 1;
	z *= y;
	y = w;
	y += 13;
	y *= x;
	z += y;
	w = input[i++];
	x = z % 26;
	x += 10;
	x = x != w;
	y = 25;
	y *= x;
	y += 1;
	z *= y;
	y = w;
	y += 16;
	y *= x;
	z += y;
	w = input[i++];
	x = z % 26;
	z /= 26;
	x += -9;
	x = x != w;
	y = 25;
	y *= x;
	y += 1;
	z *= y;
	y = w;
	y += 5;
	y *= x;
	z += y;
	w = input[i++];
	x = z % 26;
	x += 11;
	x = x != w;
	y = 25;
	y *= x;
	y += 1;
	z *= y;
	y = w;
	y += 6;
	y *= x;
	z += y;
	w = input[i++];
	x = z % 26;
	x += 13;
	x = x != w;
	y = 25;
	y *= x;
	y += 1;
	z *= y;
	y = w;
	y += 13;
	y *= x;
	z += y;
	w = input[i++];
	x = z % 26;
	z /= 26;
	x += -14;
	x = x != w;
	y = 25;
	y *= x;
	y += 1;
	z *= y;
	y = w;
	y += 6;
	y *= x;
	z += y;
	w = input[i++];
	x = z % 26;
	z /= 26;
	x += -3;
	x = x != w;
	y = 25;
	y *= x;
	y += 1;
	z *= y;
	y = w;
	y += 7;
	y *= x;
	z += y;
	w = input[i++];
	x = z % 26;
	z /= 26;
	x += -2;
	x = x != w;
	y = 25;
	y *= x;
	y += 1;
	z *= y;
	y = w;
	y += 13;
	y *= x;
	z += y;
	w = input[i++];
	x = z % 26;
	z /= 26;
	x += -14;
	x = x != w;
	y = 25;
	y *= x;
	y += 1;
	z *= y;
	y = w;
	y += 3;
	y *= x;
	z += y;
	return z;
}