#include <iostream>
#include <deque>

using namespace std;

int main() {

	deque<int> primes;

	primes.assign(3, 0);
	primes.push_back(7);
	primes.push_back(9);
	primes.push_front(2);
	primes[1] = 3;
	primes[2] = 5;
	// Assigning beyond the current indices is fine.
	// But the element cannot be retrieved by popping.
	primes[6] = 19;
	cout << primes[6] << endl;

	cout << "Here are my primes" << endl;
	while ( !primes.empty() ) {
		cout << primes.front() << endl;
		primes.pop_front();
	}
	// Value 19 is still inside.
	cout << primes[0] << endl;

}