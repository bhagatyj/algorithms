#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (* compare_fn_t) (void *k1, void *k2);

typedef struct __node_t__ {
	void *key;
	compare_fn_t compare_fn;
	void *value;
} node_t;