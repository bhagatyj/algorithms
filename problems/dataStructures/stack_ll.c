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

#define MAXSTACKSIZE 256
#define MAXCHAR 256

typedef struct __stackNode__ {
	void * item;
	struct __stackNode__ *next;
} stackNode;

typedef struct __stack__ {
	stackNode *head;
	int count;
} stack;


stack * createStringStack()
{
	stack *st;

	st = (stack *)malloc(sizeof(stack));
	st->head = NULL;
	st->count = 0;
	return st;
}

void push(stack *st, void *item)
{
	stackNode *node;

	node = (stackNode *)malloc(sizeof(stackNode));
	node->item = item;
	node->next = st->head;
	st->head = node;
	st->count++;
}

void * pop(stack *st)
{
	stackNode *node;
	void *item;

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

void deleteStringStack(stack *st)
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

// Allocating the string is the application's job.
// Stack implementor just does push/pop.
int main(int argc, char **argv)
{
	char input[MAXCHAR], *x;
	stack *st;

	st = createStringStack();
	x = fgets(input, MAXCHAR, stdin);
	while (x) {
		char *line;
		line = (char*)malloc(MAXCHAR*sizeof(char));
		strcpy(line, x);
		push(st, (void *)line);
		x = fgets(input, MAXCHAR, stdin);
	}
	while ((x = pop(st)) != NULL) {
		printf("%s", (char *)x);
		free(x);
	}

}