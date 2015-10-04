#include <iostream>

namespace Example {
class Ring {
    private:
        int _count;
        int _size;
        int _head;
        int _tail;
        int *_area;

    public:
        Ring( int size );
        ~Ring();
        int push( int value );
        int incrementIndex( int index );
        bool isEmpty();
        bool isFull();
        int pop();
};
}

        


