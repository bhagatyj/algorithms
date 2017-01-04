#include <iostream>
#include <random>
#include <stack>
#include <ostream>

using namespace std;

class Bst; // Forward declaration

class Node {
    int __key;
    int __value;
    Node *__left;
    Node *__right;
    friend class Bst;

public:
    Node( int k, int v) : __key(k), __value(v), __left(NULL), __right(NULL) {};
    friend ostream& operator<< ( ostream &out, Node &n);
    void inOrderRecursive();
    void preOrderRecursive();
    void postOrderRecursive();
};

class Bst {
    Node *__root;
    Node * _insertNode( Node *root, Node *n);

public:
    Bst() : __root(NULL) {};
    friend ostream& operator<< ( ostream &out, Bst &t);
    void insertNode( int k, int v);
    void insertNode( Node *newNode );
    void preOrder();
    void inOrder();
    void postOrder();
    void inOrderRecursive();
    void preOrderRecursive();
    void postOrderRecursive();
    int removeNode( int k);
};

ostream & operator<<( ostream &out, Node &n) {

    out << "[ addr:" << &n;
    out << " __key:" << n.__key; 
    out << " __value:" << n.__value;
    out << " __left:" << n.__left;
    out << " __right:" << n.__right << " ]";
    return out;
}

void
Bst::preOrder() {

    // Print out root address
    cout << "[ root:" << __root << " ]" << endl;

    // Handle base case
    if( __root == NULL ) {
        return;
    }

    // Create an empty stack and push root to it.
    stack<Node *> printStack;
    printStack.push(__root);

    // Pop all items one by one. 
    // For each popped item
    //    (1) handle it (print it)
    //    (2) push its right child
    //    (3) push its left child
    // Critical Comment:
    // =================
    // Pre-order order is Node, Left, Right.
    // But we are using a stack.
    // So, push right, left so that left comes out first.
    //
    while( not printStack.empty() ) {
        Node *n;
        n = printStack.top();
        printStack.pop();
    
        cout << *n << endl;
        if( n->__right ) {
            printStack.push( n->__right );
        }
        if( n->__left ) {
            printStack.push( n->__left );
        }
    }
}

void
Bst::inOrder() {

    // Print out root address
    cout << "[ root:" << __root << " ]" << endl;

    // Handle Base case
    if( __root == NULL ) {
        return;
    }

    stack<Node *> printStack;
    Node *current = __root;
    bool done = false;

    while( !done ) {
        if( current != NULL ) {
            // Reach the left most node of the current Node
            // and keep saving the nodes in the way to stack.
            printStack.push( current );
            current = current->__left;
        } else {
            // current is empty.
            // Backtrack and visit the Node at the top of the stack.
            // If the stack is empty, we are done.
            if( !printStack.empty() ) {
                current = printStack.top();
                printStack.pop();
                cout << *current << endl;
                // We have visited the node and its left subtree.
                // Now, it is the right subtree's turn.
                current = current->__right;
            } else {
                done = true;
            }
        }
    }
}

void
Bst::postOrder() {
    // Print out root address
    cout << "[ root:" << __root << " ]" << endl;

    // Handle Base case
    if( __root == NULL ) {
        return;
    }

    stack<Node *> tempStack;
    stack<Node *> printStack;
    Node *n;

    tempStack.push( __root );

    while( !tempStack.empty() ) {
        n = tempStack.top();
        tempStack.pop();
        printStack.push( n );

        if( n->__left ) {
            tempStack.push( n->__left );
        }
        if( n->__right ) {
            tempStack.push( n->__right );
        }
    }

    while( !printStack.empty() ) {
        n = printStack.top();
        printStack.pop();
        cout << *n << endl;
    }

}

void
Node::preOrderRecursive() {
    cout << *this << endl;
    if( __left ) {
        __left->preOrderRecursive();
    }
    if( __right ) {
        __right->preOrderRecursive();
    }
}

void
Node::inOrderRecursive() {
    if( __left ) {
        __left->inOrderRecursive();
    }
    cout << *this << endl;
    if( __right ) {
        __right->inOrderRecursive();
    }
}

void
Node::postOrderRecursive() {
    if( __left ) {
        __left->postOrderRecursive();
    }
    if( __right ) {
        __right->postOrderRecursive();
    }
    cout << *this << endl;
}

void
Bst::preOrderRecursive() {
    cout << "[ root:" << __root << " ]" << endl;
    if( __root ) {
        __root->preOrderRecursive();
    }
}

void
Bst::inOrderRecursive() {
    cout << "[ root:" << __root << " ]" << endl;
    if( __root ) {
        __root->inOrderRecursive();
    }
}
    
void
Bst::postOrderRecursive() {
    cout << "[ root:" << __root << " ]" << endl;
    if( __root ) {
        __root->postOrderRecursive();
    }
}
    
ostream & operator<<( ostream &out, Bst &t ) {
    out << "Tree with root @" << t.__root << endl;
    return out;
}

void
Bst::insertNode( int k, int v ) {

    Node *newNode = new Node(k,v);
    __root = _insertNode( __root, newNode );

}

void
Bst::insertNode( Node *newNode ) {

    __root = _insertNode( __root, newNode );

}

Node *
Bst::_insertNode( Node *root, Node *n ) {
    if ( !root ) {
        return n;
    }
    if ( root->__key > n->__key ) {
        root->__left =  _insertNode( root->__left, n );
        return root;
    } else if ( root->__key < n->__key ) {
        root->__right =  _insertNode( root->__right, n );
        return root;
    } else {
        // Duplicate node.
        root->__value = n->__value;
        delete n;
        return root;
    }
        
}
        
    
int main() {

    srand(time(NULL));
    Bst *myBst = new Bst();
    for( auto i=0; i<10; i++ ) {
        Node *n = new Node(rand()%256, 100+i);
        myBst->insertNode(n);
    }
    cout << *myBst << endl;

    cout << endl << "Pre Order Iterative" << endl;
    myBst->preOrder();
    cout << endl << "Pre Order Recursive" << endl;
    myBst->preOrderRecursive();

    cout << endl << "In Order Iterative" << endl;
    myBst->inOrder();
    cout << endl << "In Order Recursive" << endl;
    myBst->inOrderRecursive();

    cout << endl << "Post Order Iterative" << endl;
    myBst->postOrder();
    cout << endl << "Post Order Recursive" << endl;
    myBst->postOrderRecursive();

}
