#include <iostream>
#include <vector>
#include <random>

// Problem Definition:
//
// You are given K sorted lists of numbers. Each list has length N/K, so the total length of all of the lists is N. Describe an algorithm using heaps to merge these K lists of N/K numbers into a single sorted list of N numbers. Your algorithm should run in O(N log K) time, although you will receive partial credit for less efficient algorithms.
//
using namespace std;

class Heap {
    
};
void
mergeSort( vector<int> &sortedList,
           vector<vector< int> > myLists ) {

    

}

int main() {

    vector<vector<int> > myLists;
    vector< int > sortedList;

    for (int i=0; i<5; i++) {
        for (int j=0; j<10; j++) {
            vector< int > myList;
            myList.push_back( rand() % 2048 );
        }
        sort( myList.begin(), myList.end() );
        myLists.push_back( myList );
    }

    mergeSort( sortedList, myLists );
}
