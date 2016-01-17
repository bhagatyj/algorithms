#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXCHAR 256
#define MAXSTACKSIZE 256

void * createStack();
void deleteStack(void *st);
void push(void *st, void *item);
void * pop(void *st);
int size(void *st);
