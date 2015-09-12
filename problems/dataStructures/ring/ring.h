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
        int pop();
};
}

        


