#include "symbolTable.h"

typedef struct __node_t__ {
	void *key;
	int value;
	struct __node_t__ *left;
	struct __node_t__ *right;
} node_t;

typedef struct __symbol_table_t__ {
	node_t *root;
	compare_fn_t    compare_fn;
	printTree_fn_t  dfsPrintPreOrder;
	printTree_fn_t  dfsPrintInOrder;
	printTree_fn_t  dfsPrintPostOrder;
	getValue_fn_t   getValue;
	addNode_fn_t    addNode;
} symbol_table_t;