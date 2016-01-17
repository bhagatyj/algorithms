#include <stdio.h>

#define PTR_Q_SIZE 1024
typedef struct ptrQ_t_ {
    void *store[PTR_Q_SIZE];
    int head;
    int tail;
} ptrQ_t;

void ptrQ_init(ptrQ_t *ptrQueue) {
    ptrQueue->head = 0;
    ptrQueue->tail = 0;
}

int ptrQ_incr(int index) {
    return ( (index + 1) % PTR_Q_SIZE );
}

int is_ptrQ_empty(ptrQ_t *ptrQueue) {
    return (ptrQueue->head ==  ptrQueue->tail);
}

int is_ptrQ_full(ptrQ_t *ptrQueue) {
    return (ptrQ_incr(ptrQueue->head) ==  ptrQueue->tail);
}

int ptrQ_enq(ptrQ_t *ptrQueue, void *x) {
    if ( is_ptrQ_full(ptrQueue) ) {
        return -1;
    }
    ptrQueue->store[ptrQueue->head] = x;
    ptrQueue->head = ptrQ_incr(ptrQueue->head);
    return 0;
}

void * ptrQ_deq(ptrQ_t *ptrQueue) {
    void *ret_val;
    if (is_ptrQ_empty(ptrQueue) ) {
        return NULL;
    } else {
        ret_val = ptrQueue->store[ptrQueue->tail];
        ptrQueue->tail = ptrQ_incr(ptrQueue->tail);
        return ret_val;
    }
}
