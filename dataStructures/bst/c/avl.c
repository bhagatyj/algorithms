#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<limits.h>
#include<string.h>
#include"ptrQ.h"
#include"ptrStack.h"
 
#include <stdbool.h>
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
    // I become my Left child-s right child
    // My left child-s right child becomes my left.
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
    // I become my Right child-s left child
    // My right child-s left child becomes my right
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
    /* 1.  Perform the normal Bst rotation */
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
void postOrder(node_t *root) {
    if(root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printNode(root);
    }
}

void preOrder_nonRecursive(node_t *root) {

    ptrStack_t *pS = get_new_ptrStack();

    if (pS == NULL) { return; }
    if ( !root ) { return; }

    while (1) {
        while (root) {
            // Process current node
            printNode(root);
            ptrStack_push(pS, root);
            root = root->left;
        }
        if ( is_ptrStack_empty(pS) ) {
            break;
        }
        root = ptrStack_pop(pS);
        root = root->right;
    }
    free(pS);
}

void inOrder_nonRecursive(node_t *root) {

    ptrStack_t *pS = get_new_ptrStack();

    if (pS == NULL) { return; }
    if ( !root ) { return; }

    while (1) {
        while (root) {
            // Process current node
            ptrStack_push(pS, root);
            root = root->left;
        }
        if ( is_ptrStack_empty(pS) ) {
            break;
        }
        root = ptrStack_pop(pS);
        printNode(root);
        root = root->right;
    }
    free(pS);
}

/*
 * Post order is more tricky than pre and in order 
 * traversal.
 */
void postOrder_nonRecursive(node_t *root) {

    ptrStack_t *pS1 = get_new_ptrStack();
    ptrStack_t *pS2 = get_new_ptrStack();

    if (pS1 == NULL) { return; }
    if (pS2 == NULL) { return; }
    if ( !root ) { return; }

    ptrStack_push(pS1, root);
    while (! is_ptrStack_empty(pS1) ) {

        node_t *n = (node_t *)ptrStack_pop(pS1);
        ptrStack_push(pS2, n);

        if (n->left) {
            ptrStack_push(pS1, n->left);
        }
        if (n->right) {
            ptrStack_push(pS1, n->right);
        }
    }
    while ( ! is_ptrStack_empty(pS2) ) {
        node_t *n = (node_t *) ptrStack_pop(pS2);
        printNode(n);
    }
    free(pS1);
    free(pS2);
}

void levelTraversal(node_t *root) {
    ptrQ_t *st = get_new_ptrQ();
    if (st == NULL) { return; }

    ptrQ_enq(st, root);
    while ( ! is_ptrQ_empty(st) ) {
        node_t *n = (node_t *)ptrQ_deq(st);
        printNode(n);
        if (n->left) ptrQ_enq(st, n->left);
        if (n->right) ptrQ_enq(st, n->right);
    }
    free(st);

}

// Caveats:
// In a Bst, all the descendants of a node should obey the rule
// the value of the descendant should be less than root if it is on the left-side.
// the value of the descendant should be more than root if it is on the left-side.
// Hence, recursive checking is needed.
//
// Special care needs to be taken for the first occurence of INT_MIN and INT_MAX.
// For example, the following trees are valid:
//
// [-2147483648]
// [-2147483648,null,2147483647]
// [2147483647]
// [2147483647, -2147483648,null]
//
bool isValidBstNode(node_t *root, int min, int max, bool leftMaxAllowed, bool rightMaxAllowed) {

	if (!root) {
		return true;
	}
	if (leftMaxAllowed) {
		if ( root->key < min ) { return false; }
	} else {
		if ( root->key <= min ) { return false; }
	}
	if (rightMaxAllowed) {
		if ( root->key > max ) { return false; }
	} else {
		if ( root->key >= max ) { return false; }
	}

	bool leftValid = isValidBstNode( root->left, min, root->key, leftMaxAllowed, false );
	bool rightValid = isValidBstNode( root->right, root->key, max, false, rightMaxAllowed );
	printf("key:%d min:%d max:%d allowed:%d%d left:%d %p right:%d %p\n",
             root->key, min, max, leftMaxAllowed, rightMaxAllowed, 
		     leftValid, root->left, rightValid, root->right);
	return (leftValid & rightValid);
} 

bool isValidBst(node_t * root) {
	
	return isValidBstNode( root, INT_MIN, INT_MAX, true, true);
    
}

void isValidBstTester() {
  node_t *root;

  root = (node_t *) malloc(sizeof(node_t));
  memset(root, 0, sizeof(node_t));
  root->right = (node_t *) malloc(sizeof(node_t));
  memset(root->right, 0, sizeof(node_t));
  // [ 1, N, 1 ] -> invalid
  root->key = 1;
  root->right->key = 1;
  printf("Validity %d \n",isValidBst(root));

  // [ -2147483648, N, 1 ] -> valid
  root->key = -2147483648;
  printf("Validity %d \n",isValidBst(root));

  // [ -2147483648, N, 2147483647 ] -> valid
  root->right->key = 2147483647;
  printf("Validity %d \n",isValidBst(root));

}
	
int main()
{
  node_t *root = NULL;
  int i;
 
  for (i=0; i<10; i+=1) {
      root = insert(root, i);
  }
 
  printf("Level order traversal of the constructed AVL tree is \n");
  levelTraversal(root);
  printf("Post order traversal of the constructed AVL tree is \n");
  postOrder(root);
  printf("Post order traversal of the constructed AVL tree is \n");
  postOrder_nonRecursive(root);
  printf("Height is %d\n", height(root) );
  printf("Validity %d \n",isValidBst(root));

  isValidBstTester();

  return 0;

}
