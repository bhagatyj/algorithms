/*
 * Problem: 
 * Length of the longest substring without repeating characters
 * Given a string, find the length of the longest substring without 
 * repeating characters. For example, the longest substrings without 
 * repeating characters for “ABDEFGABEF” are “BDEFGA” and “DEFGAB”, 
 * with length 6. For “BBBB” the longest substring is “B”, with length 1. 
 * For “GEEKSFORGEEKS”, there are two longest substrings shown in the 
 * below, with length 7. "EKSFORG", "KSFORGE"
 *
 * Solution:
 * Walk through the array
 * Create a map of characters seen.
 * If you come across a character already seen, reset the map.
 * Before resetting, remember the start/length of the last run.
 *
 */

#include <iostream>
#include <assert.h>
#include <string>
#include <map>
using namespace std;

string findSubString( string input ) {
    map<char, int> charMap;
    int start, length;
    int bestStart, bestLength, size;
    
    start = 0; length = 0;
    bestStart = 0; bestLength = 0;
    size = input.size();

    for ( int curr=0; curr<size; curr++ ) {
        if ( charMap.find( input[ curr ] ) == charMap.end() ) {
            length++; 
        } else {
            if ( length > bestLength ) {
                bestLength = length;
                bestStart = start;
            }
            start = curr;
            length = 1;
            charMap.clear();
        }
        charMap[ input[ curr ] ] = 1;
    }
    return input.substr(bestStart, bestLength);
}
int main() {
    cout << findSubString( string("geeksforgeeks") ) << endl;
    cout << findSubString( string("bbbbbb") ) << endl;
    cout << findSubString( string("abcabc") ) << endl;
}

