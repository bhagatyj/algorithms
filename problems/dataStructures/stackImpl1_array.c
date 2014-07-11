// Stacks
	// stack * createStringStack(int N)
	// void push (stack *st, char *line)
	// char * pop(stack *st)
	// int isStackEmpty(stack *st)
// UseCase
	// Get strings from STDIN
	// And print them in reverse order.
#include "stack.h"

stack * createStack()
{
	stack *st;

	st = (stack *)malloc(sizeof(stack));
	st->top = 0;
	return st;
}

void deleteStack(stack *st)
{
	free(st);
}

void push(stack *st, void *item)
{
	if (st->top == MAXSTACKSIZE) {
		printf("Too many items\n");
		return;
	}
	st->items[st->top++] = item;
}

void * pop(stack *st)
{
	void *item;

	if (st->top) {
		item = st->items[--st->top];
		st->items[st->top] = NULL;
		return item;
	}
	return NULL;

}

int size(stack *st)
{
	return st->top;
}
