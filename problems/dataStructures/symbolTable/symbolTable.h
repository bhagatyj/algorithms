#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (* compare_fn_t) (void *k1, void *k2);

// If node already exists, createNode would change the value.
void * createNode(void *, int);

void * createST(compare_fn_t);

void addNodeToST(void *, void *);

int getValue(void *, void *);

void dfs(void *);
