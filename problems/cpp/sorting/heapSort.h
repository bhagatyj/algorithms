#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__
#include "base.h"

using namespace std;

/*
 *
 */
class Heap : public Sort {
public:
    Heap( int size );
    void add ( int n );
    int delHead ( );
    void print();
protected:
    int __currSize;
    int __currIndex;
    void sink( int index );
    void swim( int index );
};

Heap::Heap( int size ) : Sort::Sort( size ) { 
    __currSize = 0;
    __currIndex = 1;
}

void
Heap::sink( int index ) {

    while ( 2*index <= __currSize ) {
        //cout << "Debug: " << index  << " " ;
        //cout << __currSize << endl;
        if ( 2*index+1 > __currSize ) {
            // One child only.
            // Check if node is larger than child. 
            // If so swap.
            if ( __store[index] > __store[2*index] ) {
                swap( index, 2*index );
                index = 2*index;
            } else {
                return;
            }
        } else {
            // There are two children.
            // Find the smaller of the two children.
            // If node is larger than that child, swap it.
            if ( __store[2*index] < __store[2*index+1] ) {
                if ( __store[index] > __store[2*index] ) {
                    swap ( index, 2*index );
                    index = 2*index;
                } else {
                    return;
                }

            } else {
                if ( __store[index] > __store[2*index+1] ) {
                    swap ( index, 2*index+1 );
                    index = 2*index+1;
                } else {
                    return;
                }
            }
        }
    }
}

void
Heap::swim( int index ) {

    while ( (index > 1) && ( __store[index] < __store[index/2] ) ) {
        swap( index, index/2 );
        index = index/2 ;
    }

}

void 
Heap::print() {
    int i;
    for (i=0; i<=__currSize; i++) {
        cout << i << " -> " << __store[i] << endl;
    }
}

void
Heap::add( int n ) {
    if ( __currSize == __size ) {
        cout << "Heap is full\n" << endl;
        return;
    }
    __store[__currIndex] = n;
    swim(__currIndex);
    __currSize++;
    __currIndex++;

}

int
Heap::delHead( ) {
    int value;

    if ( __currSize == 0 ) {
        cout << "Empty" << endl;
        return -1;
    }
    // Get the head value
    value = __store[1];
    if ( __currSize == 1 ) {
        __currSize = 0;
        __currIndex--;
    } else {
        __store[1] = __store[__currSize];
        __currSize--;
        __currIndex--;
        sink(1);
    }
    return value;
}

class HeapSort : public Sort {
public:
    void sortIt();
    HeapSort( int size );
};

HeapSort::HeapSort( int size ) : Sort::Sort( size ) { }

//
// 
void
HeapSort::sortIt() {
    unsigned last_swapped, i, end;

    last_swapped = __size;
    do {
        end = last_swapped;
        last_swapped = 0;
        for (i=1; i<end; i++) {
            if ( __store[i] < __store[i-1] ) {
                swap( i, i-1 );
                last_swapped = i;
            }
        }
        end--;
    } while (last_swapped);
}

#endif

