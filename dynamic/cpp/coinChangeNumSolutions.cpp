#include<stdio.h>

int count( int S[], int numCoins, int totalValue )
{
    int coinIndex, value, numSolutionsUsingThisCoin, numSolutionsUsingOtherCoins;

    // numOfSolutions[i][j] represents number of ways to make sum i using first j elements
    // We need totalValue+1 rows as the numOfSolutions is consturcted in bottom up manner using
    // the base case 0 value case (totalValue = 0)
    int numOfSolutions[totalValue+1][numCoins];

    // Fill the enteries for 0 value case (totalValue = 0)
    // Whatever be the coinIndex's value, the number of such coins
    // needed to satisfy a value of 0 is 0.
    for (coinIndex=0; coinIndex<numCoins; coinIndex++)
        numOfSolutions[0][coinIndex] = 1;

    // Fill rest of the numOfSolutions enteries in bottom up manner
    for (value = 1; value < totalValue+1; value++) {
        for (coinIndex = 0; coinIndex < numCoins; coinIndex++) {
            int coinValue = S[coinIndex];
            
	        // We pick the number of solutions we used for last time.
	        if( value < coinValue ) {
                numSolutionsUsingThisCoin = 0;
            } else {
                numSolutionsUsingThisCoin = numOfSolutions[value-coinValue][coinIndex];
            }

            if( coinIndex >= 1 ) {
                numSolutionsUsingOtherCoins = numOfSolutions[value][coinIndex-1];
            } else {
                numSolutionsUsingOtherCoins = 0;
            }
    
	        // total count
	        numOfSolutions[value][coinIndex] = numSolutionsUsingThisCoin + 
                                                    numSolutionsUsingOtherCoins;
	    }
    }
    return numOfSolutions[totalValue][numCoins-1];
}

int main()
{
    int coinValues[] = {1, 2, 3};
    int numCoins = sizeof(coinValues)/sizeof(coinValues[0]);
    int totalValue = 4;
    printf(" %d ", count(coinValues, numCoins, totalValue));
  return 0;
}

