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
//   |<guessed- |                                       |       |
//   |-Pivot-   |    Unknowns....                       | Value |   
//   |-position>|                                       |  V1   |
//   ------------------------------------------------------------
//  
// We find the pivot's proper position
//   ____________________________________________________________
//   |                            |     |               |       |
//   |                            |Pivot|               | Value |   
//   |                            | V2  |               |  V1   |
//   ------------------------------------------------------------
//
// As we try to find the pivot's position, use swapping to move 
// values less than the pivot to the left hand side of the pivot
// position. This work will benefit us and reduce future work.
//  
// We swap the pivot value with the pivot's postion.
//   ____________________________________________________________
//   |                            |     |               |       |
//   |                            |Pivot|               | Value |   
//   |                            | V1  |               |  V2   |
//   ------------------------------------------------------------
//    low<------------------->high|     |low<-------------->high|
//
// Now, one element has come to its place. Continue with the rest
// of the elements. Split the array into two parts (left and right
// side of the pivot).
//
// In some ways, we can think of this as place selection for one
// item in the array + cutting the array into two parts. If it is
// pure place selection for the pivot, this would continue to be
// n-square problem as we find places for the rest of the items.
// Thankfully, we did more work while finding the pivot's place.
// We also moved every item that is larger than the pivot to its
// right. This implies that when looking for the right position 
// for any item in the right side, we do not have to visit the
// left side at all - thereby reducing the number of iterations
// in finding the right position.

// Once the iteration is completed, we get the structure
//   ____________________________________________________________
//   |                            |     |                       |
//   |<----less-than-pivot------->|Pivot|<---more-than-pivot--->|
//   |                            | V1  |                       |
//   ------------------------------------------------------------
//  
//   Now that one iteration is complete, we can recursively quick-sort
//   the first portion(0:pivot-1) and the second portion(pivot+1:n-1).
//
// In array implementations, implementation is easier if the pivot 
// is the last element. 
// 
// To achieve goals (c) and (d) above, we scan through the array - having
// an initial guessedPivotIndex of the begining of the array. If all 
// the elements in the array are greater than the pivot, the pivot can be
// placed at the guessedPivotIndex. 
// 
// If there are elements that are less than the pivot, then the guessedPivotIndex
// has to move to the right, leaving space for those elements.
// 
// So, the for loop has to look for less-than-pivot elements
// (1) swap the less-than-pivot element with the guessedPivotIndex
// (2) increment the guessedPivotIndex by 1
// After the loop is complete,
// the pivot has to be brought to the guessedPivotIndex by swapping 
// the high position with the guessedPivotIndex.
//
// # Considerations that make the code look elegant
// ==================================================
// 1. The terminating condition happens when there is only one element.
// When the high variable is the index of the last element (as opposed to
// (index_of_last + 1), it is elegant to express the terminating condition as
//  	if ( low == high ) { return; }
//
// This also makes the recursive calls to look with symmetric looking values:
// 		quicksort(low, pivotIndex-1);
// 		quicksort(pivotIndex+1, high);
// 	
//
// # Pitfalls..
// ============
// 1. Do not miss the terminating condition (low == high). It is better to
// write it explicitly.
//
// 2. It is easy to miss the last swap in the partition function. This swap
// brings the pivot to its rightful location.
//
// Note: The critical difference between the last swap and the swaps done inside
// the for loop is - guessedPivotIndex is not incremented in the last swap. This
// is why the last swap is written separately.

int
QuickSorter::partition(int low, int high) {
    int pivotValue = __store[high];
    int guessedPivotIndex = low;
    int i;

    for ( i=low; i<high; i++) {
        if ( __store[i] <= pivotValue ) {
            swap( guessedPivotIndex, i );
            guessedPivotIndex++;
        }
    }
    cout << "high: " << high << endl;
    swap(guessedPivotIndex, high);
    return guessedPivotIndex;
}

void
QuickSorter::quicksort(int low, int high) {
    int pivotIndex;

    if (low == high) {
		return;
	}
    pivotIndex = partition(low, high);
    quicksort(low, pivotIndex-1);
    quicksort(pivotIndex+1, high);
}
// 
void
QuickSorter::sortIt() {
    if (__size) {
        quicksort(0, __size-1);
    }
}
#endif

