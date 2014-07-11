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