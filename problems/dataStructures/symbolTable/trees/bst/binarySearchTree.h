#include "symbolTableInterface.h"

typedef struct __node_t__ {
	void *key;
	unsigned long value;
	struct __node_t__ *left;
	struct __node_t__ *right;
} node_t;

