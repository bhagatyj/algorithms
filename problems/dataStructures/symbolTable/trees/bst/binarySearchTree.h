#include "symbolTableInterface.h"

typedef struct __node_t__ {
	void *key;
	unsigned long value;
	struct __node_t__ *left;
	struct __node_t__ *right;
} node_t;

typedef int    (* walk_fn_t) (node_t *, onEachNode_fn_t);
