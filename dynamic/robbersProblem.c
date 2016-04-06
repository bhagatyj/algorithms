/*
 * You are a professional robber planning to rob houses along a street. 
 * Each house has a certain amount of money stashed, the only constraint 
 * stopping you from robbing each of them is that adjacent houses have 
 * security system connected and it will automatically contact the police 
 * if two adjacent houses were broken into on the same night.
 *
 * Given a list of non-negative integers representing the amount of money 
 * of each house, determine the maximum amount of money you can rob 
 * tonight without alerting the police.
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

/* 
 * This is a dynamic problem - "optimal substructure" pattern.
 * In other words,
 *
 * The answer for N houses depends on the answer for "N-1" houses
 * and the answer for "N-2" houses.
 *
 *  amount(N) = maxOf ( amount(N-1), amount(N-2) + value(N) )
 *
 * Initial condition:
 * 	amount(0) = 0
 * 	amount(1) = value(1)
 *
 * From here on..
 * amount(2) = max( amount(1), value(2) )
 * amount(3) = max( amount(2), amount(1) + value(3) )
 * amount(4) = max( amount(3), amount(2) + value(4) )
 *
 * and so on..
 * Thus sub-problem + memoization technique can be used
 * to solve this problem.
 * When computing the answer for N, we need to remember the answers
 * for N-1 and N-2.
 *
 */
int rob( int *house, int count) {

	int n;
	int ans_n, ans_n_minus_1, ans_n_minus_2;

	n=2;
	ans_n_minus_2 = 0;
	ans_n_minus_1 = house[0];

	while ( n <= count ) {
		ans_n = max( ans_n_minus_1, ans_n_minus_2 + house[n-1] );
		ans_n_minus_2 = ans_n_minus_1;
		ans_n_minus_1 = ans_n;
		n++;
	}
	return ans_n;
}

int main(int argc, char **argv) {
	
	int houses[6] = { 1, 100, 2, 100, 3, 100};
	int result;

	assert( rob( houses, 6 ) == 300 );

	houses[0] = 200;
	assert( rob( houses, 6 ) == 400 );

	houses[0] = 100; houses[4] = 200;
	assert( rob( houses, 6 ) == 302 );

	houses[4] = 300;
	assert( rob( houses, 6 ) == 402 );
}
