//	// Problem:
//	//
//	Given N strings. Each string contains only lowercase letters from (both inclusive). 
//  The set of  strings is said to be GOOD SET if no string is prefix of another string else, it is BAD SET. 
//  (If two strings are identical, they are considered prefixes of each other.)
//	
//	For example, aab, abcde, aabcd is BAD SET because aab is prefix of aabcd.
//	
//	Print GOOD SET if it satisfies the problem requirement. 
//	Else, print BAD SET and the first string for which the condition fails.
//	
//	Input Format 
//	First line contains , the number of strings in the set. 
//	Then next  lines follow, where  line contains  string.
//	
//	Constraints 
//	1 <= N <= 100000
//	1 <= Length of String <= 60

//	Output Format 
//	Output GOOD SET if the set is valid. 
//	Else, output BAD SET followed by the first string for which the condition fails.
//	
//	Sample Input00
//	
//	7
//	aab
//	defgab
//	abcde
//	aabcde
//	cedaaa
//	bbbbbbbbbb
//	jabjjjad
//	
//	Sample Output00
//	
//	BAD SET
//	aabcde
//	
//	Sample Input01
//	
//	4
//	aab
//	aac
//	aacghgh
//	aabghgh
//	Sample Output01
//	
//	BAD SET
//	aacghgh
//	Explanation 
//	aab is prefix of aabcde. So set is BAD SET and it fails at string aabcde.

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
// aab
// root--a-->()--a-->()--b-->($)
// aax
// root--a-->()--a-->()--b-->($)
//                     --x-->($)
// aabc
// root--a-->()--a-->()--b-->($)--c-->($)
//                     --x-->($)
//
// Constructing aabc will identify that it has to go beyond a wordEnd.

class Node {
    protected:
        map<char, Node *> children;
        bool wordEnd = false;
        friend class Trie;
        Node() {};
};

class Trie {
    protected:
        Node root;
    public:
        Trie() {}
        void addWord( string word );
        bool hasOverlaps = false;
        string *firstBadCase;
};

void
Trie::addWord( string word ) {

    Node *n = &root;
    Node *newNode;
    bool overlap = false;

    if( hasOverlaps ) { return; }
    for ( char &c : word ) {
        if( n->children.find(c) != n->children.end() ) {
            n = n->children[c];
            if( ( n->wordEnd ) && !hasOverlaps ) {
                overlap = true;
            }
        } else {
            newNode = new Node();
            n->children[c] = newNode;
            n = newNode;
        }
    }
    if( n ) {
        n->wordEnd = true;
    }
    if (overlap) {
        hasOverlaps = true;
        firstBadCase = new string(word);
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int count;
    Trie t;
    vector<string> words;
    cin >> count;
    for (int i=0; i<count; i++) {
        string word;
        cin >> word;
        t.addWord( word );
    }
    if( ! t.hasOverlaps ) {
        cout << "GOOD SET" << endl;
    } else {
        cout << "BAD SET" << endl;
        cout << *(t.firstBadCase) << endl;
    }   
    return 0;
}
