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

void
BubbleSort::sortIt() {
    unsigned swapped, i, end;

    end = __size;
    do {
        swapped = false;
        for (i=1; i<end; i++) {
            if ( __store[i] < __store[i-1] ) {
                swap( i, i-1 );
                swapped = true;
            }
        }
        end--;
    } while (swapped);
}
#endif

