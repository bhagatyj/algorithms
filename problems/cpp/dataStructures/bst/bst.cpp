#include <iostream>
using namespace std;

class Node {
    public:
        int key;
        int value;
        Node *left;
        Node *right;

        Node( int k, int v );
        void printData( void );
};

Node::Node( int k, int v) {
    value = v;
    key = k;
    right = left = NULL;
}

void 
Node::printData(void) {
    cout << "Key:" << key << " Val:" << value << endl;
}

class Tree {
    public:
        void addNode( int k, int v);
        Tree ( Node *n);
        Tree ( void );
        void inOrderPrint( Node *n);
        void printTree() ;
    private:
        Node *root;
        Node *insert( Node *n, int k, int v);
};
        
Tree::Tree( Node *n) {
    root = n;
}

Tree::Tree( void ) {
    root = NULL;
}

void Tree::inOrderPrint( Node *n) {
    if (n->left) {
        inOrderPrint(n->left);
    }
    n->printData();
    if (n->right) {
        inOrderPrint(n->right);
    }
}

void
Tree::printTree( void ) {
    inOrderPrint(root);
}
        
Node * Tree::insert( Node *n, int k, int v) {
    if ( ! n ) {
        n = new Node(k, v);
    } else if ( k < n->key ) {
        n->left = insert( n->left, k, v );
    } else if ( k > n->key ) {
        n->right = insert( n->right, k, v );
    } else {
        // replace data.
        n->value = v;
    }
    return n;
}

void  Tree::addNode( int k, int v) {
    if ( ! root ) {
        root = new Node(k, v);
        return;
    }
    insert( root, k, v );
}

int main(int argc, char **argv) {
    Tree *t = new Tree( );
    t->addNode(1, 1);
    t->addNode(2, 4);
    t->addNode(3, 8);
    t->addNode(3, 9);
    t->addNode(4, 16);
    t->printTree();
}
