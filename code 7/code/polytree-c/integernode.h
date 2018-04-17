#ifndef __INTEGERNODE_H__
#define __INTEGERNODE_H__

/**
* struct definition of class and external definition of class table
*/
struct IntegerNode_class {
	struct Node_class* super;
	int(*compareTo) (void*, void*);
	void(*printNode) (void*);
	void(*insert)    (void*, void*);
	void(*print)     (void*);
	void(*delete)	(void*);
	int(*sum)		(void*);
};
extern struct IntegerNode_class IntegerNode_class_table;


/**
* struct definition of object
*/
struct IntegerNode;
struct IntegerNode {
	struct IntegerNode_class* class;

	// instance variables defined in this class
	struct IntegerNode* left;
	struct IntegerNode* right;

	int i;
};

/**
* constructor
*/
void IntegerNode_ctor(void* thisv, int  i);

/**
* definition of methods implemented by class
*/
int IntegerNode_compareTo(void* thisv, void* node);
void IntegerNode_print(void* thisv);

/**
* definition of new for class
*/
void* new_IntegerNode(int i);

int IntegerNode_sum(void* thisv);

#endif /*__INTEGERNODE_H__*/
