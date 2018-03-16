#include "stdio.h"
#include "stdlib.h"
#include "list.h"
#include "list.c"
#include "string.h"

int isNumber(element_t* input) {
	// check whether this 0 compare is correct or not
	char* str = (char*)input;
	if (strcmp(str, "0") == 0) {
		printf("%s to %d\n", str, atoi(str));
		return 1;
	}
	if (atoi(str) == 0) {
		return 0;
	}
	else {
		printf("%s to %d\n", str, atoi(str));
		return 1;
	}
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
	printf("%s\n", in2);
	printf("%d\n", strlen(in2));
	if (*out == NULL)
		*out = malloc(sizeof(char) * (int)strlen(in2));
	int size = atoi(in1);
	strcpy(*out, in2);
	printf("%c\n", (*(*out + 1)));
	printf("%d\n", size);
	printf("%s\n", *out);

	*(*out + size) = 0;
	printf("%s\n", *out);
}

void print(element_t input) {
	char* output = (char*)input;
	printf("%s\n", output);
}

void printOnSameLine(element_t input) {
	char* output = (char*)input;
	printf("%s ", output);
}

int main(int argc, char** argv) {
	struct list* input = list_create();
	//for (unsigned i = 1; i < argc; i++) {
		//list_append(input, argv[i]);
	//}
	
	list_append(input, "4");
	list_append(input, "apple");
	list_append(input, "3");
	list_append(input, "peach");
	list_append(input, "2");
	list_append(input, "3");
	list_append(input, "grape");
	list_append(input, "plum");

	struct list* numList = list_create();
	list_filter(isNumber, numList, input);
	struct list* stringList = list_create();
	list_filter(isString, stringList, input);

	struct list* output = list_create();
	list_map2(concatString, output, numList, stringList);

	list_foreach(print, output);
	list_foreach(printOnSameLine, output);
	printf("\n%d\n", list_len(output));
}