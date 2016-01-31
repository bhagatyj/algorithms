#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define MAX_DIST 16
#define INFINITY (MAX_DIST*MAX_DIST)
#define false 0
#define true 1

typedef struct graph_t_ {
	int numVertices;
	int numEdges;
	int *distMatrix;
} graph_t;

typedef struct dij_kit_t {
	int numVertices;
	int *prevNode;
	int *minFound;
	int *cost;
} dij_kit;

graph_t *
create_graph( int size ) {

	graph_t *g = (graph_t *) malloc(sizeof(graph_t));
	memset(g, 0, sizeof(graph_t));
	g->numVertices = size;
	g->numEdges = 0;
	g->distMatrix = (int *) malloc(sizeof(int) * size * size);
	memset(g->distMatrix, 0, sizeof(int)*size*size);
	return g;
	
}

dij_kit *
create_dij_kit( int size ) {
	int i;

	dij_kit *dk = (dij_kit *) malloc(sizeof(dij_kit));
	dk->prevNode = (int *) malloc(sizeof(int)*size);
	dk->minFound = (int *) malloc(sizeof(int)*size);
	dk->cost = (int *) malloc(sizeof(int)*size);
	
	dk->numVertices = size;
	for (i=0; i<size; i++) {
		dk->prevNode[i] = -1;
		dk->minFound[i] = false;
		dk->cost[i] = INFINITY;
	}
	return dk;
}

void
print_dij_kit(dij_kit *dk) {
	int i;
	printf("\nDijkstra's Solution\n");
	for (i=0; i<dk->numVertices; i++) {
		printf("%d: cost : %8d prevNode: %8d\n", 
				i, dk->cost[i], dk->prevNode[i]);
	}
}

void
init_graph( graph_t * g) {
	int i, j, idx;

	srand(2);
	for (i=0; i<g->numVertices; i++) {
		for (j=0; j<g->numVertices; j++) {
			// To make it sparse, 
			// choose a random number from bigger range and 
			// use 0 if the random number is > MAX_DIST.
			int x = (rand() % (2*MAX_DIST)   ) + 1;
			idx = i*g->numVertices+j;
			if ( x > MAX_DIST ) {
				g->distMatrix[idx] = INFINITY;
			} else {
				g->distMatrix[idx] = x;
				g->numEdges++;
			}
			if ( i==j ) { g->distMatrix[idx] = 0; continue; }
		}
	}
}

void
print_graph( graph_t *g) {
	int i, j, idx;
	
	printf("\nGraph Input \n");
	printf("Number of Vertices: %d\n", g->numVertices);
	printf("Number of Edges: %d\n", g->numEdges);
	printf("%8s | ", "");
	for (i=0; i<g->numVertices; i++) {
		printf("%8d", i);
	}
	printf("\n");
	for (i=0; i<80; i++) { printf("-"); } printf("\n");
	for (i=0; i<g->numVertices; i++) {
		printf("%8d | ", i);
		for (j=0; j<g->numVertices; j++) {
			idx = i*g->numVertices+j;
			printf("%8d", g->distMatrix[idx]);
		}
		printf("\n");
	}
	printf("\n");
}

dij_kit * 
solve_dk( graph_t *g, int source) {
	int minNode, i;
	int minCost;

	dij_kit *dk = create_dij_kit(g->numVertices);

	// Start with the source.
	// Set its cost as 0.
	// Set itself as the prev-node
	dk->cost[source] = 0;
	dk->prevNode[source] = source;
	minNode = source;

	while ( minNode != -1 ) {
		// First mark this as done.
		dk->minFound[minNode] = true;
		printf("MinNode is %d\n", minNode);
		// Update distance of rest of the nodes.
		for (i=0; i< dk->numVertices; i++) {
			if ( i == minNode ) { continue; }
			int idx = minNode*g->numVertices + i;
			if ( ( dk->minFound[i] ) || ( i == minNode ) ) {
				continue;
			}
			int cost_via_minNode = dk->cost[minNode] + g->distMatrix[idx];
			if ( dk->cost[i] > cost_via_minNode ) {
				dk->cost[i] = cost_via_minNode;
				dk->prevNode[i] = minNode;		
			}
		}
		// Find next minNode.
		minCost = INFINITY; minNode = -1;
		for (i=0; i< dk->numVertices; i++) {
			if ( dk->minFound[i] ) { continue; }
			if ( dk->cost[i] < minCost ) { 
				minCost = dk->cost[i];
				minNode = i;
			}
		}
	}
	return dk;
}

int main() {
	int size = 9;
	int node = 3;
	graph_t *g = create_graph(size);
	dij_kit *dk;

	init_graph(g);
	print_graph(g);
	dk = solve_dk(g, node);
	print_dij_kit(dk);
	
}
