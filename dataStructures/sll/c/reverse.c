/*
 * Reverse a SLL
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_ { 
    struct node_ *next;
    int data;
} node;

node *head = NULL;

void insert( int value ) {

    node *n = (node *) malloc(sizeof(node));
    if (!n) return;
    n->data = value;
    n->next = head;
    head = n;

}

void print( void ) {

    node *n = head;
    printf("List is \n");
    while (n) {
        printf("%d\n", n->data);
        n = n->next;
    }
    printf("\n");

}

void reverse() {
    node *curr, *prev, *next;

    curr = head;
    if ( !curr->next ) {
        return;
    }

    prev = NULL; 

    while (curr) {
        next       = curr->next;
        curr->next = prev;
        prev       = curr;
        curr       = next;
    }
    head = prev;
}

int main( int argc, char **argv) {

    int i;

    for (i=0; i<10; i++) {
        insert(i);
    }
    print();
    reverse();
    print();
}

