/*
 * Problem Definition:
 * Given an unsorted array of integers, find a subarray which adds 
 * to a given number. If there are more than one subarrays with sum 
 * as the given number, print any of them.
 *
 * Additional Definition:
 * Just print one range.
 *
 * Solution Description:
 * Walk through the array once performing sums( 0 to i) and storing
 * them in a map.
 * Walk through the array once again performing sums( 0 to i) and
 * searching for "currentSum + sum" in the map.
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

void
printIntMap( map<int, int> answer ) {
    for( map<int, int>::iterator it = answer.begin(); it != answer.end(); it++ ) {
        cout << it->first << " --> " << it->second << endl;
    }
    cout << endl;
}

vector<int>
findConsecutive( vector<int> input, int desiredSum ) {
    map<int, int> sumReverseMap;
    int sum = 0;
    int size = input.size();
    for ( int i=0; i<size; i++ ) {
        sum += input[i];
        sumReverseMap[sum] = i;
    }
    //printIntMap(sumReverseMap);
    sum = 0;
    for ( int i=0; i<size; i++ ) {
        sum += input[i];
        int searchValue = sum + desiredSum;
        map<int, int>::iterator searchIndex = sumReverseMap.find( searchValue );
        if ( searchIndex != sumReverseMap.end() ) {
            if ( i <= searchIndex->second ) {
                cout << "We get a sum of " << desiredSum 
                    << " when walking from " << i+1
                    << " to " << sumReverseMap[searchValue] << endl;
                break;
            }
        }
    }
    return ( vector<int>( 0, 3 ) );
}

void
testCase1() {
    int q1[] = { -5, -2, -31, 5, 3, 0, 29, 1, 3, -10, 4, 2, 4, 7 };
    vector<int> vq1( begin(q1), end(q1) );
    findConsecutive( vq1, 33 );
    findConsecutive( vq1, 0 );
}

int main() {
    testCase1();
}
