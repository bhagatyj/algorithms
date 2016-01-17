#include "store.h"

Node::Node(int key, string data) {
	__key = key;
	__data = data;
};

void 
Node::update(string data) {
	__data = data;
}