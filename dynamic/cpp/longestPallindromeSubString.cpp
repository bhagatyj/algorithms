//
// Problem : 
//    Find the longest pallindromic substring of a string.
//
// Design:
//    
// Brute-force:
//      Find all the substrings and determine if pall for each
// Order:
//    for i in range(len(s)):
//      for j in range( i, len(s)):
//          find if str(i,j) is pallindrome by walking towards
//          center from the ends i, j.
//
//     The order is O(n^3)
//
// Dynamic:
//      Maintain a two-dimensional table [i, j] of booleans indicating
// if substring(i,j) is a pallindrome. Once we maintain this, we can
// determine palls without walking through the inner loop.
//      Length 1:
//      pall(i,j) = true if ( i == j )
//
//      Length 2:
//      pall(i,j) = true if ( diff(i,j) == 1 ) and
//                      str[i] == str[j]
//
//      pall(i-1, j+1) = true iff 
//                  pall(i,j) is true 
//                      and
//                  str[i] = str[j]
//
//

#include <iostream>
#include <string>
#include <map>
#include <assert.h>
using namespace std;

void
printPollTable( int **table, int len) {
    int i, j;
    for (i=0; i<len; i++) {
        for (j=0; j<len; j++) {
            std::cout << table[i][j] << "\t" ;
        }
        std::cout << std::endl;
    }
}

int
getLongestPallLength( string s ) {

    int len = s.length();
    int **table = (int **) malloc( len * sizeof( int *) );
    int i, j, k, maxLength, maxStart;

    for(i=0; i<len; i++) {
        table[i] = (int *) malloc( len  * sizeof(int) );
        for( j=0; j<len; j++) {
            table[i][j] = 0;
        }
    }

    // Initialize
    // All chars are pallindromes.
    maxLength = 1;
    maxStart = 0;
    for( i=0; i<len; i++ ) {
        table[i][i] = true;
    }

    // Handle the special case of 2.
    for( i=0; i<len-1; i++ ) {
        if( s[i] == s[i+1] ) {
            table[i][i+1] = true;
            // table[i+1][i] is also true;
            // But we need to fill-in only the cells above the diagonal
            // in the table. No need to fill the cells below. It will be
            // a duplicate set.
            maxLength = 2;
            maxStart = i;
        } else {
            table[i][i+1] = 0;
        }
    }
        
    int width, start, end;
    for( width = 3; width <= len; width++ ) {
        for( start=0; start<len-width+1; start++ ) {
            end = start + width - 1;

            // Find if this is a pallindrome.
            if( ( table[start+1][end-1] == true ) &&
                ( s[start] == s[end] ) ) {
                    table[start][end] = true;
                    maxLength = width;
                    maxStart = start;
            } else {
                table[start][end] = 0;
            }
        }
    }

    printPollTable( table, len );
    cout << "maxStart : " << maxStart << endl;

    return maxLength;
}


int
main() {
    map<string, int> problemSet;

    problemSet["hello"] = 2;
    problemSet["timesem"] = 5;
    problemSet["mesem"] = 5;
    problemSet["wasitacaroracatisaw"] = 19;
    problemSet["wasItacaroracatisaw"] = 11;
    problemSet["Wasitacaroracatisaw"] = 17;
    for( map<string, int>::iterator it = problemSet.begin(); 
              it != problemSet.end(); it++ ) {
        int longest = getLongestPallLength( it->first );
        cout << "Got: " << longest <<
             " Expected: " << it->second << endl;
        assert( longest == it->second );
    }
}

