#include "stdio.h"
#include "stdlib.h"
#include "list.h"

int main(int argc, char* argv[]) {
	int length = argc - 1;
	char** str;
	int* num;
	for (unsigned i = 1; i <= length; i++)
		num[i] = strtol(argv[i], str[i], 10);
	printf("The number is %d\n", num);
	printf("The string is %s", str);
}