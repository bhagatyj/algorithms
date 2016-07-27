#include <iostream>
#include <map>
#include <vector>

/* 
 * Problem Definition:
 *
 * Current Solution:
 *
 * Issue:
 *  When the twoSum is equal to sum, we need to run both cases.
 */
using namespace std;

void
printIntVector( vector<int> answer ) {
    for( vector<int>::iterator it = answer.begin(); it != answer.end(); it++ ) {
        cout << *it << "  " ;
    }
    cout << endl;
}

vector<int>
find3Sum( vector<int> input, int sum) {

    sort( input.begin(), input.end() );
    unsigned size = input.size();
    vector<int>::iterator low, high;
    int n1, n2, n3, twoSum;
    vector<int> answer;

    low = input.begin();
    high = input.end() - 1;

    while ( low < high ) {
        n1 = *low;
        n2 = *high;
        cout << "Choosing n1:" << n1 << " and n2:" << n2 << endl;
        twoSum = n1 + n2;
        n3 = sum - twoSum;
        // Start binary search for n3.
        if ( find( low + 1, high , n3 ) != high ) {
            cout << "Found the answer...." << endl;
            answer.push_back(n1);
            answer.push_back(n2);
            answer.push_back(n3);
            break;
        }
        if ( twoSum < sum ) { low++; } else { high--; }
    }
    return answer;
}

void 
testCase1() {
    int nums[] = { -6, -4, -1, 0, 1, 5, 9 };
    vector<int> input( begin( nums ), end( nums ) );
    vector<int> answer = find3Sum( input, 0 );
    printIntVector( answer );
}


int main( ) {
   testCase1();
}
