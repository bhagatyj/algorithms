#include <iostream>
#include <map>
#include <vector>

/* 
 * Problem Definition:
 *
 * Current Solution:
 *  From Wikipedia
 *
 */
using namespace std;

void
printIntVectorVector( vector< vector<int> > answerList ) {
    for( vector< vector<int> >::iterator it = answerList.begin(); 
                    it != answerList.end(); it++ ) {
        for( vector<int>::iterator it2 = it->begin(); 
                    it2 != it->end(); it2++ ) {
            cout << *it2 << "  " ;
        }
        cout << endl;
    }
    cout << endl;
}

vector< vector<int> >
find3Sum( vector<int> input, int sum) {

    sort( input.begin(), input.end() );
    unsigned size = input.size();
    vector<int>::iterator start, low, high, end;
    vector< vector<int> > answerList;

    end = input.end() - 3;
    for (start = input.begin(); start < end; start++ ) {
        low = start + 1;
        high = input.end() - 1;
        
        while ( low < high ) {
            if ( *start + *low + *high == sum ) {
                vector<int> answer;
                answer.push_back(*start);
                answer.push_back(*low);
                answer.push_back(*high);
                answerList.push_back(answer);
                // We need to move something here to make 
                // forward progress.
                // Moving low forward.
                // This implies that, duplicate results are lost.
                low++;
            }
            if ( *start + *low + *high < sum ) { low++; } 
            if ( *start + *low + *high > sum ) { high--; } 
        }
    }
    return answerList;
}

void 
testCase1() {
    int nums[] = { -6, -5, -4, -2, -1, 2, 5, 7, 9, 9 };
    vector<int> input( begin( nums ), end( nums ) );
    vector< vector<int> > answer = find3Sum( input, 0 );
    printIntVectorVector( answer );
}


int main( ) {
   testCase1();
}
