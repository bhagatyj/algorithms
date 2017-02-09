#include <iostream>
#include <map>
#include <string>
#include <assert.h>

// Given a string which only contains lowercase. You need delete the repeated letters 
// only leave one, and try to make the lexicographical order of new string is smallest. 
// i.e: bcabc 
// You need delete 1 'b' and 1 'c', so you delete the first 'b' and first 'c', 
// the new string will be abc which is smallest. 
// If you try to use greedy algorithm to solve this problem, 
// you must sure that you could pass this case: 
// cbacdcbc. answer is acdb not adcb 

using namespace std;
map<char, int> stringMap;
map<char, int> alreadyPrinted;


// Initialize the character map with number of occurrences
// for each character. 
// This routine uses the default initialization of maps.
// In cpp maps, if the key is not present, the first access
// would create it automatically and default initialize it.
// In this case, it would default initialize to 0 (int)
// 
void stringMapInit( string input ) {
	for ( char & c : input ) {
		stringMap[c]++;
	}
}

void printMap() {
    map<char, int>::iterator it = stringMap.begin();
    for ( ; it != stringMap.end() ; ++it ) {
        cout << it->first << " --> " << it->second << endl;
    }
}

void init( string input ) {
	stringMap.erase( stringMap.begin(), stringMap.end() );
	alreadyPrinted.erase( alreadyPrinted.begin(), alreadyPrinted.end() );
    stringMapInit(input);
}

// The walkandPrint walks along the inputString. It uses the fact 
// that maps are arranged in sorted order of keys for simple key
// types. If the char being walked is the first one in the map,
// it deserves to be printed. So it prints it.
//
// If the char being walked is not the first one in the map,
// but it no longer appears in the input string, this is our last
// chance to print it. However, before printing it, we should make
// sure that to print any chars that are more deserving.
//
// So, before printint the last char, we scan all the chars from
// last printed index to current index and print them.
//
string
walkAndPrint( string input ) {
    string output;
    map<char, int>::iterator it;
    char lowestChar;
    int size = input.size();
    int lastPrintedIndex = 0;

	cout << "Input String: " << input << endl;
	init( input );
	printMap();
    for (int i=0; i<size; i++) {
        char c = input[i];
        if ( stringMap.empty() ) {
            cout << "Empty map" << endl;
            break;
        }

        if (alreadyPrinted.find(c) != alreadyPrinted.end()) {
            continue;
        }

        it = stringMap.begin();
        lowestChar = it->first;

        cout << "Walking :: Char :: " << c 
			 << " Lowest : " << lowestChar << endl;


        if ( c <= lowestChar ) {
            cout << "Appending lowestChar: " << c << endl;
            output.append(string(1, c));
            stringMap.erase(c);
            alreadyPrinted.insert(pair<char, int>(c, 0));
            lastPrintedIndex = i;
        } else {
            int j;
            stringMap[c]--;
            if (stringMap[c] == 0) {
                cout << "Last chance " << c << endl;
            	// Before appending a last chance guy
            	// Check if there is anyone who is more deserving 
            	// and not printed so far.
            	for (j=lastPrintedIndex; j<i; j++) {
                	if (input[j] < c) {
                    	if (alreadyPrinted.find(input[j]) != alreadyPrinted.end()) {
                        	continue;
                    	}
                    	cout << "Appending more deserved folks: "
								<< input[j] << endl;
                    	output.append(string(1, input[j]));
                    	stringMap.erase(input[j]);
                    	alreadyPrinted.insert(pair<char, int>(input[j], 0));
                    	lastPrintedIndex = i;
                	}
            	}
                cout << "Appending last chance " << c << endl;
                output.append(string(1,c));
                stringMap.erase(c);
                alreadyPrinted.insert(pair<char, int>(c, 0));
            }
            
        }
    }
    cout << "Here is the ans..." << output << endl;
	return output;
}

int main(int argc, char **argv) {
    assert( walkAndPrint( "cbacdcbc" ) == string("acdb") );
    assert( walkAndPrint( "cbadcdcbc" ) == string("acdb") );
}
