#include <stdio.h>

// Create a PQ.
void * createPriorityQ(void);

// Create a PQ of initial capacity max.
void * createPriorityQ(int max);

// Create a PQ from the keys in the array.
void * createPriorityQ(int *arr, int count);

// Insert a key into the PQ.
void insert(void *pq, void *item);

// Return the largest key
void * max(void *pq);

// Retuen and remove the largest key
void * delMax(void *pq);

// Is the PQ empty ?
int isEmpty(void *PQ);

// Return the size
int size(void *PQ);
