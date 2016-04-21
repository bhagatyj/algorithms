// This should be split into
// stack-interface
// Various classes that implement that interface
// Each of these classes should support stacks of Templates.
// A main program that can 

#include <iostream>
using namespace std;

#define MAXCHAR 256
#define MAXSTACKSIZE 256


template <class T>
class Stack {
public:

	Stack()
	{
		top = 0;
		for (int i=0; i<MAXSTACKSIZE; i++) {
			items[i] = NULL;
		}
	}

	void push(T item)
	{
		if (top == MAXSTACKSIZE) {
			return;
		}
		items[top++] = item;
	}

	T pop(void)
	{
		T item;
		if (top == 0) {
			return NULL;
		} else {
			item = items[--top];
			items[top] = NULL;
		}
	}

	int size(void) {
		return top;
	}

private:
	T items[MAXSTACKSIZE];
	int top;

};

int main ()
{

	return 0;
}
