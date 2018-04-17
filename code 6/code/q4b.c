#include "stdio.h" 

int countNumOfOne(int num) {
	int numOfOne = 0;
	signed int copy = num;
	do {
		signed int currentCopy = copy;
		currentCopy = currentCopy & 0x80000000;
		if (currentCopy < 0) {
			numOfOne++;
		}
		copy = copy << 1;
	} while (copy != 0);

	return numOfOne;
}

int main(void) {
	int x[8];
	x[0] = 1;
	x[1] = 2;
	x[2] = 3;
	x[3] = 0xffffffff;
	x[4] = 0xfffffffe;
	x[5] = 0;
	x[6] = 184;
	x[7] = 340057058;
	int y[8];

	int i = 8;
	while (i > 0) {
		y[i - 1] = countNumOfOne(x[i - 1]);
		i--;
	}
	for (int i = 0; i < sizeof(x) / sizeof(int); i++) {
		printf("%d\n", x[i]);
	}
	for (int i = 0; i < sizeof(y) / sizeof(int); i++) {
		printf("%d\n", y[i]);
	}
}