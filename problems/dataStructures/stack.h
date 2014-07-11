#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXCHAR 256
#define MAXSTACKSIZE 256

typedef struct __stack__ {
	void *items[MAXSTACKSIZE];
	int top;
} stack;

stack * createStack();
void deleteStack(stack *st);
void push(stack *st, void *item);
void * pop(stack *st);
int size(stack *st);
