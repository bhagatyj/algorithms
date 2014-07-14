#include "symbolTableInterface.h"

typedef struct __node_t__ {
	void *key;
	int value;
	struct __node_t__ *left;
	struct __node_t__ *right;
} node_t;

