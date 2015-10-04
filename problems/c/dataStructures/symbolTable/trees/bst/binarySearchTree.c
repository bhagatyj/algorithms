#include "binarySearchTree.h"


void addNodeToST(void *, void *);

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

void printPreorder(node_t *node)
{
	if (node == NULL) {
		return;
	}
	printf("%-24s:%lu\n", (char *) node->key, node->value);
	printPreorder(node->left);
	printPreorder(node->right);
}

void printInorder(node_t *node)
{
	if (node == NULL) {
		return;
	}
	printInorder(node->left);
	printf("%-24s:%lu\n", (char *) node->key, node->value);
	printInorder(node->right);
}

void printPostorder(node_t *node)
{
	if (node == NULL) {
		return;
	}
	printPostorder(node->left);
	printPostorder(node->right);
	printf("%-24s:%lu\n", (char *) node->key, node->value);
}

// void dfsPrintPreOrder(void *stPtr)
// {
// 	symbol_table_t *st = (symbol_table_t *)stPtr;

// 	printf("Nodes in pre-order...\n");
// 	printPreorder(st->root);
// }

// // void dfsPrintInOrder(void *stPtr)
// // {
// // 	symbol_table_t *st = (symbol_table_t *)stPtr;

// // 	printInorder(st->root);
// // }

// void dfsPrintPostOrder(void *stPtr)
// {
// 	symbol_table_t *st = (symbol_table_t *)stPtr;

// 	printf("Nodes in post-order...\n");
// 	printPostorder(st->root);
// }


node_t * addNode(node_t *main, node_t *newNode, symbol_table_t *st)
{
	int ret;

	if (!main) {
		return newNode;
	}

	ret = st->compare_fn(main->key, newNode->key);
	if (ret == 0) {
		// repeated node
		main->value = st->genValue(main->key, main->value);
		free(newNode);
		return main;
	}
	if (ret > 0) {
		main->left = addNode(main->left, newNode, st);
	} else {
		main->right = addNode(main->right, newNode, st);
	}
	return main;
}

void addNodeToST(void *stPtr, void *nodePtr) {

	symbol_table_t *st = (symbol_table_t *)stPtr;
	node_t * newNode = (node_t *)nodePtr;
	node_t *node;

	node = st->root;
	st->root = addNode(node, newNode, st);
}


unsigned long getValue(void *stPtr, void *key)
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


int walkNodeInorder(node_t *node, onEachNode_fn_t onEachNode_fn)
{
	int ret;

	if (node == NULL) {
		return FALSE;
	}
	ret += walkNodeInorder(node->left, onEachNode_fn);
	ret += onEachNode_fn(node->key, node->value);
	ret += walkNodeInorder(node->right, onEachNode_fn);

	return ret;
}

int walkNodePreorder(node_t *node, onEachNode_fn_t onEachNode_fn)
{
	int ret;

	if (node == NULL) {
		return FALSE;
	}
	ret += onEachNode_fn(node->key, node->value);
	ret += walkNodePreorder(node->left, onEachNode_fn);
	ret += walkNodePreorder(node->right, onEachNode_fn);

	return ret;
}

int walkNodePostorder(node_t *node, onEachNode_fn_t onEachNode_fn)
{
	int ret;

	if (node == NULL) {
		return FALSE;
	}
	ret += walkNodePostorder(node->left, onEachNode_fn);
	ret += walkNodePostorder(node->right, onEachNode_fn);
	ret += onEachNode_fn(node->key, node->value);

	return ret;
}

int walkTreeOrder(void *stPtr, walk_fn_t walk_fn, onEachNode_fn_t onEachNode_fn)
{

	symbol_table_t *st = (symbol_table_t *)stPtr;
	int ret;
	node_t *node;

	node = st->root;
	return (walk_fn(node, onEachNode_fn));
}

/*
	This function is meant for generic users who do not 
	differentiate between Pre/In/Post order methods of 
	printing the nodes.

	Can be used by a genric Application that needs to run
	a function through all the nodes of a SymbolTable.

	It uses the In-order routine.
*/
int walkTreeFn(void *stPtr, onEachNode_fn_t onEachNode_fn)
{

	symbol_table_t *st = (symbol_table_t *)stPtr;
	int ret;
	node_t *node;

	node = st->root;
	return (walkNodeInorder(node, onEachNode_fn));
}

int printNode (void *key, unsigned long value)
{
	printf("%-24s:%lu\n", (char *)key, value);
	return FALSE;
}

void dfsPrintPreOrder(void *stPtr)
{
	printf("Nodes in pre-order...\n");
	walkTreeOrder(stPtr, walkNodePreorder, printNode);
}

void dfsPrintInOrder(void *stPtr)
{
	printf("Nodes in in-order...\n");
	walkTreeOrder(stPtr, walkNodeInorder, printNode);
}

void dfsPrintPostOrder(void *stPtr)
{
	printf("Nodes in post-order...\n");
	walkTreeOrder(stPtr, walkNodePostorder, printNode);
}

void * createST(compare_fn_t compare_fn, genValue_fn_t gen_fn)
{
	symbol_table_t *st;

	st = (symbol_table_t *)malloc(sizeof(symbol_table_t));
	st->root = NULL;
	st->compare_fn = compare_fn;
	st->genValue = gen_fn;
	st->dfsPrintPreOrder = dfsPrintPreOrder;
	st->dfsPrintInOrder = dfsPrintInOrder;
	st->dfsPrintPostOrder = dfsPrintPostOrder;
	st->addNode = addNodeToST;
	st->getValue = getValue;
	st->fnCreateNode = createNode;
	st->walkTreeFn = walkTreeFn;
	return (void *)st;
}


