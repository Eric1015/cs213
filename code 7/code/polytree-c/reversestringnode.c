#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "stringnode.h"
#include "reversestringnode.h"

struct ReverseStringNode_class ReverseStringNode_class_table = {
	&StringNode_class_table,  /* super */
	ReverseStringNode_compareTo,
	StringNode_printNode,
	Node_insert,
	Node_print,
	Node_delete,
};

int ReverseStringNode_compareTo(void* thisv, void* nodev) {
	struct ReverseStringNode* this = thisv;
	struct ReverseStringNode* node = nodev;
	return -1 * strcmp(this->s, node->s);
}

void* new_ReverseStringNode(char* s) {
	struct ReverseStringNode* obj = malloc(sizeof(struct ReverseStringNode));
	obj->class = &ReverseStringNode_class_table;
	StringNode_ctor(obj, s);
	return obj;
}
