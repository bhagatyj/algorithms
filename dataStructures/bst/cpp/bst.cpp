#include <iostream>
#include <queue>
//
// ## Level Order Traversal
// ## Height of tree
// ## Deletion of node in bst
// ## Check if a binart tree is BST - Method 1
// check if each node falls within expected range
// ## Check if a binart tree is BST - Method 2 
// (in order traversal - check sorted order)
// ##
// 
//
using namespace std;

class Node {
    public:
        int key;
        int value;
        int height;
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
    cout << "Key:" << key << " Val:" << value ;
    cout << "\t\tLeft : " << ((left) ? (left->key) : NULL) ;
    cout << "\t\tRight : " << ((right) ? (right->key) : NULL);
    cout << endl;
}

class Tree {
    protected:
        Node *root;
        Node *insert( Node *n, int k, int v);
        int findHeight( Node *n);
        Node *_removeNode( Node *root, int key);
        Node * findMin(Node *n);
    public:
        void addNode( int k, int v);
        void removeNode( int k);
        Tree ( Node *n);
        Tree ( void );
        void preOrderPrint( Node *n);
        void inOrderPrint( Node *n);
        void postOrderPrint( Node *n);
        void levelOrderPrint() ;
        void printTree();
        void printRoot();
        int height();
};

/*
class AvlTree : Tree {
    protected:
        Node *insert( Node *n, int k, int v);
        Node *_removeNode( Node *root, int key);
    public:
        void addNode( int k, int v);
        void removeNode( int k);
};
*/

        
int
Tree::height() {
    return findHeight( root );
}

// ## Height of tree
//
// Height of a node is defined as the number of edges from a node to the 
// farthest leaf descendant. If a node has no children, then, it's height is 0.
// Thus the number of levels is a tree is equal to its height.
// By extension, if the root is NULL, the height is -1.
// The height of a node is the max of the heights of its left, right sub-trees.
// 
// Height of the tree is -1 if the root node is NULL.
// For a root node with no children, it is 0.
// and so on..
int 
Tree::findHeight( Node *n) {
    int leftHeight, rightHeight, currHeight;

    if ( !n ) {
       return -1;
    }
    leftHeight = findHeight( n->left );
    rightHeight = findHeight( n->right );
    currHeight = max(leftHeight, rightHeight) + 1;

    return currHeight;
}

// Deletion::
// There are three cases for bst node deletion.
//
// Case 1: Deleting a node that has no children.
//
// Deletion of a leaf node is very simple. Just remove the link
// from parent and free the memory.
//
// Case 2: Deleting a node with single child 
//
// Link the only child to parent and we are done.
//
// Case 3: Deleting a node with two children
//
// If there are two children, it is tricky.
// Find the smallest node in the right sub-tree ( or the 
// largest node in the left sub-tree).
// Copy over the value of the found node to the "to-be-deleted" node.
// Now, the problem definition just changed to "delete the found node".
// Since the "found node" is lower than the earlier node, it is more
// likely, that it has less children and becomes either Case-1 or Case-2.
// If it has two children, repeat above steps again and again until it 
// becomes Case-1 or Case-2.
// 
// Property used:
// In a subtree, the minimum value node will not have a left child.
// In a subtree, the maximum value node will not have a right child.
// 
void
Tree::removeNode(int key) {
    root = _removeNode(root, key);
}

Node * 
Tree::_removeNode(Node *n, int key) {

    if ( ! n ) {
        return NULL;
    }
    if ( key < n->key ) {
        n->left = _removeNode( n->left, key );
        return n;
    }
    if ( key > n->key ) {
        n->right = _removeNode( n->right, key );
        return n;
    }
    if ( n->key == key ) {

        // Case 1: No Child
        if ( (!n->left) && (!n->right) ) {
            delete n;
            return NULL;
        }
        // Case 2a: No left child`
        if (!n->left) {
            Node *child;
            child = n->right;
            delete n;
            return child;
        }
        // Case 2b: No right child
        if (!n->right) {
            Node *child;
            child = n->left;
            delete n;
            return child;
        }
        // Case 3: Has both children
        Node *min = findMin(n->right);
        n->value = min->value;
        n->key = min->key;
        n->right = _removeNode(n->right, min->value);
        return n;
    }
    return n;
}

Node *
Tree::findMin(Node *n) {
    Node *leftMin, *rightMin, *tmp;

    if ( !n ) {
        return NULL;
    }

    leftMin = findMin( n->left );
    rightMin = findMin( n->right );

    if ( ( !leftMin ) && ( !rightMin ) ) {
        return n;
    }
    tmp = n;
    if ( leftMin ) {
        if ( leftMin->key < n->key ) {
            tmp = leftMin;
        }
    }
    if ( rightMin ) {
        if ( rightMin->key < tmp->key ) {
            return rightMin;
        }
    }
    return tmp;
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

// ## Level Order Traversal
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
    cout << "Height of the tree is " << t->height() << endl;
    cout << "Removing keys 2 and -3" << endl;
    t->removeNode(2);
    t->removeNode(-3);
    cout << "Height of the tree is " << t->height() << endl;
    cout << "Removing key 0" << endl;
    t->removeNode(0);
    cout << "Height of the tree is " << t->height() << endl;
    t->removeNode(-5);
    cout << "Height of the tree is " << t->height() << endl;
    t->printTree();
}
