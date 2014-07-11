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
#define MAXCHAR 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTACKSIZE 256

typedef struct __stack__ {
	char ** lines;
	int top;
	int numLines;
} stack;

stack * createStringStack(int numLines)
{
	stack *st;

	st = (stack *)malloc(sizeof(stack));
	st->lines = (char **)malloc(sizeof(char *) * numLines);
	st->top = -1;
	st->numLines = numLines;
	return st;
}

void deleteStringStack(stack *st)
{
	free(st->lines);
	free(st);
}

void push(stack *st, char *line)
{
	if (st->top == st->numLines) {
		printf("Too many lines\n");
		return;
	}
	st->lines[++st->top] = line;
}

char * pop(stack *st)
{
	char *line;

	if (st->top == -1) {
		return NULL;
	}
	line = st->lines[st->top];
	st->lines[st->top] = NULL;
	st->top--;
	return line;
}

int size(stack *st)
{
	return st->top + 1;
}

int main(int argc, char **argv)
{
	char *line, input[MAXCHAR], *x;
	int len;
	stack *st;

	st = createStringStack(256);
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