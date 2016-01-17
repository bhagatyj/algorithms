#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"ptrQ.h"
#include"ptrStack.h"
 
typedef struct node_t_ {
    int key;
    struct node_t_ *left;
    struct node_t_ *right;
    int height;
    int level;
} node_t;
 
// Node Height
int height(node_t *n)
{
    if ( ! n ) {
        return -1;
    }
    return n->height;
}
 
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
node_t* newNode(int key)
{
    node_t *n = (node_t*) malloc(sizeof(node_t));
    n->key    = key;
    n->left   = NULL;
    n->right  = NULL;
    // new node is initially added at leaf
    n->height = 0;  
    // Initialize with level of the root
    n->level = 0;  
    return (n);
}
 
// Right Rotation of a node.
node_t *rightRotate(node_t *n)
{
    node_t *leftChild = n->left;
    node_t *leftChildsRight;
 
    // Right Rotated nodes always have a left child.
    assert(leftChild);
    leftChildsRight = leftChild->right;

    // Perform rotation
    leftChild->right = n;
    n->left = leftChildsRight;
 
    // Update heights
    // The order of updates is important. Needs to be done bottom-up.
    n->height = max(height(n->left), height(n->right))+1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right))+1;
 
    // Return new root
    return leftChild;
}
 
// Left Rotation of a node.
node_t *leftRotate(node_t *n)
{
    node_t *rightChild = n->right;
    node_t *rightChildsLeft;
    
    // Left Rotated nodes should always have a right child
    assert(rightChild);
    rightChildsLeft = rightChild->left;
 
    // Perform rotation
    rightChild->left = n;
    n->right = rightChildsLeft;;
 
    //  Update heights
    // The order of updates is important. Needs to be done bottom-up.
    n->height = max(height(n->left), height(n->right))+1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right))+1;
 
    // Return new root
    return rightChild;
}
 
// Get Balance factor of node N
int getBalance(node_t *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

int isRightHeavy(node_t *n) {
    if ( !n ) {
        return 0;
    }
    return ( getBalance(n) < -1 );
}
int isLeftHeavy(node_t *n) {
    if ( !n ) {
        return 0;
    }
    return ( getBalance(n) > 1 );
}
 
node_t* insert(node_t* node, int key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
 
    /* 2. Update height of this node */
    node->height = max(height(node->left), height(node->right)) + 1;
 
    // If this node becomes unbalanced, then there are 4 cases
    if ( isLeftHeavy(node) ) {
        if ( isRightHeavy(node->left) ) {
            // Left Right Case
            node->left =  leftRotate(node->left);
            return rightRotate(node);
        } else {
            // Right Right Case
            return rightRotate(node);
        }
    }

    if ( isRightHeavy(node) ) {
        if ( isLeftHeavy(node->right) ) {
            // Right Left Case
            node->right = rightRotate(node->right);
            return leftRotate(node);
        } else {
            // Left Left Case
            return leftRotate(node);
        }
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
void printNode(node_t *n) {
    printf("Height:%d Value:%d ", n->height, n->key);
    if (n->left) {
        printf("Left: %4d ", n->left->key);
    } else {
        printf("Left: Null ");
    }
    if (n->right) {
        printf("Right: %4d ", n->right->key);
    } else {
        printf("Right: Null ");
    }
    printf("\n");
}
 
void preOrder(node_t *root)
{
    if(root != NULL) {
        printNode(root);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void inOrder(node_t *root) {
    if(root != NULL) {
        inOrder(root->left);
        printNode(root);
        inOrder(root->right);
    }
}

void levelTraversal(node_t *root) {
    ptrQ_t *st;
    st = (ptrQ_t *)malloc(sizeof(ptrQ_t));
    if (st == NULL) {
        printf("No memory\n");
    }
    ptrQ_init(st);
    ptrQ_enq(st, root);
    while ( ! is_ptrQ_empty(st) ) {
        node_t *n = (node_t *)ptrQ_deq(st);
        printNode(n);
        if (n->left) ptrQ_enq(st, n->left);
        if (n->right) ptrQ_enq(st, n->right);
    }
}
int main()
{
  node_t *root = NULL;
  int i;
 
  for (i=0; i<10; i+=1) {
      root = insert(root, i);
  }
  for (i=1; i<100; i+=2) {
      //root = insert(root, i);
  }
 
  printf("Level order traversal of the constructed AVL tree is \n");
  //inOrder(root);
  levelTraversal(root);
  printf("Height is %d\n", height(root) );
 
  return 0;
}
