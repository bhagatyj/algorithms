#include "queue.h"


int main(int argc, char **argv)
{
	char *line, input[MAXCHAR], *x;
	int len;
	void *q;

	q = createQueue();
	x = fgets(input, MAXCHAR, stdin);


	while (x) {
		len = strlen(x);
		if (len != 1) {
			line = (char *)malloc(sizeof(char)*len);
			strcpy(line, x);
			enqueue(q, (void *)line);
		} else {
			x = (char *) dequeue(q);
			if (x) {
				printf("%s",x);
			}
		}
		x = fgets(input, MAXCHAR, stdin);
	}


	while ((x = (char *)dequeue(q)) != NULL) {
		printf("%s", x);
	}
	deleteQueue(q);

}