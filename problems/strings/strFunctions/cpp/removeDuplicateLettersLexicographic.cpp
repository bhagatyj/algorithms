/*
 * Problem: 
 *        Given a string which contains only lowercase letters, 
 * remove duplicate letters so that every letter appear once 
 * and only once. You must make sure your result is the smallest 
 * in lexicographical order among all possible results.
 *
 * Solution:
 *
 */


#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


class Solution {
public:
    string removeDuplicateLetters(string s);
};

string 
Solution::removeDuplicateLetters(string s) {

    vector<int> frequency(256, 0);
    vector<bool> addedToResult(256, false);

    // Go through the string once and make a
    // frequency chart
    for (char c : s) {
        frequency[c]++;
    }

    /*
     * Go through the characters in the input string.
     * We are going to choose chars and add them to result.
     *
     * While the current character is less than the last one
     * added to result and there are more instances of the
     * last one still left in the input string, pop the last
     * added and add the current one. Notice that this might pop
     * more than one element as it is a "while" statement.
     *
     */
    string result = "0"; // needed for the back
    
    for (char c : s) {

        frequency[c]--;
        // Already added --> skip. 
        if ( addedToResult[c] ) continue;

        while ( ( c < result.back() ) && 
                ( frequency[result.back()] ) )  {
            addedToResult[result.back()] = false;
            result.pop_back();
        }

        result += c;
        addedToResult[c] = true;
    }
    return result.substr(1);
}

