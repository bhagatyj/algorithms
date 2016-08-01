#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// 
// Problem Definition:
//      Find a simple method to split line to tokens.
//
// Solution:
//      Use the getline function's 3rd parameter delim
//      This solution does not work if you want to parse
//      across lines but do not want "\n" as a delimiter.
//
using namespace std;

void
splitToTokens( string input, char delim, vector<string> &tokens ) {
    
    stringstream ssInput( input );
    string item;
    
    while( getline( ssInput, item, delim ) ) {
        tokens.push_back( item );
    }

}

int
main() {
    vector<string> tokens;

    splitToTokens( "a:b:c", ':', tokens );
    for( string token : tokens ) {
        cout << token << endl;
    }
    tokens.clear();
    
    splitToTokens( "here is a little line", ' ', tokens );
    for( string token : tokens ) {
        cout << token << endl;
    }
    tokens.clear();

    // The below case uses two delimiters: 'e' and '\n' to split 
    // the tokens. 
    splitToTokens( "hereis\na\nlittleline", 'e', tokens );
    for( string token : tokens ) {
        cout << token << endl;
    }
    tokens.clear();
}

/* Output:
 * a
 * b
 * c
 * here
 * is
 * a
 * little
 * line
 * h
 * r
 * is
 * a
 * littl
 * lin
 */
