#include "stdlib.h"
#include "stdio.h"

int q2(int a1, int a2, int a3) {
	int i = 0;
	switch (a1) {
	case 10: 
		i = a2 + a3;
		break;
	case 12:
		i = a2 - a3;
		break;
	case 14:
		if (a2 > a3)
			i = 1;
		else
			i = 0;
		break;
	case 16:
		if (a3 > a2)
			i = 1;
		else
			i = 0;
		break;
	case 18:
		if (a2 == a3)
			i = 1;
		else
			i = 0;
		break;
	default:
		i = 0;
	}

	return i;
}

int main(int argc, char** argv) {
	int num[3];
	for (unsigned i = 0; i < sizeof(num) / sizeof(int); i++)
		num[i] = atoi(argv[i + 1]);
	int result = q2(num[0], num[1], num[2]);
	printf("%d\n", result);
}