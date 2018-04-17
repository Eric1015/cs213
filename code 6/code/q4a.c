#include "stdio.h"

int c[10];
int* p = c;

void add(int num, int index) {
	p[index] += num;
}

void foo() {
	add(3, 4);
	add(1, 2);
}

int main(void) {
	foo();
	for (int i = 0; i < sizeof(c) / sizeof(int); i++) {
		printf("%d\n", c[i]);
	}
}
