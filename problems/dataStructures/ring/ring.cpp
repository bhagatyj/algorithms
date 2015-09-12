#include "ring.h"
#include <assert.h>

namespace Example {

using namespace std;
Ring::Ring( int size ) {
    _area = new int [size];
    _size = size;
    _count = 0;
    _head = 0;
    _tail = 0;
}

Ring::~Ring() {
    delete[] _area;
}

bool
Ring::isEmpty() {
    return ( _tail == _head );
}

bool
Ring::isFull() {
    return ( incrementIndex(_head) == _tail);
}

int
Ring::incrementIndex( int index ) {
    return (index + 1 ) % _size;
}

int
Ring::push(int value) {
    if ( isFull() )
        return -1;
    _head = incrementIndex(_head);
    _count++;
    assert(_count < _size);
    _area[_head] = value;
    return 0;
}

int
Ring::pop() {
    if ( isEmpty() )
        return -1;
    assert(_count > 0);
    _tail = incrementIndex(_tail);
    _count--;
    return _area[_tail];
}

}
