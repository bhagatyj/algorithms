#include <iostream>
#include <map>
#include <assert.h>
#include <vector>
#include <queue>

using namespace std;

class Trie;

class Node {
    int  useCount;
    map<char, Node *> children;
    friend class Trie;
public:
    
};

class Trie {
public:
    void addWord(string s);
    bool searchWord(string s);
    void deleteWord(string s);
    static string findLongestSubstringRepeat( string s);
    string findLongestWord();
    void findLongestWordByDfs( Node *n, 
                        string wordSoFar,
                        string &longestWord );
    string findLongestWordByBfs( Node *n,
                        map< Node *, Node *> parents,
                        string longestWord );
    Trie();
    ~Trie();

private:
    Node *root;
};

Trie::Trie() {
    root = new Node();
    root->useCount = 1;
}

Trie::~Trie() {
    delete root;
}

void
Trie::addWord(string s) {
    Node *current = root;

    if ( searchWord( s ) ) {
        return;
    }

    s += '$';
    for (int i=0; i < s.length(); i++ ) {
        char ch = s[i];
        current->useCount++;
        if ( current->children[ch] == NULL ) {
            current->children[ch] = new Node();
        }
        current = current->children[ch];
    } 
    current->useCount++;
    cout << "added word:" << s.substr(0, s.length()-1) << endl;
}

void
Trie::deleteWord(string s) {
    queue<Node *> deleteQueue;
    Node *current = root, *next;

    if ( ! searchWord( s ) ) {
        return;
    }

    s += '$';
    for (int i=0; i < s.length(); i++ ) {
        char ch = s[i];
        if ( current->children[ch] == NULL ) {
            cout << "Error condition" << endl;
            return;
        } else {
            next = current->children[ch];
            next->useCount--;
            if ( next->useCount == 0 ) {
                deleteQueue.push(next);
                current->children[ch] = NULL;
            }
        }
        current = next;
    }
    while ( ! deleteQueue.empty() ) {
        Node *n = deleteQueue.front();
        deleteQueue.pop();
        delete n;
    }
    cout << "deleted word:" << s.substr(0, s.length()-1) << endl;
}

bool 
Trie::searchWord(string s) {
    Node *current = root;
    int i = 0;

    cout << "searching for " << s << endl;

    s += '$';
    for (i=0; i < s.length(); i++ ) {
        char ch = s[i];
        // Now, we have to check for the presence of
        // the character in our dictionary.
        // The wrong thing to do is:
        //
        // if ( current->children[ch] == NULL ) {
        //     return false;
        // } 
        //
        // That check adds an entry in the map for 'ch'
        // and assigns it to NULL. Though the result is
        // the same, the check has the side effect of
        // increasing the number of nodes in the trie.
        // This means that the number of nodes in our trie
        // increases just by searching. Not good.
        // 
        // Use the "find" form of searching instead.
        if ( current->children.find(ch) == current->children.end() ) { 
            return false;
        }
        current = current->children[ch];
    }
    if ( (current) && ( i == s.length() ) ) {
        return true;
    }
    return false;
}
        
/*
 * FIXME:
 * Implement a function to find the longest suffix match 
 * in a string.
 *
 * For example:
 * word: cucumber lsm: cu
 * word: abcdabcda lsm: abcda
 *
string
Trie::findLongestSubstringRepeat( string s) {

    int i=0;
    Trie *t = new Trie();

    for (i=0; i<s.length(); i++ ) {
        string sub = s.substr(i, s.length()-i );
        t->addWord(sub);
    }

    int maxLen = 0, len;
    Node *next, *current;
    string word("");
    string maxWord("");

    current = t->root();
    
    for( ch='a'; ch <='z'; ch++) {
        next = current->children[ch];
        len = 0;

        while ( next ) {
            word += ch;
            if ( next->wordMarker ) {
                if ( word.length() > maxWord.length() ) {
                    maxWord = word;
                }
            }
            for (ch='a'; ch='z'; ch++) {
            }
        }
    }
}
*/

string
Trie::findLongestWordByBfs( Node *n, 
                        map< Node *, Node *> parents,
                        string longestWord ) {
    // FIXME
    return "";    
}
// To find the longest word in a trie. 
void
Trie::findLongestWordByDfs( Node *n, 
                        string wordSoFar,
                        string &longestWord ) {

    map<char, Node *>::iterator it;
    for ( it = n->children.begin(); it != n->children.end(); it++ ) {
        // This if check for NULL is not needed if
        // the rest of the code is written properly.
        // Check out the comment in function searchWord.
        // Nevertheless, it is always good to be careful.
        if ( it->second ) {
            findLongestWordByDfs( it->second, 
                            wordSoFar + it->first, 
                            longestWord );
        }
        if ( wordSoFar.length() > longestWord.length() ) {
            longestWord = wordSoFar;
        }
    }
    return;    
}

// To find the longest word in a trie. 
// Use DFS to go down the graph and keep 
// recording max word so far.
string
Trie::findLongestWord() {

    map<Node *, Node *> parents1;
    map<Node *, Node *> parents2;
    string longestWord;

    parents1[root] = root;
    findLongestWordByDfs( root, "", longestWord );
    return longestWord;

}

int main( int argc, char **argv) {

    Trie trie;
    trie.addWord("managed");
    trie.addWord("man");
    trie.addWord("man");
    trie.addWord("world");
    trie.addWord("won");
    trie.addWord("cat");
    trie.addWord("catastrophic");
    //trie.deleteWord("world");
    cout << trie.searchWord("man") << endl;
    cout << trie.searchWord("world") << endl;
    cout << trie.searchWord("worn") << endl;
    cout << trie.searchWord("cat") << endl;
    cout << trie.searchWord("managed") << endl;
    cout << "Longest word in the dictionary is " 
         << trie.findLongestWord() << endl;

}
