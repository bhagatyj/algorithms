#include "queue.h"
#include <stdexcept>

int main(int argc, char **argv) {
	unsigned i;

	ArrayQueue myq = ArrayQueue(20);
	for (i=0; i<10; i++ ) {
		myq.enqueue(i);
	}
	int value = myq.dequeue();
	while ( value != -1 ) {
		std::cout << value << std::endl; 
		value = myq.dequeue();
	}

	try {
		for (i=0; i<20; i++) {
			myq.enqueue(i);
		}
	}
	catch (std::exception &e) {
		//std::cout << "Hello" << std::endl;
		//std::cout << e.what() << std::endl;
	}

	return 0;
}