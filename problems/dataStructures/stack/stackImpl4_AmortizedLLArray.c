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

#define BLOCKSIZE 16


typedef struct __stackNode__ {
	void * items[BLOCKSIZE];
	struct __stackNode__ *next;
} stackNode;

typedef struct __stack__ {
	stackNode *head;
	int count;
	int allocCount;
} stack;

void * createStack()
{
	stack *st;

	st = (stack *)malloc(sizeof(stack));
	st->head = NULL;
	st->count = 0;
	st->allocCount = 0;
	return (void *)st;
}

void push(void *s, void *item)
{
	stackNode *node;
	int slot;
	stack *st = (stack *)s;

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

void * pop(void *s)
{
	stackNode *node;
	void *item;
	int slot;
	stack *st = (stack *)s;

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


void deleteStack(void *s)
{
	stack *st = (stack *)s;
	while (st->count) {
		pop(st);
	}
	if (st->head) {
		free(st->head);
	}
	free(st);
}


int size(void *st)
{
	return ((stack *)st)->count;
}
