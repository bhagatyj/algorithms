#include <iostream>
#include <vector>

using namespace std;

vector<int>
add( vector<int> n1, vector<int> n2 ) {
    vector<int> answer;
    int carry = 0;
    int s1 = n1.size();
    int s2 = n2.size();

    if( s1 == 0 ) { return n2; }
    if( s2 == 0 ) { return n1; }

    vector<int>::reverse_iterator it1 = n1.rbegin();
    vector<int>::reverse_iterator it2 = n2.rbegin();
    
    while( (it1 != n1.rend()) &&
           (it2 != n2.rend()) ) {
        int value = *it1 + *it2 + carry;
        answer.push_back( value % 10 );
        carry = value / 10;
        it1++; it2++;
    }
    if( it1 == n1.rend() ) {
        while( it2 != n2.rend() ) {
            answer.push_back( *it2 + carry );
            it2++; carry = 0;
        }
    }
    if( it2 == n2.rend() ) {
        while( it1 != n1.rend() ) {
            answer.push_back( *it1 + carry );
            it1++; carry = 0;
        }
    }
    // Do not ignore carry.
    if( carry ) {
        answer.push_back( carry );
    }
    reverse( answer.begin(), answer.end() );
    
    return answer;
}

int main() {

    int num1[] = { 1, 5, 6 };
    int num2[] = { 9, 2, 7 };
    vector<int> n1( begin(num1), end(num1) );
    vector<int> n2( begin(num2), end(num2) );

    vector<int> answer = add(n1, n2);
    for( vector<int>::iterator it = answer.begin(); it != answer.end(); it++ ) {
        cout << *it;
    }
    cout << endl;
}
