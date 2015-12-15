#include "stacks.h"
#include <assert.h>
using namespace std;

Node::Node( int value) {
	data = value;
	next = NULL;
}

Node *
Node::getNext( void ) {
	return next;
}

void
Node::setNext( Node *ptr ) {
	next = ptr;
}

int
Node::getData( void ) {
	return data;
}

Stack::Stack() {
	head = NULL;
	tail = NULL;
}

int
Stack::push( int value ) {

	Node *newNode = new Node( value );

	if ( newNode == NULL ) {
		return -1;
	}

	if ( head == NULL) {
		head = newNode;
		tail = newNode;
	} else {
		// insert at tail
		assert( tail );
		tail->setNext( newNode );
		tail = newNode;
	}
	return 0;
}

int 
Stack::pop( void ) {

	if ( head == NULL ) {
		return -1;
	}

	Node *popNode = head;
	head = head->getNext();

	if (head == NULL) {
		tail = NULL;
	}
	int value = popNode->getData();
	delete popNode;

	return value;
}

void
Stack::print( void ) {
	Node *nxt = head;

	if (nxt == NULL ) {
		cout << "Empty" << endl;
		return;
	}
	do {
		cout << nxt << " value: " << nxt->getData() << endl;
		nxt = nxt->getNext();
	} while (nxt);
}