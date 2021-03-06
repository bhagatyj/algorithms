
// UseCase
	// Get strings from STDIN
	// And print them in reverse order.
#include "queue.h"

/* 
 * CRITICAL
 * Queue size has to be Desired-size + 1 <---
*/
typedef struct __queue__ {
	void **items; 
	int head;
	int tail;
} queue;

void * createQueue()
{
	queue *q;

	q = (queue *)malloc(sizeof(queue));
	q->head = 0;
	q->tail = 0;
	q->items = (void **)malloc(sizeof(void *) *MAXQSIZE);
	return (void *)q;
}

void deleteQueue(void *q)
{
	free((queue *)q);
}

void enqueue(void *qp, void *item)
{

	queue *q = (queue *)qp;
	if ((q->head +1)%(MAXQSIZE) == q->tail) {
		printf("Too many items\n");
		return;
	}
	q->items[q->head++] = item;
}

void * dequeue(void *qp)
{
	void *item;
	queue *q = (queue *)qp;

	if (q->head != q->tail) {
		item = q->items[q->tail];
		q->items[q->tail] = NULL;
		q->tail++;
		return item;
	}
	return NULL;

}

int size(void *qp)
{
	queue *q = (queue *)qp;
	if (q->head >= q->tail) {
		return (q->head - q->tail);
	} else {
		return ((MAXQSIZE - q->tail) + q->head );
	}
}
