#ifndef __SELECTION_SORT_H__
#define __SELECTION_SORT_H__
#include "base.h"

using namespace std;

class SelectionSorter : public Sort {
public:
    void sortIt();
    SelectionSorter( int size );
};

SelectionSorter::SelectionSorter( int size ) : Sort::Sort( size ) {
    
}

//
// Selection sort...
// works by dividing array into two parts - sorted and unsorted.
// To begin with, the entire array is unsorted.
// As the algo progresses
//   ____________________________________________________________
//   |                            |                              |
//   |<----sorted-section-------->|<---unsorted section--------->|
//   |                            |                              |
//   ------------------------------------------------------------
//                                i
// 
// The outer loop variable "i" divides the array to sorted and unsorted
// sections. The aim of the inner loop is to find the next minimal element
// and append it to the sorted section.
// 
//  O(n-squared)
//
// Adv: very simple algo. No swaps are done on already sorted array.
//
void
SelectionSorter::sortIt() {
    unsigned  i, j, nextPositionToFill, indexOfMinAmongRemaining;

    for (i =0; i<__size; i++) {
        // find the postion of the min element in the unsorted part
        nextPositionToFill = i;
        indexOfMinAmongRemaining = i;
        for (j = i+1; j<__size; j++) {
            if ( __store[j] < __store[indexOfMinAmongRemaining] ) {
                indexOfMinAmongRemaining = j;
            }
        }
        // If indexOfMinAmongRemaining is same as nextPositionToFill,
        // the swap would just return.
        swap(indexOfMinAmongRemaining, nextPositionToFill);
    }

}
#endif
