#include "queue.h"

Queue::Queue(void) {
	__count = 0;
}

ArrayQueue::ArrayQueue( int size) : Queue() {
	__size = size;
	__store = (int *)malloc(sizeof(int)*size);
}

ArrayQueue::~ArrayQueue() {
	delete __store;
}

void 
ArrayQueue::enqueue( int data) {
	if (incr_index(__head) == __tail) {
		throw std::overflow_error("Q is Full");
		return;
	}
	__store[__head] = data;
	__head = incr_index(__head);
}

unsigned
ArrayQueue::incr_index(unsigned index) {
	return ( index + 1 ) % __size;
}

int 
ArrayQueue::dequeue() {
	if (__head == __tail) {
		return -1;
	}
	int value = __store[__tail];
	__tail = incr_index(__tail);
	return value;
}
