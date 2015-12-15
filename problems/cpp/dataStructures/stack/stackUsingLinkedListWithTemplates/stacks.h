#ifndef __STACKS_H__
#define __STACKS_H__

#include <iostream>

template <class T>
class Node {
private:
	T data;
	class Node *next;

public:
	Node( T value);
	Node * getNext( void );
	void setNext( Node *ptr );
	T getData( void );
};

template <class T>
class Stack {
private:
	class Node<T> *head;
	class Node<T> *tail;

public:
	int push( T value);
	T pop( void );
	void print( void );
	Stack();
};

#endif