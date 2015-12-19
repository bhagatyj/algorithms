/* 
 * Size of class and object
 * Even in cases where the constructor allocates data, it is allocated on the heap
 * A class's functions are present in the code segment. 
 * The size of the class C1, C3, C4 is 16. 
 * Even adding another variable doesn't increase it (in C4).
 * C2 has the same addition from C1 - but is derived. The size of C2 is 24.
 */

#include <iostream>

using namespace std;

class C1 {
	int a;
	int *data;
public:
	C1 ();
	void doNothing();
	~C1();
};

C1::C1 () {
	data = new int;
}

void 
C1::doNothing() {
	return;
}

C1::~C1 () {
	delete data;
}

class C2: C1 {
	int b;
};

class C3 {
	int a;
	int *data;
};

class C4 {
	int a;
	int *data;
};

int main () {
	C1 c1;
	cout << "Size of C1 is : " << sizeof(C1) << endl;
	cout << "Size of object C1 is : " << sizeof(c1) << endl;

	cout << "Size of C2 is : " << sizeof(C2) << endl;
	cout << "Size of C4 is : " << sizeof(C4) << endl;

}



