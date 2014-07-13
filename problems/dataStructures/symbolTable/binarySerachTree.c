
#include "symbolTable.h"

typedef struct __node_t__ {
	void *key;
	int value;
	struct __node_t__ *left;
	struct __node_t__ *right;
} node_t;

typedef struct __symbol_table_t__ {
	compare_fn_t compare_fn;
	node_t *root;

} symbol_table_t;

void createNode(void *key, int value)
{
	node_t *node = (node *t)malloc(sizeof(node_t));

	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->value = value;
}

void * createST(compare_fn_t compare_fn)
{
	symbol_table_t *st;

	st = (symbol_table_t *)malloc(sizeof(symbol_table_t));
	st->root = NULL;
	st->compare_fn = compare_fn;
}

void addNodeToST(void *stPtr, void *nodePtr) {

}

int getValue(void *st, void *key);
