// Stacks
	// stack * createStringStack(int N)
	// void push (stack *st, char *line)
	// char * pop(stack *st)
	// int isStackEmpty(stack *st)
// UseCase
	// Get strings from STDIN
	// And print them in reverse order.
#include "stack.h"

typedef struct __stack__ {
	void *items[MAXSTACKSIZE];
	int top;
} stack;

void * createStack()
{
	stack *st;

	st = (stack *)malloc(sizeof(stack));
	st->top = 0;
	return (void *)st;
}

void deleteStack(void *st)
{
	free((stack *)st);
}

void push(void *s, void *item)
{
	stack *st = (stack *)s;
	if (st->top == MAXSTACKSIZE) {
		printf("Too many items\n");
		return;
	}
	st->items[st->top++] = item;
}

void * pop(void *s)
{
	void *item;
	stack *st = (stack *)s;

	if (st->top) {
		item = st->items[--st->top];
		st->items[st->top] = NULL;
		return item;
	}
	return NULL;

}

int size(void *st)
{
	return ((stack *)st)->top;
}
