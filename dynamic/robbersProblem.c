/*
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
 *
 * Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int max( int x, int y) {
	if ( x > y ) {
		return x;
	} else {
		return y;
	}
}

int rob( int *houses, int count) {

	int i;
	int *results;

	if ( ( houses == NULL ) || ( count == 0 ) ) {
		return 0;
	}

	results = ( int * ) malloc( sizeof(int) * (count + 1) );
	results[0] = 0;
	results[1] = houses[0];

	for (i=2; i<count+1; i++) {
		results[i] = max( results[i-1], results[i-2] + houses[i-1] );
		printf("%d:%d %d %d -> %d\n", i, 
					results[i-1], results[i-2], 
					houses[i-1], results[i]);
	}
	return results[count];

}

void printHouses( int *houses, int count, int result) {
	int i;
	printf("Houses:		");
	for (i=0; i<count; i++) {
		printf("%4d ", houses[i]);
	}
	printf(" ---> %4d\n", result);
}

int main(int argc, char **argv) {
	
	int houses[6] = { 1, 100, 2, 100, 3, 100};
	int result;

	result = rob( houses, 6 );
	printHouses( houses, 6, result);
	assert( result == 300 );

	houses[0] = 200;
	result = rob( houses, 6 );
	printHouses( houses, 6, result);
	assert( result == 400 );

	houses[0] = 100; houses[4] = 200;
	result = rob( houses, 6 );
	printHouses( houses, 6, result);
	assert( result == 302 );

	houses[4] = 300;
	result = rob( houses, 6 );
	printHouses( houses, 6, result);
	assert( result == 402 );


}
