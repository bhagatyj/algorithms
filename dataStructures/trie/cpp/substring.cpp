#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Trie;

class Node {
    bool wordMarker;
    map<char, Node *> children;
    friend class Trie;
    Node();
public:
    void setMarker();
    
};

Node::Node() {
    wordMarker = false;
}

void
Node::setMarker() {
    wordMarker = true;
}

class Trie {
public:
    void addWord(string s);
    bool searchWord(string s);
    //void deleteWord(string s);
    Trie();
    ~Trie();

private:
    Node *root;
};

Trie::Trie() {
    root = new Node();
}

Trie::~Trie() {
    delete root;
}

void
Trie::addWord(string s) {
    Node *current = root;

    if ( s.length() == 0 ) {
        current->setMarker();
        return;
    }
    for (int i=0; i < s.length(); i++ ) {
        char ch = s[i];
        if ( current->children[ch] == NULL ) {
            current->children[ch] = new Node();
        }
        current = current->children[ch];
    } 
    current->setMarker();
}

bool 
Trie::searchWord(string s) {
    Node *current = root;
    int i = 0;

    for (i=0; i < s.length(); i++ ) {
        char ch = s[i];
        if ( current->children[ch] == NULL ) {
            return false;
        } 
        current = current->children[ch];
    }
    if ( ( current->wordMarker ) && ( i == s.length() ) ) {
        return true;
    }
    return false;
}
        

int main( int argc, char **argv) {

    Trie trie;
    trie.addWord("hello");
    trie.addWord("world");
    trie.addWord("won");
    trie.addWord("wore");
    cout << trie.searchWord("hello") << endl;
    cout << trie.searchWord("world") << endl;
    cout << trie.searchWord("worn") << endl;

}
