/*
 * Problem: Detect any loops in the LL.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_t_ {
    struct node_t_ *next;
    int data;
} node_t;

node_t *head = NULL;


node_t * insert (int data) {
    node_t *n;

    n = (node_t *) malloc(sizeof(node_t));
    if ( ! n ) {
        return NULL;
    }

    n->data = data;
    n->next = head;

    head = n;

    return n;
}

int detectLoop( void ){
    node_t *fp, *sp;

    fp = sp = head;
    while (fp) {
        if ( fp->next ) {
            fp = fp->next->next;
        } else {
            break;
        }
        sp = sp->next;

        if ( fp == sp ) {
            break;
        }
    }

    if ( fp->next ) {
        if ( fp == sp ) {
            printf("Loop detected\n");
            return 1;
        }
    }
    printf("No Loop detected\n");
    return 0;
}


int main( int argc, char **argv) {

    int i;
    node_t *n, *last;

    last = insert(100);
    for (i=0; i<10; i++) {
        n = insert(i);
    }
    detectLoop();
    last->next = n;
    detectLoop();
    for (i=11; i<20; i++) {
        n = insert(i);
    }
    detectLoop();

}

