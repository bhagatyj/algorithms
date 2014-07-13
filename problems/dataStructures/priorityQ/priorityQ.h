#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1


// Use typedef for the function pointer
typedef int (* compareKeys_fn_t) (void *, void *);

// Create a PQ.
void * createPriorityQ(compareKeys_fn_t compare_fn);

// Create a PQ of initial capacity max.
//void * createPriorityQ(int max, compareKeys_fn_t compare_fn);

// Create a PQ from the keys in the array.
//void * createPriorityQ(int *arr, int count, compareKeys_fn_t compare_fn);

// Insert a key into the PQ.
void insert(void *pq, void *item);

// Return the largest key
//void * max(void *pq);

// Retuen and remove the largest key
void * delMin(void *pq);

// Is the PQ empty ?
//int isEmpty(void *PQ);

// Return the size
//int size(void *PQ);
