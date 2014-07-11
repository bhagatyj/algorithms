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
	char line[MAXCHAR];
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

void push(stack *st, char *line)
{
	stackNode *node;
	int len;

	node = (stackNode *)malloc(sizeof(stackNode));
	len = strlen(line);
	if (len > MAXCHAR) {
		printf("Too Long string\n");
		return;
	}
	strncpy(node->line, line, len);
	node->next = st->head;
	st->head = node;
	st->count++;
}

char * pop(stack *st, char *line)
{
	stackNode *node;

	if (st->count == 0) {
		return NULL;
	}

	node = st->head;
	st->head = node->next;
	st->count--;
	strcpy(line, node->line);
	free(node);
	return line;
}

void deleteStringStack(stack *st)
{
	char x[MAXCHAR];
	while (st->head) {
		pop(st, x);
	}
	free(st);
}


int size(stack *st)
{
	return st->count;
}

int main(int argc, char **argv)
{
	char input[MAXCHAR], *x;
	int len;
	stack *st;

	st = createStringStack();
	x = fgets(input, MAXCHAR, stdin);
	while (x) {
		len = strlen(x);
		push(st, x);
		x = fgets(input, MAXCHAR, stdin);
	}
	//memset(input, 0, MAXCHAR);
	while ((x = pop(st, input)) != NULL) {
		printf("%s", x);
		//memset(input, 0, MAXCHAR);
	}

}