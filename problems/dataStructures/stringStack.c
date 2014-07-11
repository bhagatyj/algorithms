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
	char *lines[MAXSTACKSIZE];
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

void push(stack *st, char *line)
{
	if (st->top == MAXSTACKSIZE) {
		printf("Too many lines\n");
		return;
	}
	st->lines[st->top++] = line;
}

char * pop(stack *st)
{
	char *line;

	if (st->top) {
		line = st->lines[--st->top];
		st->lines[st->top] = NULL;
		return line;
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
		push(st, line);
		x = fgets(input, MAXCHAR, stdin);
	}
	while ((x = pop(st)) != NULL) {
		printf("%s", x);
	}

}