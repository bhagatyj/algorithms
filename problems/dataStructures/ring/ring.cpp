#include "ring.h"

namespace Example {

using namespace std;
Ring::Ring( int size ) {
    _area = new int [size];
    _size = size;
}

Ring::~Ring() {
    delete[] _area;
}

int
Ring::push(int value) {
    return 0;
}

int
Ring::pop() {
    return 0;
}
}
