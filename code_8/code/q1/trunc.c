#include "stdio.h"
#include "stdlib.h"
#include "list.h"
#include "string.h"

int isNumber(element_t* input) {
	char* str = (char*)input;
	if (strcmp(str, "0") == 0)
		return 1;
	if (atoi(str) == 0)
		return 0;
	else
		return 1;
}

int isString(element_t* input) {
	if (isNumber(input) == 0)
		return 1;
	else
		return 0;
}

void concatString(element_t* out_data, element_t in_data1, element_t in_data2) {
	char** out = (char**)out_data;
	char* in1 = (char*)in_data1;
	char* in2 = (char*)in_data2;
	if (*out == NULL)
		*out = malloc(sizeof(in2));
	int size = atoi(in1);
	strcpy(*out, in2);

	if (size < strlen(in2))
	*(*out + size) = 0;
}

void printLine(element_t input) {
	char* output = (char*)input;
	printf("%s\n", output);
}

void printOnSameLine(element_t input) {
	char* output = (char*)input;
	printf("%s ", output);
}

void pointNull(element_t input) {
	element_t* data = input;;
	data = NULL;
}

void stringLength(element_t* result, element_t input) {
	int** r = (int**)result;
	char* str = (char*)input;
	if (*r == NULL)
		*r = malloc(sizeof(int));
	**r = strlen(str);
}

void getMax(element_t* address, element_t output, element_t input) {
	int** a = (int**)address;
	int* o = (int*)output;
	char* i = (char*)input;
	int target = strlen(i);
	if (*a == NULL)
		*a = malloc(sizeof(int));
	if (*o < target)
		**a = target;
}

int main(int argc, char** argv) {
	struct list* input = list_create();
	for (unsigned i = 1; i < argc; i++) {
		list_append(input, argv[i]);
	}
	struct list* numList = list_create();
	list_filter(isNumber, numList, input);
	struct list* stringList = list_create();
	list_filter(isString, stringList, input);

	struct list* output = list_create();
	list_map2(concatString, output, numList, stringList);
	
	int max = 0;
	int* mp = &max;
	list_foldl(getMax, (element_t*)&mp, output);

	list_foreach(printLine, output);
	list_foreach(printOnSameLine, output);
	printf("\n%d\n", max);

	list_foreach(free, output);
	list_destroy(input);
	list_destroy(output);
	list_destroy(numList);
	list_destroy(stringList);
}