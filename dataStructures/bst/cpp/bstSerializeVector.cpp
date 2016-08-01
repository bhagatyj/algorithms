#include <iostream>
#include <list>

using namespace std;

struct Node {
    int key;
    Node *left;
    Node *right;
    Node( int k ) : key( k ), left( NULL ), right( NULL ) {}
};

#define EMPTY -1

void
serialize( Node *root, list< int >& data ) {
    if( root == NULL ) {
        data.push_back( EMPTY );
        return;
    }
    data.push_back( root->key );
    serialize( root->left, data );
    serialize( root->right, data );
}

Node *
deserialize( list< int >& data ) {
    if( data.empty() ) return NULL;
    int key = data.front();
    data.pop_front();
    if( key == EMPTY ) return NULL;
    Node *curr = new Node( key );
    curr->left = deserialize( data );
    curr->right = deserialize( data );
    return curr;
}

void
printList( list< int > data, string message ) {
    cout << message;
    for( list< int >::iterator it=data.begin(); it!=data.end(); ++it ) {
        cout << *it << " ";
    }
    cout << endl;
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

    list< int > data;
    serialize( root, data );
    printList( data, "Serialized:  " );

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


