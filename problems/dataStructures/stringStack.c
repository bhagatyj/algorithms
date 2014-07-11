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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 256
#define MAXSTACKSIZE 256

typedef struct __stack__ {
	void *items[MAXSTACKSIZE];
	int top;
} stack;

stack * createStringStack()
{
	stack *st;

	st = (stack *)malloc(sizeof(stack));
	st->top = 0;
	return st;
}

void deleteStringStack(stack *st)
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

int main(int argc, char **argv)
{
	char *line, input[MAXCHAR], *x;
	int len;
	stack *st;

	st = createStringStack();
	x = fgets(input, MAXCHAR, stdin);
	while (x) {
		len = strlen(x);
		line = (char *)malloc(sizeof(char)*len);
		strcpy(line, x);
		push(st, (void *)line);
		x = fgets(input, MAXCHAR, stdin);
	}
	while ((x = (char *)pop(st)) != NULL) {
		printf("%s", x);
	}

}