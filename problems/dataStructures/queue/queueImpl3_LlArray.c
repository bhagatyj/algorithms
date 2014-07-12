
/*

Queue using Linked Lists:


  --------
 |  headBlock  |-----> NULL
 |--------|
 |  tailBlock  |-----> NULL
  --------


  --------
 |  headBlock  |---------.
 |--------|         |
 |  tailBlock  |-----.   |
  --------      |   |
                v   V
              --------
             |  next  | ---> NULL
             |--------|
             |  it 1  |
              --------
             |  it 2  |
              --------
             |  ....  |
              --------
             |  ....  |
              --------
             |  it N  |
              --------


  --------
 |  headBlock  |---------------------.
 |--------|                     |
 |  tailBlock  |-----.               |
  --------      |               |
                v               V
              --------       --------
             |  next  |---->|  next  | ---> NULL
             |--------|     |--------|
             |  it 1  |     | it N+1 |
              --------       --------
             |  it 2  |     | it N+2 |
              --------       --------
             |  ....  |     |  ....  |
              --------       --------
             |  ....  |     |  ....  |
              --------       --------
             |  it N  |     |  it 2N |
              --------       --------


*/

#include "queue.h"

#define BLOCKSIZE 16

typedef struct __block_t__ {
	void * items[BLOCKSIZE];
	struct __block_t__ *next;
} block_t;

typedef struct __queue__ {
	block_t *headBlock;
	block_t *tailBlock;
	int headIdx;
	int tailIdx;
	int count;
	int allocCount;
} queue;


void * createQueue()
{
	queue *q;

	q = (queue *) malloc(sizeof(queue));
	q->headBlock = NULL;
	q->tailBlock = NULL;
	q->headIdx;
	q->tailIdx;
	q->count = 0;
	q->allocCount = 0;
	return (void *)q;
}


void enqueue(void *qp, void *item)
{
	block_t *block;
	queue *q = (queue *)qp;
	int slot;

	if ((q->count + 1) > q->allocCount) {
		block = (block_t *) malloc(sizeof(block_t));
		block->next = NULL;
		q->allocCount += BLOCKSIZE;

		if (q->headBlock) {
			q->headBlock->next = block;
		}
		q->headBlock = block;

		if (q->tailBlock == NULL) {
			q->tailBlock = block;
		}
	} else {
		block = q->headBlock;
	}

	slot = q->count % BLOCKSIZE;
	block->items[slot] = item;

	q->count++;
}

void * dequeue(void *qp)
{
	block_t *block;
	void *item;
	int slot;
	queue *q = (queue *)qp;

	if (q->count == 0) {
		return NULL;
	}

	block = q->tailBlock;
	slot = (q->count - 1) % BLOCKSIZE;
	item = block->items[slot];
	block->items[slot] = NULL;

	if (slot == 0) {
		q->tailBlock = block->next;

		if (q->headBlock == block) {
			q->headBlock = NULL;
		}
		free(block);
	}

	q->count--;

	return item;
}

void deleteQueue(void *qp)
{
	queue *q = (queue *)qp;
	while (q->headBlock) {
		dequeue(q);
	}
	free(q);
}


int size(void *qp)
{
	return ((queue *)qp)->count;
}
