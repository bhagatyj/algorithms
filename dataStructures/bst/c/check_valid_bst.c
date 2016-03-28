#include <stdbool.h>
#include <limits.h>

bool isValidBSTNode(struct TreeNode *root, int min, int max, bool leftMaxAllowed, bool rightMaxAllowed) {

    if (!root) {
        return true;
    }
    if ( leftMaxAllowed ) {
        if ( root->val < min ) { return false; }
    } else {
        if ( root->val <= min ) { return false; }
    }
    if ( rightMaxAllowed ) {
        if ( root->val > max ) { return false; }
    } else {
        if ( root->val >= max ) { return false; }
    }
    bool leftValid = isValidBSTNode( root->left, min, root->val, leftMaxAllowed, 0 );
    bool rightValid = isValidBSTNode( root->right, root->val, max, 0, rightMaxAllowed );
    return (leftValid & rightValid);
}

bool isValidBST(struct TreeNode * root) {
    
    return isValidBSTNode( root, INT_MIN, INT_MAX, 1, 1);

}

