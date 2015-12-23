#include "sLStore.h"

using namespace std;

SLNode::SLNode(int key, string data, SLNode *next) : Node(key, data), __next(next) {
}

SLStore::SLStore() {
	type.append("Linked List Store\n");
	head = NULL;
}

SLNode *
SLStore::find ( int key) {
	SLNode *n;

	n = head;
	while (n) {
		if (n->__key == key) {
			return n;
		}
		n = n->__next;
	}
	return NULL;
}

int 
SLStore::add ( int key, string data ) {
	SLNode *n;

	if ((n = find(key)) != NULL) {
		n->__data = data;
	} else {
		n = new SLNode(key, data, head);
		head = n;
	}
	return 0;
}

string 
SLStore::get( int key ) {

	SLNode *n = find(key);
	if (n) {
		return n->__data;
	}
	return NULL;
}

        
int 
SLStore::remove( int key ) {

	SLNode *n, *prev;

	// Check the head node first
	if (head) {
		if (head->__key == key) {
			n = head;
			head = head->__next;
		} else {
			n = head->__next;
			prev = head;
			while (n) {
				if (n->__key == key) {
					prev->__next = n->__next;
					break;
				} else {
					prev = prev->__next;
					n = n->__next;
				}
			}
		}
	}
	if (n) {
		delete n;
		return 0;
	}
	return -1;
}
        
void 
SLStore::print( void ) {

	SLNode *n;
	unsigned i = 0;

	n = head;
	cout << type << endl;
	while (n) {
		cout << "Node " << i++ << endl;
		cout << "Key : " << n->__key << endl;
		cout << "Data : " << n->__data << endl << endl;
		n = n->__next;
	}

	return;
}