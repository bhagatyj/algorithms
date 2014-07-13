
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

	symbol_table_t *st = (symbol_table_t *)stPtr;
	node_t * newNode = (node_t *)nodePtr;
	node_t *node;
	int ret;

	node = st->root;
	st->root = addNode(node, newNode, st->compare_fn);
}

void addNode(node *main, node *newNode, compare_fn_t compare_fn_t)
{

	if (!main) {
		return newNode;
	}

	ret = st->compare_fn(newNode, node);
	if (ret == 0) {
		// repeated node
		node->value = newNode->value;
		free(newNode);
	}
	if (ret < 0) {
		main->left = addNode(main->left, newNode, compare_fn);
	} else {
		main->right = addNode(main->right, newNode, compare_fn);
	}
	return main;
}

int getValue(void *st, void *key);
{

}

void printPreorder(node_t *node)
{
	if (node == NULL) {
		return;
	}
	printf("%s\n"node->key);
	
}
void dfs(void *stPtr)
{
	symbol_table_t *st = (symbol_table_t *)stPtr;

	printPreorder(st->node);
}