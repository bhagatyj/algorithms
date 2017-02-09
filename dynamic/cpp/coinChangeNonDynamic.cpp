#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

	int coinChange(vector<int>& coins, int amount);
	int findCoins(vector<int>& coins, int index, int amount, int coins_so_far, int &solution);
};

int
Solution::coinChange(std::vector<int> &coins, int amount) {
	// Sort the vector

	int solution = -1;
	std::sort(coins.begin(), coins.end());
	findCoins(coins, coins.size()-1, amount, 0, solution);
	return solution;

}

int
Solution::findCoins(std::vector<int> &coins, int index, int amount, int coins_so_far, int &solution) {
	int max_coins, num_coins, i, j, rest;

	// If there are no more coins, we have come to the end of the
	// road. 
	if ( index == -1 ) {
		return -1;
	}

	int denom = coins[index];

	// The maximum number of coins that I can use at this denomination
	// is given by dividing the amount by the denomination. If it 
	// divides without a remainder, I need not use any further denominations.
	// I just need to return the dividend.

	if ( ( amount % denom ) == 0 ) {
		num_coins = amount/denom;
		// Check if this is lesser than best solution so far
		if (solution != -1) {
			if ( coins_so_far + num_coins < solution) {
				solution = coins_so_far + num_coins;
			}
		} else {
			solution = coins_so_far + num_coins;
		}
		return num_coins;
	}

	// Since there is a remainder, I need to solve the remainder using the rest
	// of the denominations - if possible. I should try remainders for all possible 
	// multiples of this denominator - starting from the max multiple.

	int max_factor = amount/denom;
	for (i=max_factor; i>=0; i--) {
		// If I already have a solution that is better than the current pursuit,
		// Let's drop the pursuit.
		if ( solution != -1 ) {
			if ( coins_so_far+i > solution ) {
				break;
			}
		}
		rest = amount - (i*denom);
		int ans = findCoins( coins, index-1, rest, coins_so_far+i, solution);
        // We may or may not have found the answer in this run.
        // Irrespective, continue through all the runs and keep accumulating
        // the solutions in the solution variable.
        // After we try all the runs, we will get the minimum value.
        //

	}
	// Tried all possible combinations
	return -1;
}
