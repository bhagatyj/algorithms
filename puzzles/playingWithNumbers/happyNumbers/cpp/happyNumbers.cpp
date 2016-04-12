#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector <int> getDigits( int n ) {
    vector <int> digits;
    int x;
    while (n) {
        x = n %10;
        // avoid zeros.
        if (x) {
            digits.push_back(x);
        }
        n = n / 10;
    }
    return digits;
}

int sumOfDigits( int n ) {
    vector <int> digits = getDigits(n);
    int sum = 0;

    for ( int i=0; i< digits.size(); i++ ) {
        sum += digits[i] * digits[i];    
    }
    return sum;
}

// Maintain a sequence as the number progresses.
// If the same number happens again in the sequence,
// it is not a magic number. If we meet 1, it is a
// magic number.
// For vectors, the std::find
//   std::find( sequence.begin(), sequence.end(), n ) != sequence.end() 
//   runs in O(n) time
// For sets
//         sequence.find( n ) 
//      runs in O( log n )
// For maps
//     sequenece.find( n ) != sequence.end()
//     runs faster than O(n). 
//       
// map<int, bool> might be faster for the find.
bool isHappyNumber( int n ) {
    set <int> sequence;

    do {
        n = sumOfDigits(n);
        if ( find( sequence.begin(), sequence.end(), n ) != sequence.end() ) {
            return false;
        }
        sequence.insert(n);
    } while ( n != 1 );
    return true;
}

int main( int argc, char **argv) {

    int i;
    for (i=1; i<=100000; i++) {
        if ( isHappyNumber(i) ) {
        }
    }


}
