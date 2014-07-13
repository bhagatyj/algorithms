#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (* compare_fn_t) (void *k1, void *k2);

// If node already exists, createNode would change the value.
void * createNode(void *key, int value);

void * createST(compare_fn_t compare_fn);

void addNodeToST(void *st, void *node);

int getValue(void *st, void *key);
