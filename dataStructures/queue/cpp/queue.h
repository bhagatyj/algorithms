#ifndef __Queue__
#define __Queue__
#include <iostream>


#define QUEUE_DEFAULT_SIZE 256
class Queue {
protected:
	int __count;

public:
	Queue(void);
	/* 
	 * The below functions are pure virtual.
	 * They are not implemented in the base class.
	 */
	virtual void enqueue( int data) = 0;
	virtual int dequeue() = 0;
};

class ArrayQueue: public Queue {
protected:
	int *__store;
	unsigned __head;
	unsigned __tail;
	unsigned __size;
	unsigned incr_index(unsigned index);

public:
	void enqueue( int data);
	int dequeue();
	ArrayQueue(int size=QUEUE_DEFAULT_SIZE);
	~ArrayQueue();
};

#endif