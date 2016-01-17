#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__
#include "base.h"

using namespace std;

class QuickSorter : public Sort {
public:
    void sortIt();
    QuickSorter( int size );
    int partition(int low, int high);
    void quicksort(int low, int high);
};

QuickSorter::QuickSorter( int size ) : Sort::Sort( size ) {
    
}

//
// Quick Sort...
// Quicksort works by doing the following in each iteration.
// 
// During the iteration, the aim is to get the following done.
//     (a) Select a pivot
//     (b) find the right place for the pivot in the array.
//     (c) Bring all elements <= pivot to left side of pivot
//     (d) Bring all elements > pivot to right side of pivot
// 
// We start the Iteration with the following:
//   ____________________________________________________________
//   |<chosen-  |                                       |       |
//   |-Pivot-   |    Unknowns....                       | Pivot |   
//   |-position>|                                       |       |
//   ------------------------------------------------------------

// Once the iteration is completed, we get the structure
//   ____________________________________________________________
//   |                            |     |                       |
//   |<----less-than-pivot------->|Pivot|<---more-than-pivot--->|
//   |                            |     |                       |
//   ------------------------------------------------------------
//  
//   Now that one iteration is complete, we can recursively quick-sort
//   the first portion(0:pivot-1) and the second portion(pivot+1:n-1).
//
// In array implementations, implementation is easier if the pivot 
// is the last element. 
// 
// To achieve goals (c) and (d) above, we scan through the array - having
// a chosenPivotPosition. If all the elements in the array are greater than
// the pivot, the pivot can easily go to the chosenPivotPosition. 
// 
// If there are elements that are less than the pivot, then the chosenPivotPosition
// has to move to the right, leaving space for those elements.
// 
// So, the for loop has to look for less-than-pivot elements
// (1) swap the less-than-pivot element with the chosenPivotPosition
// (2) increment the chosenPivotPosition by 1
// After the loop is complete,
// the pivot has to be brought to the chosenPivotPosition by swapping 
// the high position with the chosenPivotPosition.

int
QuickSorter::partition(int low, int high) {
    int pivot = __store[high];
    int chosenPivotPosition = low;
    int i;

    for ( i=low; i<high; i++) {
        if ( __store[i] <= pivot ) {
            swap( chosenPivotPosition, i );
            chosenPivotPosition++;
        }
    }
    swap(chosenPivotPosition, high);
    cout << chosenPivotPosition << endl;
    return chosenPivotPosition;
}

void
QuickSorter::quicksort(int low, int high) {
    int pivot;

    if (low < high) {
        pivot = partition(low, high);
        quicksort(low, pivot-1);
        quicksort(pivot+1, high);
    }
}
// 
void
QuickSorter::sortIt() {
    if (__size) {
        quicksort(0, __size-1);
    }
}
#endif

