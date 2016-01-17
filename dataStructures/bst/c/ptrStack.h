#include <stdio.h>

#define PTR_STACK_SIZE 1024
typedef struct ptrStack_t_ {
    void *store[PTR_STACK_SIZE];
    int head;
} ptrStack_t;

void ptrStack_init(ptrStack_t *ptrStack) {
    ptrStack->head = -1;
}

int ptrStack_push(ptrStack_t *ptrStack, void *x) {
    if (ptrStack->head == PTR_STACK_SIZE) {
        return -1;
    }
    ptrStack->store[ptrStack->head] = x;
    ptrStack->head++;
    return 0;
}

void * ptrStack_pop(ptrStack_t *ptrStack) {
    if (ptrStack->head == -1) {
        return NULL;
    } else {
        return ptrStack->store[--ptrStack->head];
    }
}

int is_ptrStack_empty(ptrStack_t *ptrStack) {
    return (ptrStack->head ==  -1);
}
