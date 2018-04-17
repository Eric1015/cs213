#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "integernode.h"

/**
* declaration and initialzation of class table
*/
struct IntegerNode_class IntegerNode_class_table = {
	&Node_class_table,  /* super */
	IntegerNode_compareTo,  
	IntegerNode_print,  
	Node_insert,
	Node_print,
	Node_delete,
	IntegerNode_sum,
};

/**
* constructor
*/
void IntegerNode_ctor(void* thisv, int  i) {
	struct IntegerNode* this = thisv;
	Node_ctor(thisv);
	this->i = i;
}

int IntegerNode_compareTo(void* thisv, void* node) {
	struct IntegerNode* a = thisv;
	struct IntegerNode* b = node;
	return a->i == b->i ? 0 : a->i > b->i ? 1 : -1;
}

/**
* print
*/
void IntegerNode_print(void* thisv) {
	struct IntegerNode* a = thisv;
	printf("%d\n", a->i);
}

void* new_IntegerNode(int i) {
	struct IntegerNode* obj = malloc(sizeof(struct IntegerNode));
	obj->class = &IntegerNode_class_table;
	IntegerNode_ctor(obj, i);
	return obj;
}

int IntegerNode_sum(void* thisv) {
	struct IntegerNode* a = thisv;
	int s = a->i;
	if (a->left != NULL)
		s += IntegerNode_sum(a->left);
	if (a->right != NULL)
		s += IntegerNode_sum(a->right);
	return s;
}

