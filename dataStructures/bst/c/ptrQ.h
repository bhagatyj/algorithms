#include <stdio.h>

#define PTR_Q_SIZE 1024
typedef struct ptrQ_t_ {
    void *store[PTR_Q_SIZE];
    int head;
    int tail;
} ptrQ_t;

void 
ptrQ_init(ptrQ_t *pQ) {
    pQ->head = 0;
    pQ->tail = 0;
}

ptrQ_t *
get_new_ptrQ(void) {
    ptrQ_t *pQ;
    pQ = (ptrQ_t *)malloc(sizeof(ptrQ_t));
    if (pQ == NULL) {
        printf("No memory\n");
        exit(-1);
    }
    ptrQ_init(pQ);
    return pQ;
}

int 
ptrQ_incr(int index) {
    return ( (index + 1) % PTR_Q_SIZE );
}

int 
is_ptrQ_empty(ptrQ_t *pQ) {
    return (pQ->head ==  pQ->tail);
}

int 
is_ptrQ_full(ptrQ_t *pQ) {
    return (ptrQ_incr(pQ->head) ==  pQ->tail);
}

int 
ptrQ_enq(ptrQ_t *pQ, void *x) {
    if ( is_ptrQ_full(pQ) ) {
        return -1;
    }
    pQ->store[pQ->head] = x;
    pQ->head = ptrQ_incr(pQ->head);
    return 0;
}

void * 
ptrQ_deq(ptrQ_t *pQ) {
    void *ret_val;
    if (is_ptrQ_empty(pQ) ) {
        return NULL;
    } else {
        ret_val = pQ->store[pQ->tail];
        pQ->tail = ptrQ_incr(pQ->tail);
        return ret_val;
    }
}
