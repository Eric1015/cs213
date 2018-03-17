#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "list.h"
#include "string.h"

void convertNumber(element_t* output, element_t input) {
	intptr_t* out = (intptr_t*)output;
	char*     a = input;
	char* ep;
	*out = strtol(a, &ep, 0);
	if (*ep) {
		*out = -1;
	}
}

void isString(element_t* output, element_t input0, element_t input1) {
	intptr_t in0 = (intptr_t)input0;
	char* in1 = (char*)input1;
	char** out = (char**)output;
	if (in0 != -1)
		*out = NULL;
	else
		*out = in1;
}

int isPositive(element_t input) {
	intptr_t in = (intptr_t)input;
	if (in < 0)
	*out = strdup(in2);
	int size = in1;

	if (size < strlen(in2))
		(*out)[size] = 0;
}

void printLine(element_t input) {
	char* output = (char*)input;
	printf("%s\n", output);
}

void printOnSameLine(element_t input) {
	char* output = (char*)input;
	printf("%s ", output);
}

void getMax(element_t* address, element_t output, element_t input) {
	intptr_t* a = (intptr_t*)address;
	intptr_t o = (intptr_t)output;
	intptr_t i = (intptr_t)input;
	if (o < i)
		*a = i;
}

int main(int argc, char** argv) {
	struct list* input = list_create();
	for (unsigned i = 1; i < argc; i++) {
		list_append(input, argv[i]);
	}
	struct list* temporalNumList = list_create();
	list_map1(convertNumber, temporalNumList, input);
	struct list* temporalStringList = list_create();
	list_map2(isString, temporalStringList, temporalNumList, input);

	struct list* numList = list_create();
	list_filter(isPositive, numList, temporalNumList);

	struct list* stringList = list_create();
	list_filter(isNotNull, stringList, temporalStringList);

	struct list* output = list_create();
	list_map2(concatString, output, numList, stringList);
	
	intptr_t mp = 0;
	list_foldl(getMax, (element_t*)&mp, numList);

	list_foreach(printLine, output);
	list_foreach(printOnSameLine, output);
	printf("\n%d\n", mp);

	list_foreach(free, output);
	list_destroy(temporalNumList);
	list_destroy(temporalStringList);
	list_destroy(input);
	list_destroy(output);
	list_destroy(numList);
	list_destroy(stringList);
}