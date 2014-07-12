
/*

Stack using Linked Lists:


  --------
 |  headBlock  |-----> NULL
  --------


 
  -------- 
 |  headBlock  |-----.
  --------      |
                v
              --------
             |  next  | ---> NULL
             |--------|
             |  it 1  |
              --------
             |  it 2  |
              --------
             |  ....  |
              --------
             |  ....  |
              --------
             |  it N  |
              --------


  -------- 
 |  headBlock  |-----.
  --------      |
                v 
              --------       --------
             |  next  |---->|  next  | ---> NULL
             |--------|     |--------|
             |  it 1  |     | it N+1 |
              --------       --------
             |  it 2  |     | it N+2 |
              --------       --------
             |  ....  |     |  ....  |
              --------       --------
             |  ....  |     |  ....  |
              --------       --------
             |  it N  |     |  it 2N |
              --------       --------


The "headBlock" field keeps track of the "headNode" or the headBlock-Allocation-unit.
It doesn't really keeptrack of the headBlock item. In this implementation, the
headIdx value is used as the headBlock.

That is not a good idea in terms of debugging.
I should revise and re-implement this using different field names.

Use "headBlock" to denote the headBlock-item
Use headBlock to denote the headBlock-Block of items.

*/
#include "stack.h"

#define BLOCKSIZE 16

typedef struct __block_t__ {
	void * items[BLOCKSIZE];
	struct __block_t__ *next;
} block_t;

typedef struct __stack__ {
	block_t *headBlock;
	int headIdx;
	int numBlocks;
} stack;


void * createStack()
{
	stack *st;

	st = (stack *)malloc(sizeof(stack));
	st->headBlock = NULL;
	st->headIdx = 0;
	st->numBlocks = 0;
	return (void *)st;
}

void push(void *s, void *item)
{
	block_t *node;
	int slot;
	stack *st = (stack *)s;

	if ((st->headIdx + 1) > (st->numBlocks * BLOCKSIZE)) {
		node = (block_t *)malloc(sizeof(block_t));
		st->numBlocks += 1;
		node->next = st->headBlock;
		st->headBlock = node;
	} else {
		node = st->headBlock;
	}
	slot = st->headIdx % BLOCKSIZE;
	node->items[slot] = item;
	st->headIdx++;
}

void * pop(void *s)
{
	block_t *node;
	void *item;
	int slot;
	stack *st = (stack *)s;

	if (st->headIdx == 0) {
		return NULL;
	}

	node = st->headBlock;
	slot = (st->headIdx - 1) % BLOCKSIZE;
	item = node->items[slot];
	node->items[slot] = NULL;

	if (slot == 0) {
		st->headBlock = node->next;
		free(node);
		st->numBlocks -= 1;
	}
	st->headIdx--;
	return item;

}

void deleteStack(void *s)
{
	stack *st = (stack *)s;
	while (st->headBlock) {
		pop(st);
	}
	free(st);
}


int size(void *st)
{
	return ((stack *)st)->headIdx;
}
