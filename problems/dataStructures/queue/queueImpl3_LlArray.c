
/*

Queue using Linked Lists:


  --------
 | headB  |-----> NULL
 |--------|
 | tailB  |-----> NULL
  --------


  --------
 | headB  |---------.
 |--------|         |
 | tailB  |-----.   |
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
 | headB  |---------------------.
 |--------|                     |
 | tailB  |-----.               |
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
	int numBlocks;
} queue;


void * createQueue()
{
	queue *q;

	q = (queue *) malloc(sizeof(queue));
	q->headBlock = NULL;
	q->tailBlock = NULL;
	q->headIdx = 0;
	q->tailIdx = 0;
	q->count =  0;
	q->numBlocks = 0;
	return (void *)q;
}


void enqueue(void *qp, void *item)
{
	block_t *block;
	queue *q = (queue *)qp;
	int slot;

	if (q->headIdx == 0) {
		// Need more slots
		block = (block_t *) malloc(sizeof(block_t));
		block->next = NULL;
		q->numBlocks++;

		if (q->headBlock) {
			q->headBlock->next = block;
		}
		q->headBlock = block;

		if (q->tailBlock == NULL) {
			q->tailBlock = block;
		}
		q->headIdx = 0;
	} else {
		block = q->headBlock;
	}

	slot = q->headIdx % BLOCKSIZE;
	block->items[slot] = item;
	q->headIdx = (q->headIdx + 1) % BLOCKSIZE;
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
	slot = q->tailIdx % BLOCKSIZE;
	item = block->items[slot];
	block->items[slot] = NULL;

	q->tailIdx++;
	if (q->tailIdx == BLOCKSIZE) {
		if (q->tailBlock != q->headBlock) {
			// headBlock has advanced.
			// we can also advance.
			q->tailBlock = block->next;

			if (q->headBlock == block) {
				q->headBlock = NULL;
			}
			free(block);
			q->numBlocks--;
		}
		q->tailIdx = 0;
	}

	q->count--;

	return item;
}

void deleteQueue(void *qp)
{
	queue *q = (queue *)qp;
	while (q->count) {
		dequeue(q);
	}
	free(q);
}


int size(void *qp)
{
	return ((queue *)qp)->count;
}
