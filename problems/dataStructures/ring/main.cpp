#include "ring.h"

using namespace std;

int main(int argc, char **argv) {

    Example::Ring *myRing = new Example::Ring(100);

    for (int i=0; i<99; i++) {
        myRing->push(i);
    }
    for (int i=0; i<99; i++) {
        cout << myRing->pop() << endl;
    }
}
