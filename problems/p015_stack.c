#include "p015_stack.h"

stack * createStack(int size)
{
	stack *st = malloc(sizeof(stack));
	memset(st, 0, sizeof(stack));
	return st;
}

void push(stack *st, char c)
{

	if (st->top != MAXSTACKSIZE-1) {
		st->values[++st->top] = c;
	}
	//printf("pushed %c\n", c);

}

char pop(stack *st) 
{
	char c;
	int top = st->top;

	if (top == 0) {
		return 0;
	}
	c = st->values[top];
	st->values[top] = 0;
	st->top--;
	return c;
}

void printStack(stack *st)
{
	int i, top;

	top = st->top;
	printf("Stack is: ");
	for (i=0; i<=top; i++) {
		printf("%c", st->values[i]);
	}
	printf("\n");
}


int mainTest (int argc, char **argv)
{
	stack * st;
	st = createStack(20);

	push(st, 'a');
	push(st, 'n');
	push(st, 'u');
	push(st, 'g');
	printStack(st);
	printf("%c\n", pop(st));
	printStack(st);

	return 0;

}
