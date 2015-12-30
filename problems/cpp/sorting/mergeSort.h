#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__
#include "base.h"
#include <algorithm>

using namespace std;

class MergeSorter : public Sort {
protected:
    int *__store2;
public:
    void sortIt();
    MergeSorter( int size );
    ~MergeSorter( );
    void printStore2();
    void swapStore();
    void merge( int src[], int dst[], int start_left, int start_right, int end_right);
};

MergeSorter::MergeSorter( int size ) : Sort::Sort( size ) {
    int i;
    __store2 = new int[__size];
    if (__store2 == NULL) {
        cout << "Error in allocation" << endl;
    }
    for (i=0; i<__size; i++) {
        __store2[i] = 0;
    }
}

void
MergeSorter::printStore2() {
    int i;
    cout << "Store 2:: " << __size << " elements" << endl;
    for (i=0; i<__size; i++) {
        cout << "Element:" << i << "\t : \t"<< __store[i] << endl;
    }
}

MergeSorter::~MergeSorter() {
    delete[] __store2;
}

// Left Run is  left[start_left... end_left]
// Right Run is right[start_right..end_right]
void
MergeSorter::merge(int src[], int dst[], 
           int start_left, int start_right, int end_right) {

    int end_left = start_right;
    int i_left, i_right, idx;

    i_left = start_left;
    i_right = start_right;

    for ( idx = start_left; idx < end_right; idx++ ) {
        // If there are elements on both runs...
        // compare and copy the lesser one...
        if ( ( i_left < end_left ) &&
             ( i_right < end_right ) ) {
            if ( src[i_left] < src[i_right] ) {
                dst[idx] = src[i_left];
                i_left++;
            } else {
                dst[idx] = src[i_right];
                i_right++;
            }
        } else {
            // If there are no more elements on the right,
            // Just copy the elements from left..
            if ( i_left < end_left ) {
                dst[idx] = src[i_left];
                i_left++;
            } else {
                assert( i_right < end_right);
                dst[idx] = src[i_right];
                i_right++;
            }
        }
    }
}

void
MergeSorter::swapStore() {
    int *tmp;
    tmp = __store;
    __store = __store2;
    __store2 = tmp;
}

void
MergeSorter::sortIt() {
    // Each 1-element run in A is already sorted.
    // Make successively longer sorted runs
    // 2, 4, 8 and so on until whole array is sorted.
    int width, i, start_left, start_right, end_right;

    for ( width = 1; width < __size; width = 2*width ) {

        // Once the width is chosen, walk along the array
        // in strides of 2*width, and invoke merge of
        // two width-long arrays.

        for ( i=0; i<__size; i=i+2*width ) {

            // The left array starts at i 
            // The right array starts at i+width
            // Except cases where there is no right array.
            // For example, __size = 5, width = 2, i = 4
            // 
            // The right array ends at i+2*width
            // Except cases where right array is cut off by __size
            // For example, __size = 5, width = 4, i = 0
            // For example, __size = 6, width = 4, i = 4
            //
            // All these cases imply that start_right
            // and end_right need a min function.
            //
            // The merge function is written with these scenarios
            // in mind. Hence, if the right array is small or has no 
            // elements, merge function stops picking elements at the
            // end of right.
            // 
            start_left = i;
            start_right = min(i+width, __size);
            end_right = min(i+2*width, __size);

            merge( __store, __store2, start_left, start_right, end_right);

        }
        swapStore();
    }
}

#endif

