#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXCHAR 256


#define MAX_ELEMENTS 256

void * createQueue();
void deleteQueue(void *st);
void enqueue(void *st, void *item);
void * dequeue(void *st);
int size(void *st);
