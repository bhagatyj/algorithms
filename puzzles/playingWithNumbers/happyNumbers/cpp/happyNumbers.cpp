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

bool isHappyNumber( int n ) {
	vector <int> sequence;

	sequence.push_back(n);
	do {
		n = sumOfDigits(n);
		if ( find( sequence.begin(), sequence.end(), n ) != sequence.end() ) {
			return false;
		}
		sequence.push_back(n);
	} while ( n != 1 );
	return true;
}

int main( int argc, char **argv) {

	int i;
	cout << "The happy numbers from 1 to 100 are ... " << endl;
	for (i=1; i<1000; i++) {
		if ( isHappyNumber(i) ) {
			cout << i << endl;
		}
	}
	cout << endl;

}
