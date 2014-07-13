#include "priorityQ.h"

#define MAXCHAR 32

int compareInt(void *v1, void *v2)
{
	int *i1 = (int *)v1;
	int *i2 = (int *)v2;

#ifdef DEBUG
	printf("Comparing %d and %d : ", *i1, *i2);
#endif

	if (*i1 <= *i2) {
		return TRUE;
	}
	return FALSE;
}

void * createIntItem(int x)
{
	int *item = (int *)malloc(sizeof(int));
	*item = x;
	return item;
}

int main(int argc, char **argv)
{
	char input[MAXCHAR], *x;
	int len, *item;
	void *pq;

	pq = createPriorityQ(compareInt);
	x = fgets(input, MAXCHAR, stdin);

	while (x) {
		len = strlen(x);
		if (len != 1) {
			item = createIntItem(atoi(x));
			if (item) {
				insert(pq, (void *)item);
			}
		} else {
			item = (int *) delMin(pq);
			if (item) {
				printf("%d\n",*item);
			}
		}
		x = fgets(input, MAXCHAR, stdin);
	}


	while ((item = (int *)delMin(pq)) != NULL) {
		printf("%d\n", *item);
	}
	//deleteStack(st);

}