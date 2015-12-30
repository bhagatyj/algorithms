#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__
#include "base.h"

using namespace std;

class BubbleSort : public Sort {
public:
    void sortIt();
    BubbleSort( int size );
};

BubbleSort::BubbleSort( int size ) : Sort::Sort( size ) {
    
}

//
// Optimized Bubble sort...
// It is advantageous to keep track of the number of swaps in the inner loop.
// If no swaps are done in inner loop, list is sorted and there is no need to 
// continue further.
//
// Also, it is advantageous to keep track of last swapped element. In the
// next run, there is no need to scan elements greater than last swapped 
// element.
// 
void
BubbleSort::sortIt() {
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

