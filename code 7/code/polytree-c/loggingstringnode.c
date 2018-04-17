#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "stringnode.h"
#include "loggingstringnode.h"

struct LoggingStringNode_class LoggingStringNode_class_table = {
	&StringNode_class_table,  /* super */
	StringNode_compareTo,
	StringNode_printNode,
	LoggingStringNode_insert,
	Node_print,
	Node_delete,
};

void LoggingStringNode_insert(void* thisv, void* nodev) {
	struct LoggingStringNode* a = thisv;
	struct LoggingStringNode* b = nodev;
	printf("insert %s\n", b->s);
	a->class->super->insert(thisv, nodev);
}

void* new_LoggingStringNode(char* s) {
	struct LoggingStringNode* obj = malloc(sizeof(struct LoggingStringNode));
	obj->class = &LoggingStringNode_class_table;
	StringNode_ctor(obj, s);
	return obj;
}
