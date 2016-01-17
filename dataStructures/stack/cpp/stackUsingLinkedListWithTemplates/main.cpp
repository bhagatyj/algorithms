#include "stacks.h"
#include "stacks.cpp"

using namespace std;

int main(int argc, char **argv) {

	Stack<int> st;
	int data;

	st.push(12);
	st.push(24);
	st.pop();
	st.push(36);
	st.push(48);
	st.push(60);

	cout << "Printing the stack so far " << endl;
	st.print();
	cout << endl;

	while ( ( data = st.pop() ) != -1 ) {
		cout << "Popped Value: " << data << endl;
	}

}