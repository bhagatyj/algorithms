#include <iostream>

namespace Example {
class RingBuffer {
    private:
        int _count;
        int _size;
        int _head;
        int _tail;
        int *_area;

    public:
        RingBuffer( int size );
        ~RingBuffer();
        int push( int value );
        int incrementIndex( int index );
        bool isEmpty();
        bool isFull();
        int pop();
};
}

        


