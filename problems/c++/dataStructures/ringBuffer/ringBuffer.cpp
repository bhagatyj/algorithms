#include "ring.h"
#include <assert.h>

namespace Example {

using namespace std;
RingBuffer::RingBuffer( int size ) {
    _area = new int [size];
    _size = size;
    _count = 0;
    _head = 0;
    _tail = 0;
}

RingBuffer::~RingBuffer() {
    delete[] _area;
}

bool
RingBuffer::isEmpty() {
    return ( _tail == _head );
}

bool
RingBuffer::isFull() {
    return ( incrementIndex(_head) == _tail);
}

int
RingBuffer::incrementIndex( int index ) {
    return (index + 1 ) % _size;
}

int
RingBuffer::push(int value) {
    if ( isFull() )
        return -1;
    _head = incrementIndex(_head);
    _count++;
    assert(_count < _size);
    _area[_head] = value;
    return 0;
}

int
RingBuffer::pop() {
    if ( isEmpty() )
        return -1;
    assert(_count > 0);
    _tail = incrementIndex(_tail);
    _count--;
    return _area[_tail];
}

}
