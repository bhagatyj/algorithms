
// Implement Hash Lists of queue to get performance.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


typedef struct list_head_t_ {
	struct list_head_t_ *next;
	struct list_head_t_ *prev;
} list_head_t;

typedef struct node_t_ {
	list_head_t elem;
	int key;
	int value;
} node_t;

node_t *nodes;
list_head_t free_q;
list_head_t inuse_q;

void 
init_list_head( list_head_t *elem) {
	elem->next = elem;
	elem->prev = elem;
}


void
enqueue( list_head_t *q, list_head_t *elem) {
	elem->prev = q;
	elem->next = q->next;
	q->next = elem;
	elem->next->prev = elem;
}

void
remove_elem(list_head_t *q, list_head_t *elem) {
	elem->prev->next = elem->next;
	elem->next->prev = elem->prev;
	init_list_head(elem);
}

list_head_t *
dequeue(list_head_t *q) {

	if (q->next == q) {
		return NULL;
	} else {
		list_head_t *elem;
		elem = q->next;
		q->next = q->next->next;
		q->next->prev = q;
		return elem;
	}
}
	
		
		
void lruCacheInit(int capacity) {
	node_t *n;
	int i;
	
	init_list_head(&free_q);
	init_list_head(&inuse_q);
	nodes = (node_t *) malloc(capacity * sizeof(node_t));
	memset(nodes, 0, capacity*sizeof(node_t));
	for (i=0; i<capacity; i++) {
		init_list_head(&(nodes[i].elem));
		enqueue( &free_q, &nodes[i].elem );
	}
    
}

void lruCacheFree() {

	free(nodes);
	init_list_head(&free_q);
	init_list_head(&inuse_q);
    
}

int lruCacheGet(int key) {
	list_head_t *elem;
	node_t *n;

	elem = inuse_q.next;
	while ( elem != &inuse_q ) {
		n = (node_t *)elem;
		if ( n->key == key ) {
			remove_elem( &inuse_q, (list_head_t *)n );
			enqueue( &inuse_q, (list_head_t *)n );
			return n->value;
		}
		elem = n->elem.next;
	}

	return -1;
}
    
void lruCacheSet(int key, int value) {
	list_head_t *elem;
	node_t *n;

	// Could be setting a new value to 
	// a key present in the Cache.
	// Look through the cache first.
	elem = inuse_q.next;
	while ( elem != &inuse_q ) {
		n = (node_t *)elem;
		if ( n->key == key ) {
			n->value = value;
			remove_elem( &inuse_q, (list_head_t *)n );
			enqueue( &inuse_q, (list_head_t *)n );
			return ;
		}
		elem = n->elem.next;
	}


	// Not present in the cache. 
	n = (node_t *) dequeue( &free_q );
	if ( n ) { 
		n->key = key;
		n->value = value;
		enqueue( &inuse_q, &n->elem );
	} else {
		// Re-use the least used entry
		n = (node_t *) inuse_q.prev;
		n->key = key;
		n->value = value;
		remove_elem( &inuse_q, (list_head_t *)n );
		enqueue( &inuse_q, (list_head_t *)n );
	}
}

void printQueue( list_head_t *q, int max ) {
	list_head_t *elem;
	node_t *n;
	int i = 0;

	elem = q->next;
	while ( elem != q ) {
		n = (node_t *)elem;
		printf(" %p %d -> %d prev: %p next:%p\n", 
				n, n->key, n->value, n->elem.prev, n->elem.next);
		if ( i++ > 2*max ) {
			break;
		}
		elem = n->elem.next;
	}
}


int main() {
	
	int i, max;

	max = 10;
	lruCacheInit(max);
	printQueue(&free_q, max);
	for (i=0; i<10; i++) {
		lruCacheSet(i, i*i);
	}
	printQueue(&inuse_q, max);
	lruCacheGet(0);
	printf("After Get 0\n");
	printQueue(&inuse_q, max);
	for (i=10; i<12; i++) {
		lruCacheSet(i, i*i);
	}
	printQueue(&inuse_q, max);
	for (i=1; i<3; i++) {
		printf("%d %d\n", i, lruCacheGet(i) );
		assert(lruCacheGet(i) == -1);
	}
	printQueue(&inuse_q, max);
	for (i=0; i<12; i++) {
		printf("%d %d\n", i, lruCacheGet(i) );
		if ( ( i==0 ) || ( i > 2 ) ) {
			assert(lruCacheGet(i) == i*i);
		}
	}
	
	lruCacheFree();
}
