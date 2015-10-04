#include "ring.h"
#include <assert.h>

using namespace std;

#define RINGSIZE 100
int main(int argc, char **argv) {

    Example::Ring *myRing = new Example::Ring(RINGSIZE+1);

    for (int i=0; i<RINGSIZE; i++) {
        assert( myRing->push(i) == 0);
    }
    for (int i=0; i<RINGSIZE; i++) {
        cout << myRing->pop() << endl;
    }
}
