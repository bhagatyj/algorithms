#include "priorityQ.h"
#define MAXITEMS 512

typedef struct __priorityQ_t__ {
	void * items[MAXITEMS];
	compareKeys_fn_t compare_fn;
	int size;
} priorityQ_t;

void printPQ(priorityQ_t  *pq)
{
#ifdef DEBUG
	int i;

	printf("Printing PQ: ");
	for (i=1; i<=pq->size; i++) {
		printf("%d\t", *((int *)pq->items[i]));
	}
	printf("\n");
#endif
}

int less(priorityQ_t *pq, int idx1, int idx2)
{
	void *item1, *item2;

	item1 = pq->items[idx1];
	item2 = pq->items[idx2];

	if (pq->compare_fn(item1, item2)) {
		return TRUE;
	} else {
		return FALSE;
	}

}

void swap(priorityQ_t *pq, int idx1, int idx2)
{
	void *tmp;

	tmp = pq->items[idx1];
	pq->items[idx1] = pq->items[idx2];
	pq->items[idx2] = tmp;

}

void swim(priorityQ_t *pq, int idx)
{
	while ((idx > 1) && (less(pq, idx, idx/2))) {
		swap(pq, idx, idx/2);
		idx = idx/2;
	}
}

void sink(priorityQ_t *pq, int idx)
{
	while (2*idx <= pq->size) {
		// List is long. We may not have sunk enough.
		// Still more comparisons to do.
		if ((2*idx+1) > pq->size) {
			// One child only.
			// Check if node is larger than child. 
			// If so, swap.
			if (less(pq, 2*idx, idx)) {
				swap(pq, idx, 2*idx);
				idx = 2*idx;
			} else {
				return;
			}
		} else {
			// Two children.
			// Find the smaller of the two children.
			// If node is larger than that child, swap.
			if (less(pq, 2*idx, 2*idx+1)) {
				if (less(pq, 2*idx, idx)) {
					swap(pq, idx, 2*idx);
					idx = 2*idx;
				} else {
					return;
				}
			} else {
				if (less(pq, 2*idx+1, idx)) {
					swap(pq, idx, 2*idx+1);
					idx = 2*idx+1;
				} else {
					return;
				}
			}
		}
	}
}

/* In order to use the easy numbers
 * in comparison logic ie. k -> 2k, 2k+1,
 * we should not use index - 0.
 * So, index is equal to new size.
 */
void insertNode(priorityQ_t *pq, void *item)
{
	int index;

	pq->size += 1;
	index = pq->size;

	pq->items[index] = item;
#ifdef DEBUG
	printf("Swim item: %d, index: %d\n", *(int *)item, index);
#endif
	swim(pq, index);
}

void moveItems(priorityQ_t *pq)
{
	int i;
	for (i=2; i<=pq->size; i++) {
		pq->items[i-1] = pq->items[i];
	}
	return;
}

void * delHead(priorityQ_t *pq)
{
	void *head;

	if (pq->size == 0) {
		return NULL;
	}

	head = pq->items[1];

	if (pq->size == 1) {
		pq->items[1] = NULL;
		pq->size--;
	} else {
		pq->items[1] = pq->items[pq->size];
#ifdef DEBUG
		printf("Item 1 became %d\n", *(int *)pq->items[1]);
#endif
		pq->size--;
		sink(pq, 1);
	}
	printPQ(pq);
	return head;
}


void * createPriorityQ(compareKeys_fn_t compare_fn)
{
	priorityQ_t *pq;
	int i;

	pq = (priorityQ_t *)malloc(sizeof(priorityQ_t));
	pq->compare_fn = compare_fn;
	pq->size = 0;

	for (i=0; i<MAXITEMS; i++) {
		pq->items[i] = NULL;
	}

	return pq;
}


// Create a PQ of initial capacity max.
//void * createPriorityQ(int max, compareKeys_fn_t compare_fn);

// Create a PQ from the keys in the array.
//void * createPriorityQ(int *arr, int count, compareKeys_fn_t compare_fn);

// Insert a key into the PQ.
void insert(void *pqPtr, void *item)
{
	priorityQ_t *pq = (priorityQ_t *) pqPtr;
	insertNode(pq, item);
	printPQ(pq);
}

// Return the largest key
//void * max(void *pq);

// Retuen and remove the largest key
void * delMin(void *pqPtr)
{
	priorityQ_t *pq = (priorityQ_t *)pqPtr;
	void *max = delHead(pq);
	return max;
}

// Is the PQ empty ?
//int isEmpty(void *PQ);

// Return the size
//int size(void *PQ);
