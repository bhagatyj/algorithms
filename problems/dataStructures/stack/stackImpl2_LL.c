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
	void * item;
	struct __stackNode__ *next;
} stackNode;

typedef struct __stack__ {
	stackNode *head;
	int count;
} stack;


void * createStack()
{
	stack *st;

	st = (stack *)malloc(sizeof(stack));
	st->head = NULL;
	st->count = 0;
	return (void *)st;
}

void push(void *s, void *item)
{
	stackNode *node;
	stack *st = (stack *)s;

	node = (stackNode *)malloc(sizeof(stackNode));
	node->item = item;
	node->next = st->head;
	st->head = node;
	st->count++;
}

void * pop(void *s)
{
	stackNode *node;
	void *item;
	stack *st = (stack *)s;

	if (st->count == 0) {
		return NULL;
	}

	node = st->head;
	st->head = node->next;
	st->count--;
	item = node->item;
	free(node);
	return item;
}

void deleteStack(void *s)
{
	stack *st = (stack *)s;
	while (st->head) {
		pop(st);
	}
	free(st);
}


int size(void *st)
{
	return ((stack *)st)->count;
}
