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
        answer.push_back( value % 2 );
        carry = value / 2;
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
    if ( carry ) {
        answer.push_back( carry );
    }
    reverse( answer.begin(), answer.end() );
    
    return answer;
}

int main() {

    string sn1 = "1000010";
    string sn2 = "1000010";
    vector<int> n1, n2;
    for ( char ch: sn1 ) { n1.push_back( (ch == '0' ? 0 : 1 ) ); }
    for ( char ch: sn2 ) { n2.push_back( (ch == '0' ? 0 : 1 ) ); }

    vector<int> answer = add(n1, n2);
    for( vector<int>::iterator it = answer.begin(); it != answer.end(); it++ ) {
        cout << *it;
    }
    cout << endl;
}
