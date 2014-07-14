
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

void * createNode(void *key, int value)
{
	node_t *node = (node_t *)malloc(sizeof(node_t));

	//printf("Create node for %s\n", key);
	node->key = strdup(key);
	node->left = NULL;
	node->right = NULL;
	node->value = value;

	return (void *)node;
}

void * createST(compare_fn_t compare_fn)
{
	symbol_table_t *st;

	st = (symbol_table_t *)malloc(sizeof(symbol_table_t));
	st->root = NULL;
	st->compare_fn = compare_fn;

	return (void *)st;
}


node_t * addNode(node_t *main, node_t *newNode, compare_fn_t compare_fn)
{
	int ret;

	if (!main) {
		return newNode;
	}

	ret = compare_fn(main->key, newNode->key);
	if (ret == 0) {
		// repeated node
		main->value += newNode->value;
		free(newNode);
		return main;
	}
	if (ret > 0) {
		if (!main->left) {
			//printf("Adding %s to left of %s\n", newNode->key, main->key);
		}
		main->left = addNode(main->left, newNode, compare_fn);
	} else {
		if (!main->right) {
			//printf("Adding %s to right of %s\n", newNode->key, main->key);
		}
		main->right = addNode(main->right, newNode, compare_fn);
	}
	return main;
}

void addNodeToST(void *stPtr, void *nodePtr) {

	symbol_table_t *st = (symbol_table_t *)stPtr;
	node_t * newNode = (node_t *)nodePtr;
	node_t *node;

	node = st->root;
	st->root = addNode(node, newNode, st->compare_fn);
}

int getValue(void *stPtr, void *key)
{

	symbol_table_t *st = (symbol_table_t *)stPtr;
	int ret;
	node_t *node;

	node = st->root;
	while (node) {
		ret = st->compare_fn(node->key, key);
		if (ret == 0) {
			break;
		}
		if (ret > 0) {
			node = node->left;
		} else {
			node = node->right;
		}
	}

	return (ret ? 0 : node->value);

}

void printPreorder(node_t *node)
{
	if (node == NULL) {
		return;
	}
	printf("%d:%s\n", node->value, (char *) node->key);
	printPreorder(node->left);
	printPreorder(node->right);
}

void printInorder(node_t *node)
{
	if (node == NULL) {
		return;
	}
	printInorder(node->left);
	printf("%d:%s\n", node->value, (char *) node->key);
	printInorder(node->right);
}

void printPostorder(node_t *node)
{
	if (node == NULL) {
		return;
	}
	printInorder(node->left);
	printInorder(node->right);
	printf("%d:%s\n", node->value, (char *) node->key);
}

void dfs(void *stPtr)
{
	symbol_table_t *st = (symbol_table_t *)stPtr;

	printf("Nodes in pre-order...\n");
	printPreorder(st->root);
	printf("Nodes in in-order...\n");
	printInorder(st->root);
	printf("Nodes in post-order...\n");
	printPostorder(st->root);
}