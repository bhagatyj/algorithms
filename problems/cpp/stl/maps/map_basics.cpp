#include <iostream>
#include <map>

using namespace std;

// In map, once the item is inserted, you cannot change the key. 
// Modifying "it->first" gives error. 
// pair<const key_type, mapped_type>
//
int main(int argc, char **argv) {

    map<int, char> alphabets;
    int i;

	// Reading before initialization.
	// Value will be zero.
	// In CPP maps, as soon as you access the map with the [] operator,
	// if the key doesn't exist it gets added.
	// The default initializer of the type gets invoked
	// For ints and chars, the default value is 0.
	//
    for (i=0; i<26; i++) {
        cout << i << " --> " << alphabets[i] 
                  << " --> " << (int) alphabets[i] 
				  << endl;
    }

    for (i=0; i<26; i++) {
        alphabets[i] = 'a' + i;
    }
    for (i=0; i<26; i++) {
        cout << i << " --> " << alphabets[i] << endl;
    }

    alphabets[1] = 'B';
    // As the method at returns a reference, it can be used for assignment.
    alphabets.at(2) = 'C';
    // at can also be used to get a const reference.
    const char &x = alphabets.at(3);
    cout << x << endl;

    alphabets.erase(0);
    alphabets.insert( pair<int, char>( 0, 'A') );


    cout << "Forward" << endl;
    for ( map<int, char>::iterator it = alphabets.begin(); it != alphabets.end(); ++it ) {
        cout << it->first << " --> " << it->second << endl;
    }

    map<int, char>::iterator it = alphabets.find(5);
    cout << "5 maps to " << it->second << endl;
    cout << "7 maps to " << alphabets.at(7) << endl;
    cout << "8 maps to " << alphabets[8] << endl;

    map<int, int> squares;
    map<int, int> cubes;
    
    for (i=0; i<10; i++) {
        squares.insert(pair<int, int>(i, i*i));
        cubes.insert(pair<int, int>(i, i*i*i));
    }

    cubes.swap(squares);
    // Now cubes contains the squares and squares contain cubes.
    cout << "Cubes In Reverse - but it contains squares (just swapped)" << endl;
    for ( map<int,  int>::const_reverse_iterator rit = cubes.crbegin(); rit != cubes.crend(); ++rit ) {
        cout << rit->first << " --> " << rit->second << endl;
    }
    squares.swap(cubes);
    // Now cubes and squares are fine...
    cout << "Cubes In Reverse - now it is fine.. (swapped again)" << endl;
    for ( map<int,  int>::const_reverse_iterator rit = cubes.crbegin(); rit != cubes.crend(); ++rit ) {
        cout << rit->first << " --> " << rit->second << endl;
    }
    cout << "Number of elements in cubes is " << cubes.size() << endl;
    cubes.erase(cubes.begin());
    map<int, int>::iterator it_low, it_up;

    it_low = cubes.lower_bound(3);
    it_up = cubes.upper_bound(8); // actually points to 9.
    cubes.erase(it_low, it_up);

    cout << "Number of elements in cubes is " << cubes.size() << endl;
    cout << (cubes.empty() ? "Cubes is Empty" : "Cubes is not empty") << endl;
}

