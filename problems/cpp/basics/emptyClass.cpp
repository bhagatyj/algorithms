/*
 *
 * What is the size of empty classes ? 
 * What about size of empty derived classes ? 
 * If the empty base class has size "x", does it 
 * increase the size of derived class ?
 *
 *  Bjarne Stroustrup's C++ Style and Technique FAQ, the reason the size is non-zero is 
 * "To ensure that the addresses of two different objects will be different." 
 * And the size can be 1 because alignment doesn't matter here, 
 * as there is nothing to actually look at.
 */
#include <iostream>

class C1 {};
class C2 {};

class C3: public C1, C2 {};

using namespace std;
int main(int argc, char **argv) {
    cout << "size of C1:" << sizeof(C1) << endl;
    cout << "size of C2:" << sizeof(C2) << endl;
    cout << "size of C3:" << sizeof(C3) << endl << endl;

    C1 a;
    C2 b;
    C3 c;
    cout << "size of object C1:" << sizeof(a) << endl;
    cout << "size of object C2:" << sizeof(b) << endl;
    cout << "size of object C3:" << sizeof(c) << endl << endl;
    cout << "size of int :" << sizeof(int) << endl;
}
