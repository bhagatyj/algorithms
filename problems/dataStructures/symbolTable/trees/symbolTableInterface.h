#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef int (* compare_fn_t) (void *k1, void *k2);
typedef void (* printTree_fn_t) (void *stPtr);
typedef int (* getValue_fn_t) (void *stPtr, void *key);
typedef void (* addNode_fn_t) (void *stPtr, void *nodePtr);
typedef int (* genValue_fn_t) (void *key, int currentValue);
typedef void * (*createNode_fn_t) (void *key, int value);


// If node already exists, createNode would change the value.
void * createNode(void *, int);

void * createST(compare_fn_t, genValue_fn_t);


int getValue(void *, void *);

void dfs(void *);

typedef struct __symbol_table_t__ {
	void           *root;
	createNode_fn_t fnCreateNode;
	compare_fn_t    compare_fn;
	printTree_fn_t  dfsPrintPreOrder;
	printTree_fn_t  dfsPrintInOrder;
	printTree_fn_t  dfsPrintPostOrder;
	getValue_fn_t   getValue;
	genValue_fn_t   genValue;
	addNode_fn_t    addNode;
} symbol_table_t;