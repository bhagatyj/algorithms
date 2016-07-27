/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 *
 * Description:
 * First let’s review some statement for tree in graph theory:
 *
 * 1. A tree is an undirected graph in which any two vertices are connected by exactly one path.
 * 2. Any connected graph who has n nodes with n-1 edges is a tree.
 * 3. The degree of a vertex of a graph is the number of edges incident to the vertex.
 * 4. A leaf is a vertex of degree 1. An internal vertex is a vertex of degree at least 2.
 * 5. A path graph is a tree with two or more vertices that is not branched at all.
 * 6. A tree is called a rooted tree if one vertex has been designated the root.
 * 7. The height of a rooted tree is the number of edges on the longest downward path between root and a leaf.
 * OK. Let’s stop here and look at our problem.
 *
 * Our problem want us to find the minimum height trees and return their root labels. First we can think about a simple case — a path graph.
 *
 * For a path graph of n nodes, find the minimum height trees is trivial. Just designate the middle point(s) as roots.
 *
 * Despite its triviality, let design a algorithm to find them.
 *
 * Suppose we don’t know n, nor do we have random access of the nodes. We have to traversal. It is very easy to get the idea of two pointers. One from each end and move at the same speed. When they meet or they are one step away, (depends on the parity of n), we have the roots we want.
 *
 * This gives us a lot of useful ideas to crack our real problem.
 *
 * For a tree we can do some thing similar. We start from every end, by end we mean vertex of degree 1 (aka leaves). We let the pointers move the same speed. When two pointers meet, we keep only one of them, until the last two pointers meet or one step away we then find the roots.
 *
 * It is easy to see that the last two pointers are from the two ends of the longest path in the graph.
 *
 * The actual implementation is similar to the BFS topological sort. Remove the leaves, update the degrees of inner vertexes. Then remove the new leaves. Doing so level by level until there are 2 or 1 nodes left. What’s left is our answer!
 *
 * The time complexity and space complexity are both O(n).
 *
 * Source: http://algobox.org/minimum-height-trees/
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node_t_ {
    int degree;
    bool candidate;
} node_t;

int* findMinHeightTrees(int n, int** edges, int edgesRowSize, int edgesColSize, int* returnSize) {

    int i, j, *ans, numCands;
    node_t *cands;
    int iter=0;

    cands = (node_t *) malloc( n *sizeof(node_t) );
    memset(cands, 0, n *sizeof(node_t) );
    ans = (int *) malloc(2 *sizeof(int));
    for (i=0; i<n; i++) {
        cands[i].candidate = true;
    }
    if (n == 1) {
        *ans = 0;
        *returnSize=1;
        return ans;
    }
    if (n == 2) {
        *ans = 0;
        *(ans+1) = 1;
        *returnSize = 2;
        return ans;
    }

    do {
        for (i=0; i<edgesRowSize; i++) {
            if ( cands[edges[i][0]].candidate  &&
                 cands[edges[i][1]].candidate )  {
                    cands[edges[i][0]].degree++;
                    cands[edges[i][1]].degree++;
            }
        }
        numCands = 0;
        for (i=0; i<n; i++) {
            if ( cands[i].degree <= 1 ) {
                cands[i].candidate = false;
            } else {
                numCands++;
            }
            cands[i].degree = 0;
        }
    } while (numCands > 2);

    *returnSize = numCands;
    j=0;
    for (i=0; i<n; i++) {
        if (cands[i].candidate == true) {
            *(ans+j) = i;
            j++;
        }
    }
    //*(returnSize) = numCands;
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
