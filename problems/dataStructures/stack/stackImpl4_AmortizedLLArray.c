
/*

Stack using Linked Lists:


  --------
 |  headB|-----> NULL
  --------


 
  -------- 
 |  headB|-----.
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
 |  headB|-----.
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
	int numSlots;
} stack;

void * createStack()
{
	stack *st;

	st = (stack *)malloc(sizeof(stack));
	st->headBlock = NULL;
	st->headIdx = 0;
	st->numSlots = 0;
	return (void *)st;
}

void push(void *s, void *item)
{
	block_t *node;
	int slot;
	stack *st = (stack *)s;

	if ((st->headIdx + 1) > st->numSlots) {
		node = (block_t *)malloc(sizeof(block_t));
		st->numSlots += BLOCKSIZE;
		node->next = st->headBlock;
		st->headBlock = node;
	} else {
		if ((st->headIdx + BLOCKSIZE) < st->numSlots) {
			node = st->headBlock->next;
		} else {
			node = st->headBlock;
		}
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

	if (st->headIdx + BLOCKSIZE > st->numSlots) {
		node = st->headBlock;
		slot = (st->headIdx - 1) % BLOCKSIZE;
		item = node->items[slot];
	} else {
		// there is an extra block at the headBlock
		node = st->headBlock->next;
		slot = (st->headIdx - 1) % BLOCKSIZE;
		item = node->items[slot];

		if (slot == 0) {
			free(st->headBlock);
			st->headBlock = node;
			st->numSlots -= BLOCKSIZE;
		}
	}
	st->headIdx--;
	return item;

}


void deleteStack(void *s)
{
	stack *st = (stack *)s;
	while (st->headIdx) {
		pop(st);
	}
	if (st->headBlock) {
		free(st->headBlock);
	}
	free(st);
}


int size(void *st)
{
	return ((stack *)st)->headIdx;
}

