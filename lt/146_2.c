#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define HASH_BUCKETS 997

typedef struct list_elem_t_ {
	struct list_elem_t_ *next;
	struct list_elem_t_ *prev;
} list_elem_t;

typedef struct node_t_ {
	list_elem_t hash_elem;
	list_elem_t q_elem;
	int key;
	int value;
} node_t;

typedef struct queue_t_ {
	list_elem_t *head;
	list_elem_t *tail;
	int count;
} queue_t;

node_t *nodes;
queue_t free_q;
queue_t inuse_q;;
queue_t hash_nodes[HASH_BUCKETS];

void
enqueue(queue_t *q, list_elem_t *n) {

	n->next = NULL;
	n->prev = NULL;

	if (q->head == NULL) {
		// First element
		q->head = n;
		q->tail = n;
		return;
	}
	n->next = q->head;
	q->head->prev = n;
	q->head = n;

}

void
enqueue_at_tail(queue_t *q, list_elem_t *n) {

	if (q->head == NULL) {
		// First element
		q->head = q->tail = n;
		return;
	}
	n->prev = q->tail;
	q->tail->next = n;
	q->tail = n;

}

void 
lruCacheInit(int capacity) {
	int i;

	nodes = (node_t *) malloc(sizeof(node_t) * capacity);
	memset(nodes, 0, sizeof(node_t) * capacity);
	memset(&free_q, 0, sizeof(queue_t));
	memset(&inuse_q, 0, sizeof(queue_t));
	memset(&hash_nodes, 0, sizeof(queue_t)*HASH_BUCKETS);

	for (i=0; i<capacity; i++) {
		enqueue(&free_q, &nodes[i].q_elem);
	}
}

void
lruCacheFree() {
	free(nodes);
	memset(&free_q, 0, sizeof(queue_t));
	memset(&inuse_q, 0, sizeof(queue_t));
	memset(&hash_nodes, 0, sizeof(queue_t)*HASH_BUCKETS);
}

int
get_hash(int key) {
	return (key % HASH_BUCKETS);
}

void
remove_elem(queue_t *q, list_elem_t *n) {
	if (n->next) {
		n->next->prev = n->prev;
	} else {
		q->tail = n->prev;
	}
	if (n->prev) {
		n->prev->next = n->next;
	} else {
		q->head = n->next;
	}
	n->next = n->prev = NULL;
}

list_elem_t *
dequeue(queue_t *q) {
	list_elem_t *elem;
	if (q->head) {
		elem = q->head;
		q->head = elem->next;
		if ( elem->next == NULL ) { 
			q->tail = NULL; 
		}
		elem->prev = NULL;
		elem->next = NULL;
		return elem;
	}
	return NULL;
}

list_elem_t *
dequeue_tail(queue_t *q) {
	list_elem_t *elem;
	if (q->tail) {
		elem = q->tail;
		q->tail = elem->prev;
		if (q->tail) {
			q->tail->next = NULL;
		}
		if ( elem->prev == NULL ) { 
			q->head = NULL; 
		}
		elem->prev = NULL;
		elem->next = NULL;
		return elem;
	}
	return NULL;
}
	
void
printQ(queue_t *q, int max) {
	list_elem_t *elem;
	int count = 0;
	elem = q->head;
	while ( elem ) {
		node_t *node = (node_t *) (elem - 1);
		printf("elem:%p key:%2d val:%4d next:%p prev:%p\n", elem, 
					node->key, node->value, elem->next, elem->prev);
		elem = elem->next;
		if (++count > max) {
			break;
		}
	}
}

void
lruCacheSet(int key, int value) {

	int hash_index = get_hash(key);
	list_elem_t *elem;

	elem = hash_nodes[hash_index].head;
	while (elem) {
		node_t *node = (node_t *)elem;
		if ( node->key == key ) {
			node->value = value;
			remove_elem(&hash_nodes[hash_index], elem);
			enqueue(&hash_nodes[hash_index], elem);
			return;
		}
	}
	printf("Not present in list\n");
	elem = dequeue_tail(&free_q);
	if ( elem ) {
		node_t *node = (node_t *)(elem-1);
		node->key = key;
		node->value = value;
		enqueue(&hash_nodes[hash_index], (list_elem_t *)node);
		enqueue(&inuse_q, elem);
	} else {
		int old_hash_index;
		list_elem_t *hash_elem;

		printf("No more free elem %p \n", elem);
		elem = dequeue_tail(&inuse_q);
		hash_elem = elem - 1;
		node_t *node = (node_t *)(hash_elem);
		old_hash_index = get_hash(node->key);
		remove_elem(&hash_nodes[old_hash_index], hash_elem);
		printf("Dequeued elem %p from hash %d for hash %d \n", 
				elem, old_hash_index, hash_index);
		assert(elem);
		node->key = key;
		node->value = value;
		enqueue(&inuse_q, elem);
		enqueue(&hash_nodes[hash_index], hash_elem);
	}
}

int
lruCacheGet(int key) {
	int hash_index = get_hash(key);
	list_elem_t *elem;

	elem = hash_nodes[hash_index].head;
	while (elem) {
		node_t *node = (node_t *)elem;
		if ( node->key == key ) {
			remove_elem(&inuse_q, elem+1);
			enqueue(&inuse_q, elem+1);
			return node->value;
		}
		elem = elem->next;
	}
	return -1;
}
		
int main() {
	
	int i, max;

	max = 10;
	lruCacheInit(max);
	printf("Init complete \n");
	for (i=0; i<10; i++) {
		lruCacheSet(i, i*i);
	}
	printf("Free Q\n");
	printQ(&free_q, max+1);
	printf("Inuse Q\n");
	printQ(&inuse_q, max+1);
	printf("Set complete \n");
	assert(lruCacheGet(0) == 0);
	printf("Get complete \n");
	printf("After Get 0\n");
	printf("Inuse Q\n");
	printQ(&inuse_q, max+1);
	lruCacheSet(10, 100);
	lruCacheSet(11, 121);
	lruCacheSet(12, 144);
	printf("Set complete \n");
	printf("Inuse Q\n");
	printQ(&inuse_q, max+1);
	for (i=1; i<3; i++) {
		printf("%d %d\n", i, lruCacheGet(i) );
		assert(lruCacheGet(i) == -1);
	}
	for (i=0; i<=12; i++) {
		printf("%d %d\n", i, lruCacheGet(i) );
		if ( ( i==0 ) || ( i > 3 ) ) {
			assert(lruCacheGet(i) == i*i);
		}
	}
	
	lruCacheFree();
}

