#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct Node {
    int key;
    Node *left;
    Node *right;
    Node( int k ) : key( k ), left( NULL ), right( NULL ) {}
};

#define EMPTY string("NULL")
#define DELIMITER ':'

void
serialize( Node *root, string &data ) {
    if( root == NULL ) {
        data += EMPTY; 
        data.append( 1, DELIMITER );
        return;
    }
    data += to_string( root->key );
    data.append( 1, DELIMITER );
    serialize( root->left, data );
    serialize( root->right, data );
}

void
splitToTokens( string data, char delim, list<string> &tokens ) {

    stringstream ss(data);
    string item;

    while( getline( ss, item, delim) ) {
        tokens.push_back(item);
    }
}

Node *
deserialize( list<string> &tokens ) {

    string data = tokens.front();
    tokens.pop_front();

    if ( data.find("NULL") != -1 ) {
        return NULL;
    } else {
        int key = stoi(data);
        Node *curr = new Node( key );
        curr->left = deserialize( tokens );
        curr->right = deserialize( tokens );
        return curr;
    }

}

Node *
deserialize( string &data ) {
    
    list<string> tokens;
    
    splitToTokens( data, DELIMITER, tokens);

    if( tokens.empty() ) return NULL;

    return deserialize( tokens );
}


void
printTree( Node *root ) {
    if( root == NULL ) return;
    cout << root->key << " ";
    printTree( root->left );
    printTree( root->right );
}

void
testCase1( void ) {
    cout << "\n*** " << __FUNCTION__ << " ***" << endl;
    Node *root = new Node( 1 );
    root->left = new Node( 2 );
    root->right = new Node( 3 );
    root->right->right = new Node( 7 );
    root->left->left = new Node( 4 );
    root->left->left->left = new Node( 8 );
    root->left->left->right = new Node( 9 );

    cout << "Tree before: ";
    printTree( root );
    cout << endl;

    string data;
    serialize( root, data );
    cout << "Serialized: " << data << endl ;

    Node *reconverted = deserialize( data );

    cout << "Tree after:  ";
    printTree( reconverted );
    cout << endl;
}

int
main( void ) {
    testCase1();

    return( 0 );
}


