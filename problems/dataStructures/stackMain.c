#include "stack.h"


int main(int argc, char **argv)
{
	char *line, input[MAXCHAR], *x;
	int len;
	stack *st;

	st = createStack();
	x = fgets(input, MAXCHAR, stdin);


	while (x) {
		len = strlen(x);
		if (len != 1) {
			line = (char *)malloc(sizeof(char)*len);
			strcpy(line, x);
			push(st, (void *)line);
		} else {
			x = (char *) pop(st);
			if (x) {
				printf("%s",x);
			}
		}
		x = fgets(input, MAXCHAR, stdin);
	}


	while ((x = (char *)pop(st)) != NULL) {
		printf("%s", x);
	}
	deleteStack(st);

}