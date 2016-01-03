#include <iostream>
#include <queue>
//
// Level Order Traversal
// 
// For the below example,
//
//                        10
//           5                         15
//    2            9              14            
// 1      4                   12
// 
// the output should be:
// 10, 5, 15, 2, 9, 14, 1, 4, 12.
//
// In a binary tree, to perform a level order traversal, we need to be
// able to remember more than one node. 
// 
//  To get to node 15 after visiting 5, we push all children nodes of 10 to a queue
// when visiting 10 and pop them one after another and visit them.
//
// So the strategy used is storing all the elements in level "L+1" when walking
// visiting level "L".
// Follow this strategy across all levels. 
//
// There are two stages to the level tree traversal algorithm:
//  (1) Discovering the nodes
//  (2) Visiting the nodes
// When visiting nodes at level "L", discover their children and push the children's
// addresses to the queue.
// By the time all nodes of level "L" are complete, all nodes at level "L+1" have
// been discovered too. Now we can start visiting the nodes at level "L+1".
// 
// To store nodes at level L+1 and retreieve them in order later, we need some FIFO
// mechanism like c++ queue.
//
// Finding the height of the tree.
// The height of the tree is the max length between tree and leaf nodes. One way to
// get the height is to perform a treaversal of the nodes. At any time that you meet
// a leaf node, compare the height of the node to the max height found so far and then
// update the max if necessary.
//
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
        void preOrderPrint( Node *n);
        void inOrderPrint( Node *n);
        void postOrderPrint( Node *n);
        void levelOrderPrint() ;
        void printTree();
        void printRoot();
        int height();
    private:
        Node *root;
        Node *insert( Node *n, int k, int v);
        int findHeight( Node *n, int &maxHeight );
};
        
int 
Tree::height() {
    int maxHeight = 0;
    findHeight(root, maxHeight);
    return maxHeight;
}

int 
Tree::findHeight( Node *n, int &maxHeight ) {
    int leftHeight=0, rightHeight=0, currentHeight;

    if ( ( ! n->left ) && ( ! n->right ) ) {
       return 0;
    }
    if ( n->left ) {
        leftHeight = findHeight( n->left, maxHeight ) + 1;
    }
    if ( n->right ) {
        rightHeight = findHeight( n->right, maxHeight ) + 1;
    }
    currentHeight = max(leftHeight, rightHeight);
    maxHeight = max(currentHeight, maxHeight);
    cout << "At node " << n->key << " height is " << currentHeight << endl;
    return currentHeight;

}

void
Tree::printRoot() {
    cout << "Printing the root element" << endl;
    root->printData();
    cout << endl;
}

Tree::Tree( Node *n) {
    root = n;
}

Tree::Tree( void ) {
    root = NULL;
}

void Tree::preOrderPrint( Node *n) {
    n->printData();
    if (n->left) {
        preOrderPrint(n->left);
    }
    if (n->right) {
        preOrderPrint(n->right);
    }
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

void Tree::postOrderPrint( Node *n) {
    if (n->left) {
        preOrderPrint(n->left);
    }
    if (n->right) {
        preOrderPrint(n->right);
    }
    n->printData();
}

void
Tree::printTree( void ) {

    cout << "Printing the tree in preorder" << endl;
    preOrderPrint(root);
    cout << endl;

    cout << "Printing the tree in inorder" << endl;
    inOrderPrint(root);
    cout << endl;

    cout << "Printing the tree in postorder" << endl;
    postOrderPrint(root);
    cout << endl;

    cout << "Level Order Traversal" << endl;
    levelOrderPrint();
    cout << endl;
}
        
Node * Tree::insert( Node *n, int k, int v) {
    if ( ! n ) {
        n = new Node(k, v);
    } else if ( k < n->key ) {
        n->left = insert( n->left, k, v );
    } else if ( k > n->key ) {
        n->right = insert( n->right, k, v );
    } else {
        // Found a node with the same key.
        // Replace data.
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

void Tree::levelOrderPrint() {
    queue<Node *> printQ;
    Node * n;

    if (root == NULL) { return; }

    printQ.push(root);
    while ( !printQ.empty() ) {
        Node *n = printQ.front();
        n->printData();
        if (n->left) { 
            printQ.push(n->left);
        }
        if (n->right) {
            printQ.push(n->right);
        }
        printQ.pop();
    }
}

// As this is a simple bst and not a balanced bst,
// the order in which elements are added determines
// the structure of the tree.
// 
int main(int argc, char **argv) {
    int i, max;
    Tree *t = new Tree( );
    max = 5;
    for ( i=0; i<= max; i++) {
        t->addNode(i, i*i);
    }
    for ( i=-1*max; i< 0; i++) {
        t->addNode(i, i*i);
    }
    t->printTree();
    cout << "Height of the tree is " << t->height() << endl;
}
