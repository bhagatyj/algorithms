#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__
#include "base.h"

using namespace std;

/*
 * The Heap class ...
 * The Heap maintains the minHeap property - 
 * Value at child nodes is always more than parent's value.
 *
 * Index "0" is reserved to simplyfy the index math. 
 * With index-0 reserved, the node at index "x" has two children
 * at indices "2x" and "2x+1".
 *
 * 
 * Below are the indices of the nodes that are used to form the tree 
 * structure.
 * 
 *                          1
 *
 *                2                   3
 *
 *         4           5         6           7
 *
 *    8           9         10        11          12
 *
 * 13    14   15     16  17    18  19     20   21     22
 * 
 * Thus, walking through the array is equivalent of performing a level-walk
 * in a binary tree with the minHeap property.
 *  
 * The heap maintains itself (and even balances well) by implementing the 
 * "swim" and "sink" methods.
 *
 * Consider the "swim" method as used by nodes that have small key value. If
 * at any point (happens at insertions - especially tail insertion), a small 
 * node finds itself below large nodes, it swims up as much as it can 
 * (until it sees smaller parent above itself).
 *
 * Similarly, if at any point ( happens at deletion - especially during head deletion), 
 * a node finds that it is heavy, it sinks as much as it can - until both children are
 * larger than itself. In this case, care needs to be taken for cases such as 
 * (a) detect that the node is already a leaf - no more children
 * (b) detect that there is only one child, and check only that one.
 * (c) if there are two children, both should be checked and the node should sink
 *     in the direction of whichever child is less.
 * 
 * Head deletion is used to pick the smallest element in the minHeap. To re-arrange the
 * tree to a balanced structure, a neat technique can be used. Once the head element is
 * removed, the last element in the array is placed at the head and it is allowed to sink
 * as much as it can. This balances the tree and maintains minimal depth at all times.
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
protected:
    Heap *__heap;
};

HeapSort::HeapSort( int size ) : Sort::Sort( size ) {
    __heap = new Heap(size+1);
}

//
// 
void
HeapSort::sortIt() {
    unsigned i, value;

    for (i=0; i<__size; i++) {
        __heap->add(__store[i]);
    }

    value = __heap->delHead();
    i = 0;
    while (value != -1) {
        __store[i++] = value;
        value = __heap->delHead();
    }
}
#endif

