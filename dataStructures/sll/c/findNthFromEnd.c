/*
 * Question : Find nth element from the end of a single linked list
 *
 * Optimization : Use a single traversal
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_t_ {
    int data;
    struct node_t_ *next;
} node_t;

node_t *head = NULL;

void insert( int data ) {
    node_t *n;

    n = ( node_t *) malloc( sizeof(node_t) );
    if (n == NULL) {
        return;
    }
    n->data = data;
    n->next = head;
    head = n;
}

void printList( void ) {
    node_t *n;

    n = head;
    while (n) {
        printf("%d\n", n->data);
        n = n->next;
    }
}

void findNthFromEnd( int n ) {
    node_t *p, *q;
    int i = 0;

    p = head;
    while ( p ) {
        if ( i < n ) {
            i++;
            p = p->next;
            continue;
        }
        if ( i == n ) {
            i++;
            q = head;
            p = p->next;
            continue;
        } 
        q = q->next;
        p = p->next;
    }
    if ( i == n+1 ) {
        printf("%d th element from end is %d\n", n, q->data);
    }
    if ( i < n+1 ) {
        printf("Not enough elements in the list\n");
    }
}


int main(int argc, char **argv) {
    int i;
    int maxValue = 31;

    for (i=0; i<maxValue; i+=2) {
        insert(i);
    }
    printList();
    findNthFromEnd(0);
    findNthFromEnd(2);
    findNthFromEnd(6);
    findNthFromEnd(60);

}


/*
 * Solution: 
 *   Uses two pointers p, q. 
 *   P starts at head and runs till it goes down the road by "n" links.
 *   Q starts at head at this point and both run till P meets end.
 *   print Q.
 * 
 */
