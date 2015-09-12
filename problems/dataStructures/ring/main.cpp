#include "ring.h"

int main(int argc, char **argv) {

    Example::Ring *myRing = new Example::Ring(100);

    for (int i=0; i<99; i++) {
        myRing->push(i);
    }
    for (int i=0; i<99; i++) {
        printf("%d\n", myRing->pop() );
    }
}
