/*
 * Given a m x n grid filled with non-negative numbers, 
 * find a path from top left to bottom right 
 * which minimizes the sum of all numbers along its path.
 *
 * int (*a)[5] = (int [][5]){ 
 * 								{ 1, 2, 3, 4, 5 } , 
 * 								{ 6, 7, 8, 9, 10 } };
 *
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int *
create_matrix( int size) {
	int *mat;
	int i;

	mat = (int *) malloc(sizeof(int *) * size * size);
	assert(mat);
	for (i=0; i<size; i++) {
		memset(mat, 0, sizeof(int)*size*size);
	}
	return mat;
}

void
print_matrix( int *mat, int size, char *text) {
	int i, j;
	printf("Matrix %s\n", text);
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++) {
			printf("%8d", mat[i*size+j]);
		}
		printf("\n");
	}
}
void
print_path_matrix( char **mat, int size, char *text) {
	int i, j;
	printf("Matrix %s\n", text);
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++) {
			if ( mat[i*size+j] ) {
				printf("%8s", mat[i*size+j]);
			} else {
				printf("%8s", "");
			}
		}
		printf("\n");
	}
}

int min( int i, int j) {
	if ( i < j ) { return i; } else { return j; }
}
	
void
fill_cost_path( int *cost_matrix, char **path_matrix,
				int *qmat, int i, int j, int size) {
	char path[32];
	if ( cost_matrix[(i-1)*size+j] < cost_matrix[i*size+(j-1)] ) {
		cost_matrix[i*size+j] = cost_matrix[(i-1)*size+j] + 
									qmat[i*size+j];
		snprintf(path, 32, "%d, %d", i-1, j);
		path_matrix[i*size+j] = strdup(path);
	} else {
		cost_matrix[i*size+j] = cost_matrix[(i)*size+j-1] + 
									qmat[i*size+j];
		snprintf(path, 32, "%d, %d", i, j-1);
		path_matrix[i*size+j] = strdup(path);
	}
	return;
}

// Dynamic Programming:
// The answer for N rows depends on the answer for N-1 rows.
//
// Initialization:
// 	   Fill the [0][0] cell with [0][0]
// 	   Fill all [i][0] cells with [i-1][0].
// 	   Fill all [0][i] cells with [0][i-1].
//
// Sweep through the matrix diagonally.
// On a diagonal, the sum of i,j indices will always be less than
// a max number. The max number increases from 0 to 2*(size-1).
// The sweep can be done using two loops without repeats.
// For a given value of sum and i, j has only one value.
//
// In fact, sweeping diagnoally is not really required for this
// problem. One can sweep row-wise as well. That would be much 
// easier. Leaving the sweep diagonal implementation as it is
// just to show a diagonal sweeping routine.
//
void
find_path( int *qmat, int size) {
	char **path_matrix;
	int *cost_matrix;
	int i, j, sum;
	char path[32];

	path_matrix = (char **) malloc(sizeof( char *) * size * size);
	memset(path_matrix, 0, sizeof(char *) * size * size );
	cost_matrix = create_matrix(size);


	cost_matrix[0] = qmat[0];
	path_matrix[0] = "0, 0";

	for (i=1; i<size; i++) {
		cost_matrix[i] = cost_matrix[i-1] + qmat[i];
		snprintf(path, 32, "%d, %d", 0, i-1);
		path_matrix[i] = strdup(path);

		cost_matrix[i*size] = cost_matrix[(i-1)*size] + qmat[i*size];
		snprintf(path, 32, "%d, %d", i-1, 0);
		path_matrix[i*size] = strdup(path);
	}
	
	for (sum=1; sum<(2*size-1); sum++) {
		for (i=1; i<min(sum, size); i++) {
			j = sum-i;
			fill_cost_path( cost_matrix, path_matrix, qmat, i, j, size);
		}
	}
	print_matrix( cost_matrix, 5, "Cost");
	print_path_matrix( path_matrix, 5, "Path");

}

int main(int argc, char **argv) {

	int qmat[5][5] = { { 1, 1, 4, 2, 3 },
					   { 2, 3, 1, 4, 1 },
					   { 3, 2, 1, 2, 4 },
					   { 5, 4, 2, 4, 5 },
					   { 6, 7, 8, 9, 2 }};
	int i, j, size = 5;
	printf("Size of qmat is %lu\n", sizeof(qmat) );
	print_matrix( (int *)qmat, 5, "Question");
	find_path((int *)qmat, 5);

}
