#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Node_t_ {
    struct Node_t_ *prev;
    struct Node_t_ *next;
    int data;
} Node_t;

void
printRing( Node_t *n ) {
    Node_t *begin = n;
    do {
        printf("%d\n", n->data );
        n = n->next;
    } while ( n != begin );
}

Node_t *
createNode( int x ) {
    Node_t *n = (Node_t *)malloc(sizeof(Node_t)); 
    if (!n) { printf("No more memory\n"); return NULL; }
    n->data = x;
    n->prev = n;
    n->next = n;
    return n;
}

void
insertNode( Node_t **head, Node_t *n) {
    Node_t *prev, *next, *curr;

    // No other nodes.
    if( *head == NULL ) { 
        *head = n; 
        return; 
    }

    curr = *head;
    // Only one node.
    if( curr->next == curr ) { 
        curr->next = n;
        curr->prev = n;
        n->next = curr;
        n->prev = curr;
        if ( curr->data > n->data ) {
            *head = n;
        }
        return;
    }
    
    // Many nodes.
    // Find the insertion point.
    // Three possible cases:
    // 1. New node is > than all existing nodes
    //      Insert new node 
    // 2. New node is < than all existing nodes
    // 3. New node is > some and < some
    
    // First check if all existing nodes are > than new node.
    if ( curr->data > n->data ) {
        n->next = curr;
        n->prev = curr->prev;
        curr->prev = n;
        n->prev->next = n;
        *head = n;
        return;
    }

    // Go through the List once and stop 
    Node_t *begin = curr;
    do {
        next = curr->next;
        if ( next->data > n->data ) {
            break;
        }
        curr = curr->next;
    } while ( curr != begin );

    // Check if next guy holds higher value.
    if ( next->data > n->data ) {
        n->next = curr->next;
        n->prev = curr;
        curr->next = n;
        n->next->prev = n;
        // No need to change the head.
        return;
    }

    // If we are here, all nodes are < new node.
    curr = curr->prev;
    n->next = curr->next;
    n->prev = curr;
    curr->next = n;
    n->next->prev = n;
    return;
}

int main() {
    Node_t *head = NULL;
    int i;
    for (i=0; i<10; i++) {
        int x = rand() % 1024;
        Node_t *n = createNode(x);
        insertNode(&head, n);
    }
    printRing(head);    
}
        
