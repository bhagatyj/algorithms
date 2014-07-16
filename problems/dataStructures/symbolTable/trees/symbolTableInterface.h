#ifndef __symbolTableInterface_h__
#define __symbolTableInterface_h__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define TRUE 1
#define FALSE 0

typedef void * (* createNode_fn_t) (void *key, int value);
typedef int    (* compare_fn_t) (void *k1, void *k2);
typedef void   (* addNode_fn_t) (void *stPtr, void *nodePtr);
typedef int    (* onEachNode_fn_t) (void *key, unsigned long value);
typedef int (*walkTree_fn_t) (void *stPtr, onEachNode_fn_t onEachNode_fn);

typedef unsigned long    (* getValue_fn_t) (void *stPtr, void *key);
typedef unsigned long    (* genValue_fn_t) (void *key, int currentValue);

typedef void   (* printTree_fn_t) (void *stPtr);


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
	walkTree_fn_t   walkTreeFn;
} symbol_table_t;


void * createST(compare_fn_t, genValue_fn_t);

#endif
