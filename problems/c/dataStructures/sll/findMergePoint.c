/* 
 * Find the merging point of two single link lists
 */

#include <stdlib.h>
#include <string.h>
 #include <stdio.h>

typedef struct node_ {
	int data;
	struct node_ *next;
} node;

node *h1 = NULL;
node *h2 = NULL;

void concatenate(node *l1, node *l2) {
	node *n;

	n = l1;
	while (n->next) {
		n = n->next;
	}
	n->next = l2;
}

void insert(node **head, int data) {
	node *n = (node *) malloc( sizeof( node ));
	if (!n) { return; }
	n->data = data;
	n->next = *head;
	*head = n;
}

void print(node **head) {
	node *n = *head;
	printf("Linked List at sll %p is:\n", head);
	while ( n != NULL ) {
		printf("0x%08x\n", n->data);
		n = n->next;
	}
	printf("\n");
}

void create_lists(int size1, int size2)
{
	int i;
	for (i=0; i<size1; i++) {
		insert(&h1, i);
	}

	for (i=0; i<size2; i++) {
		insert(&h2, i);
	}
}

unsigned len(node *n) {
	unsigned count = 0;
	while (n) {
		count++;
		n = n->next;
	}
	return count;
}

node * advance(node *n, unsigned count) {
	if (count == 0) {
		return n;
	}
	while ( n ) {
		count--;
		n = n->next;
		if (count == 0) {
			return n;
		}
	}
	return n;
}

node * find_merging_point(node *l1, node *l2) {

	unsigned len1, len2;

	len1 = len(l1);
	len2 = len(l2);

	if (len1 > len2) {
		l1 = advance(l1, len1-len2);
	} else {
		l2 = advance(l2, len2-len1);
	}

	// We have equal length lists now. 
	// They should have the same element at the meeting point
	while (l1 && l2) {
		if (l1 == l2) {
			printf("Lists meet at %p: 0x%08x \n\n",
						l1, l1->data);
			return l1;
		}
		l1 = l1->next;
		l2 = l2->next;
	}
	printf("Lists do not meet\n\n");
	return NULL;
}

int main(int argc, char **argv) {

	create_lists(2, 3);
	print(&h1);
	print(&h2);
	find_merging_point(h1, h2);
	concatenate(h1, h2);
	print(&h1);
	find_merging_point(h1, h2);

	h1 = NULL; h2 = NULL;
	create_lists(4, 4);
	print(&h1);
	print(&h2);
	find_merging_point(h2, h1);
	concatenate(h1, h2);
	print(&h1);
	find_merging_point(h1, h2);
	return 0;
}
