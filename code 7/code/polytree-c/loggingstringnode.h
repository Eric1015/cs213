#ifndef __LOGGINGSTRINGNODE_H__
#define __LOGGINGSTRINGNODE_H__

struct LoggingStringNode_class {
	struct StringNode_class* super;
	int(*compareTo) (void*, void*);
	void(*printNode) (void*);
	void(*insert)    (void*, void*);
	void(*print)     (void*);
	void(*delete)	(void*);
};
extern struct LoggingStringNode_class LoggingStringNode_class_table;

/**
* struct definition of object
*/
struct LoggingStringNode;
struct LoggingStringNode {
	struct LoggingStringNode_class* class;

	// instance variables defined in super class(es)
	struct LoggingStringNode* left;
	struct LoggingStringNode* right;

	// instance variables defined in this class
	char* s;
};

void LoggingStringNode_insert(void* thisv, void* nodev);

/**
* definition of new for class
*/
void* new_LoggingStringNode(char*);

#endif /*__LOGGINGSTRINGNODE_H__*/
