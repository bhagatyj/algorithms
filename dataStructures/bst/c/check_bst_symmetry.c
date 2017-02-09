#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

bool 
isSymmetricTrees( struct TreeNode *left, struct TreeNode *right ) {
	if ( !left && !right ) { return true; }
	if ( !left && right ) { return false; }
	if ( left && !right ) { return false; }
	if ( left->val != right->val ) { return false; }
	
	return ( isSymmetricTrees( left->left, right->right ) &&
	         isSymmetricTrees( left->right, right->left ) );
}


bool 
isSymmetric(struct TreeNode* root) {
	if ( !root ) {
    	return true;
	}
	return ( isSymmetricTrees( root->left, root->right ) );

}

struct TreeNode * getNode(int val) {
	struct TreeNode *t;
	t = (struct TreeNode *) malloc(sizeof(struct TreeNode));
	memset(t, 0, sizeof(struct TreeNode));
	t->val = val;
	return t;
}

int main() {

	struct TreeNode *root;
	root = getNode(1);
	root->left = getNode(2);
	printf("%d\n", isSymmetric(root));
	root->right = getNode(2);
	printf("%d\n", isSymmetric(root));
	root->left->left = getNode(3);
	root->right->left = getNode(3);
	printf("%d\n", isSymmetric(root));
	root->right->left = NULL;
	root->right->right = getNode(3);
	printf("%d\n", isSymmetric(root));
}



