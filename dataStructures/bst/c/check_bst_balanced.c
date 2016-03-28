#include <stdio.h>
#include <stdbool.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

typedef struct TreeNode node;

#define BAD_HEIGHT -100

int max( int left, int right ) {
	if ( left > right ) { return left; } 
	return right;
}

int getHeightIfBalanced(struct TreeNode* root) {
	int leftHeight;
	int rightHeight;

	if ( root == NULL ) {
		return -1;
	}
	
	leftHeight = getHeightIfBalanced(root->left);
	rightHeight = getHeightIfBalanced(root->right);

	if ( (leftHeight == BAD_HEIGHT) ||
		 (rightHeight == BAD_HEIGHT) ) {
		return BAD_HEIGHT;
	}

	if (( leftHeight == rightHeight + 1 )  ||
	    ( leftHeight == rightHeight     )  ||
	    ( leftHeight == rightHeight -1  )  ) {
		
		return ( max(leftHeight, rightHeight) + 1);
	} else {
		return BAD_HEIGHT;
	}
    
}

bool isBalanced(struct TreeNode* root) {
	if ( getHeightIfBalanced(root) == BAD_HEIGHT) {
		return false;
	}
	return true;
    
}
int main() {

}
