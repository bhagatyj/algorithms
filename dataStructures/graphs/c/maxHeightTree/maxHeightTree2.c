/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct bucket_t_ {
    int 			degree;
	struct node_t_ *head;
} bucket_t;

typedef struct node_t_ {
    int				key;
	struct node_t_ *next;
} node_t;

typedef struct retvalue_t_ {
	int		degree;
	int		key;
} retvalue_t;

bucket_t *heap = NULL;
node_t *curr_leaves;
node_t *next_leaves;

void add_to_bucket(int key, node_t *n) {
	bucket_t *b = &heap[key];
	n->next = b->head;
    b->head = n;
	b->degree++;
}

/* 
 * if n_key is -1, remove the first node. This is called in cases of leaves.	
 */
void
remove_from_bucket(int b_key, int n_key, retvalue_t *ret) {
	bucket_t *b = &heap[b_key];
	node_t *n = b->head;

	if (n == NULL) {
		// already removed.
		ret->key = -1;
		ret->degree = 0;
		return;
	}
	if ((n->key == n_key) || (n_key == -1) ) {
		b->head = NULL;
		b->degree--;
		ret->degree = b->degree;
		ret->key = n->key;
		free(n);
		return;
	}
	while (n->next) {
		if (n->next->key == n_key) {
			node_t *tmp = n->next;
			n->next = n->next->next;
			b->degree--;
			ret->degree = b->degree;
			ret->key = tmp->key;
			free(tmp);
			return;
		}
	}

	assert(0); // could not find the key.
		
}

void add_to_leaf_list(node_t *leaves, int key) {
	node_t *leaf = (node_t *)malloc(sizeof(node_t));
	leaf->key = key;
	leaf->next = leaves->next;
	leaves->next = leaf;
}

int* findMinHeightTrees(int n, int** edges, int edgesRowSize, int edgesColSize, int* returnSize) {

    int i, j, *ans;
    int num_leaves=0, next_num_leaves;

	heap = (bucket_t *)malloc(n*sizeof(bucket_t));
	memset(heap, 0, n*sizeof(bucket_t));
	ans = (int *) malloc(sizeof(int)*2);
	*ans = 0; returnSize = 0;

	for (i=0; i<edgesRowSize; i++) {
		node_t *x = (node_t *)malloc(sizeof(node_t));
		node_t *y = (node_t *)malloc(sizeof(node_t));
		int key1 = edges[edgesRowSize][0];
		int key2 = edges[edgesRowSize][1];
		memset(x, 0, sizeof(node_t));
		memset(y, 0, sizeof(node_t));
		x->key = key1;
		y->key = key2;
		add_to_bucket(key1, y);
		add_to_bucket(key2, x);
	}

	curr_leaves = (node_t *)malloc(sizeof(node_t));
	next_leaves = (node_t *)malloc(sizeof(node_t));
	memset(curr_leaves, 0, sizeof(node_t));
	memset(next_leaves, 0, sizeof(node_t));

	for (i=0; i<n; i++) {
		if ( heap[i].degree == 1) {
			add_to_leaf_list(curr_leaves, i);
			num_leaves++;
		}
	}

	while ( num_leaves > 2) {
		node_t *leaf = curr_leaves->next;
		node_t *tmp;
		retvalue_t ret;
		remove_from_bucket(leaf->key, -1, &ret);
		if ( ret.key != -1) {
			remove_from_bucket(ret.key, leaf->key, &ret);
			if (ret.degree == 1) {
				add_to_leaf_list(next_leaves, ret.key);
				next_num_leaves++;
			}
		}
		free(leaf);
		num_leaves = next_num_leaves;
		tmp = curr_leaves;
		curr_leaves = next_leaves;
		next_leaves = tmp;
		memset(next_leaves, 0, sizeof(node_t));
	}
			
	node_t *leaf = curr_leaves->next;
	*ans = leaf->key;
	returnSize = 0;
	if ( leaf->next ) {
		*(ans+1) = leaf->next->key;
		returnSize++;
	}
    return ans;
}

int main() {
	int **edges; // { { 1, 0 }, { 1, 2 }, {1, 3} };
	int ansSize, *ans, i;

	edges = (int **) malloc ( 3 * sizeof(int *) );
	for (i=0; i<3; i++) {
		edges[i] = (int *) malloc( 2 * sizeof(int) );
	}
	edges[0][0] = 1;
	edges[0][1] = 0;
	edges[1][0] = 1;
	edges[1][1] = 2;
	edges[2][0] = 1;
	edges[2][1] = 3;
	ans = findMinHeightTrees( 4, edges, 3, 2, &ansSize);
	for (i=0; i<ansSize; i++) {
		printf("Ans %d\n", *(ans+i));
	}
	for (i=0; i<3; i++) {
		free(edges[i]);
	}
	free(edges); free(ans);

	edges = (int **) malloc ( 5 * sizeof(int *) );
	for (i=0; i<5; i++) {
		edges[i] = (int *) malloc( 2 * sizeof(int) );
	}
	edges[0][0] = 0;
	edges[0][1] = 3;
	edges[1][0] = 1;
	edges[1][1] = 3;
	edges[2][0] = 2;
	edges[2][1] = 3;
	edges[3][0] = 4;
	edges[3][1] = 3;
	edges[4][0] = 5;
	edges[4][1] = 4;
	ans = findMinHeightTrees( 6, edges, 5, 2, &ansSize);
	for (i=0; i<ansSize; i++) {
		printf("Ans %d\n", *(ans+i));
	}
	for (i=0; i<5; i++) {
		free(edges[i]);
	}
	free(edges); free(ans);

	edges = (int **) malloc ( 5 * sizeof(int *) );
	assert(edges);
	for (i=0; i<5; i++) {
		edges[i] = (int *) malloc( 2 * sizeof(int) );
		assert(edges[i]);
	}
	edges[0][0] = 3;
	edges[0][1] = 0;
	edges[1][0] = 3;
	edges[1][1] = 1;
	edges[2][0] = 3;
	edges[2][1] = 2;
	edges[3][0] = 3;
	edges[3][1] = 4;
	edges[4][0] = 5;
	edges[4][1] = 4;
	ans = findMinHeightTrees( 6, edges, 5, 2, &ansSize);
	for (i=0; i<ansSize; i++) {
		printf("Ans %d\n", *(ans+i));
	}
	for (i=0; i<5; i++) {
		free(edges[i]);
	}
	free(edges); free(ans);
}
