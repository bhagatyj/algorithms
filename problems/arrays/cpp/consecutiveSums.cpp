/*
 * Problem Definition:
 * Given an unsorted array of integers, find a subarray which adds 
 * to a given number. If there are more than one subarrays with sum 
 * as the given number, print any of them.
 *
 * Solution Description:
 * Walk through the array once performing sums( 0 to i) and storing
 * them in a map of int-to-vectors. The map needs to be vectors so
 * that we accumulate all the possible ranges.
 *
 * Walk through the array once again performing sums( 0 to i) and
 * searching for "currentSum + sum" in the map.
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

void
printIntMap( map<int, vector<int> > answer ) {
    for( map<int, vector<int> >::iterator it = answer.begin(); it != answer.end(); it++ ) {
        cout << it->first << " --> " ;
        for( vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++ ) {
            cout << *it2 << "  " ;
        }
        cout << endl;
    }
    cout << endl;
}

vector<int>
findConsecutive( vector<int> input, int desiredSum ) {
    map<int, vector<int> > sumReverseMap;
    int sum = 0;
    int size = input.size();
    for ( int i=0; i<size; i++ ) {
        sum += input[i];
        sumReverseMap[sum].push_back(i);
    }
    // printIntMap(sumReverseMap);
    sum = 0;
    for ( int i=0; i<size; i++ ) {
        sum += input[i];
        int searchValue = sum + desiredSum;
        map<int, vector<int> >::iterator searchIndex = sumReverseMap.find( searchValue );
        if ( searchIndex != sumReverseMap.end() ) {
            for( vector<int>::iterator it = searchIndex->second.begin(); 
                    it != searchIndex->second.end(); it++ ) {
                // Check to ensure that the index found comes after the 
                // current index (i). If it comes before, that implies
                // that the sum is -ve.
                if ( i < *it ) {
                cout << "We get a sum of " << desiredSum 
                    << " when walking from " << i+1 
                    << " to " << *it << endl;
                }
            }
        }
    }
    return ( vector<int>( 0, 3 ) );
}

void
testCase1() {
    int q1[] = { -5, 33, -2, -31, 5, 3, 0, 29, 1, 3, -10, 4, 2, 4, 7 };
    vector<int> vq1( begin(q1), end(q1) );
    cout << "Find 33 " << endl;
    findConsecutive( vq1, 33 );
    cout << "Find 0 " << endl;
    findConsecutive( vq1, 0 );
}

int main() {
    testCase1();
}
