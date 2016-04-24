#include <iostream>

// This skip list is used to maintain nodes with non-negative key values.
// The SkipList contains a dummy node as head. The head node has key
// value of -1. 

 using namespace std;

const int MAX_LEVEL = 7;
const int NUM_LEVELS = MAX_LEVEL+1;

class Node {
    int __value;
    class Node *next[NUM_LEVELS];
    friend class SkipList;
   
public:
    Node( int value) : __value(value) {
        for ( int i=0; i<NUM_LEVELS; i++) {
            next[i] = NULL;
        }
    } 
    int getKey() {
        return __value;
    }
};

class SkipList {
    
    class Node *head;

public:
    SkipList() {
        head = new Node( -1 );
    }
    int getMaxLevel();
    void addNode( int value );
    class Node * findNode( int value );
    void print();
    
};

int
SkipList::getMaxLevel() {
    int level = 0;
    while ( rand() % 2 > 0 ) {
        level++; 
        if ( level == MAX_LEVEL ) { break; }
    }
    return level;
}

void
SkipList::addNode( int value ) {
    Node *nn = new Node( value );
    int level = getMaxLevel();
    Node *n = head;

    while ( level >= 0 ) {
        if ( n->next[level] == NULL ) {
            n->next[level] = nn;
            level--; continue;
        }
        if ( n->next[level]->getKey() > value ) {
            Node *tmp = n->next[level];
            n->next[level] = nn;
            nn->next[level] = tmp;
            level--; continue;
        }
        if ( n->next[level]->getKey() < value ) {
            n = n->next[level];
            continue;
        }
    }
}

void
SkipList::print() {
    using namespace std;
    for (int i=0; i<NUM_LEVELS; i++) {
        cout << "Level " << i << "\t" ;
        Node *n = head;
        while ( n->next[i] ) {
            cout << n->next[i]->getKey() << "\t" ;
            n = n->next[i];
        }
        cout << endl;
    }
}

class Node * 
SkipList::findNode( int value ) {
    Node *n = head;
    int level = MAX_LEVEL;
    while ( level >= 0 ) {
        if ( n->next[level] == NULL ) {
            level--; continue;
        }
        if ( n->next[level]->getKey() > value ) {
            level--; continue;
        }
        if ( n->next[level]->getKey() < value ) {
            n = n->next[level];
            continue;
        }
        return n->next[level];
    }
    return NULL;
}


int main() {
    SkipList *sl = new SkipList();
    for (int i=0; i<400; i+= 4) {
        sl->addNode(i);
    }
    sl->print();
    for (int i=120; i<120+40; i+= 2) {
        Node *t = sl->findNode(i);
        cout << i << " --> " 
             << t << " --> "
             << ( t ? t->getKey() : 0 ) << endl;
    }
}
