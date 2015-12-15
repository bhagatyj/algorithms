#include <iostream>

class Node {
private:
	int data;
	class Node *next;

public:
	Node( int value);
	Node * getNext( void );
	void setNext( Node *ptr );
	int getData( void );
};

class Stack {
private:
	class Node *head;
	class Node *tail;

public:
	int push( int value);
	int pop( void);
	void print( void );
	Stack();
};