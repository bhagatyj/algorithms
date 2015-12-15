#include "stacks.h"
#include <assert.h>
using namespace std;

template <class T>
Node<T>::Node( T value) {
	data = value;
	next = NULL;
}

template <class T>
Node<T> *
Node<T>::getNext( void ) {
	return next;
}

template <class T>
void
Node<T>::setNext( Node *ptr ) {
	next = ptr;
}

template <class T>
T
Node<T>::getData( void ) {
	return data;
}

template <class T>
Stack<T>::Stack() {
	head = NULL;
	tail = NULL;
}

template <class T>
int
Stack<T>::push( T value ) {

	Node<T> *newNode = new Node<T>( value );

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

template <class T>
T 
Stack<T>::pop( void ) {

	if ( head == NULL ) {
		return -1;
	}

	Node<T> *popNode = head;
	head = head->getNext();

	if (head == NULL) {
		tail = NULL;
	}
	T value = popNode->getData();
	delete popNode;

	return value;
}

template <class T>
void
Stack<T>::print( void ) {
	Node<T> *nxt = head;

	if (nxt == NULL ) {
		cout << "Empty" << endl;
		return;
	}
	do {
		cout << nxt << " value: " << nxt->getData() << endl;
		nxt = nxt->getNext();
	} while (nxt);
}