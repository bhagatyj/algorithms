// Stacks
	// stack * createStringStack(int N)
	// void push (stack *st, char *line)
	// char * pop(stack *st)
	// int isStackEmpty(stack *st)
// UseCase
	// Get strings from STDIN
	// And print them in reverse order.
// 9:25
// 
#include "stack.h"

typedef struct __stackNode__ {
	void * items[BLOCKSIZE];
	struct __stackNode__ *next;
} stackNode;

typedef struct __stack__ {
	stackNode *head;
	int count;
	int allocCount;
} stack;


stack * createStack()
{
	stack *st;

	st = (stack *)malloc(sizeof(stack));
	st->head = NULL;
	st->count = 0;
	st->allocCount = 0;
	return st;
}

void push(stack *st, void *item)
{
	stackNode *node;
	int slot;

	if ((st->count + 1) > st->allocCount) {
		node = (stackNode *)malloc(sizeof(stackNode));
		st->allocCount += BLOCKSIZE;
		node->next = st->head;
		st->head = node;
	} else {
		if ((st->count + BLOCKSIZE) < st->allocCount) {
			node = st->head->next;
		} else {
			node = st->head;
		}
	}

	slot = st->count % BLOCKSIZE;
	node->items[slot] = item;
	st->count++;
}

void * pop(stack *st)
{
	stackNode *node;
	void *item;
	int slot;

	if (st->count == 0) {
		return NULL;
	}

	if (st->count + BLOCKSIZE > st->allocCount) {
		node = st->head;
		slot = (st->count - 1) % BLOCKSIZE;
		item = node->items[slot];
	} else {
		// there is an extra block at the head
		node = st->head->next;
		slot = (st->count - 1) % BLOCKSIZE;
		item = node->items[slot];

		if (slot == 0) {
			free(st->head);
			st->head = node;
			st->allocCount -= BLOCKSIZE;
		}
	}
	st->count--;
	return item;

}

void deleteStack(stack *st)
{
	while (st->head) {
		pop(st);
	}
	free(st);
}


int size(stack *st)
{
	return st->count;
}
