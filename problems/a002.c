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
	char * lines[MAXSTACKSIZE];
	int top;
} stack;

void push(stack *st, char *line)
{
	return;
}

char * pop(stack *st)
{
	return NULL;
}


int main(int argc, char **argv)
{
	char *line, input[MAXCHAR], *x;
	int len;

	x = fgets(input, MAXCHAR, stdin);
	while (x) {
		len = strlen(x);
		line = (char *)malloc(sizeof(char)*len);
		strcpy(line, x);
		push(line);
		x = fgets(input, MAXCHAR, stdin);
	}
	while ((x = pop()) != NULL) {
		printf("%s\n", x);
	}

}