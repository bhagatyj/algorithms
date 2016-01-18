#include <stdio.h>

#define PTR_STACK_SIZE 1024
typedef struct ptrStack_t_ {
    void *store[PTR_STACK_SIZE];
    int head;
} ptrStack_t;

ptrStack_t * 
get_new_ptrStack() {
    ptrStack_t *pS;

    pS = (ptrStack_t *) malloc( sizeof(ptrStack_t) );
    if ( pS == NULL ) {
        printf("No memory\n");
        exit(-1);
    }
    pS->head = 0;
    return pS;

}

int 
is_ptrStack_empty(ptrStack_t *pS) {
    return (pS->head ==  0);
}

int 
is_ptrStack_full(ptrStack_t *pS) {
    return (pS->head ==  PTR_STACK_SIZE);
}

int 
ptrStack_push(ptrStack_t *pS, void *x) {
    if ( is_ptrStack_full(pS) ) {
        return -1;
    }
    pS->store[pS->head] = x;
    pS->head++;
    return 0;
}

void * 
ptrStack_pop(ptrStack_t *pS) {
    if ( is_ptrStack_empty(pS) ) {
        return NULL;
    } else {
        pS->head--;
        return pS->store[pS->head];
    }
}
