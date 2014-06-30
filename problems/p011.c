#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Using the Sieve of Erosthenes
typedef unsigned int uint;
#define MAXSIZE 100005
#define MAXSIEVESIZE 31625
#define END 0xFFFFFFFF
#define CROSSED 0xFFFFFFFE


unsigned int arr[MAXSIZE];
unsigned int sieve[MAXSIEVESIZE];
unsigned int factorLimit;

// Get the numbers
void getLimits(uint *min, uint *max)
{
	scanf("%u %u", min, max);
}

void initializeArr(uint min, uint max)
{
	int i, size;

	size = max - min + 1;
	for (i=0; i<size; i++) {
		arr[i] = min + i;
	}
	if (min == 1) {
		arr[0] = CROSSED;
	}
	arr[i] = END;

}

void initializeSieve(uint min, uint max)
{
	int i;
	factorLimit = sqrt(max);
	for (i=0; i<=factorLimit; i++) {
		sieve[i] = i;
	}
	sieve[i] = END;
}


void printSieve(void)
{
	int i;
	//printf("Printing the Sieve\n");
	for (i=0; sieve[i] != END; i++) {
		if (sieve[i] != CROSSED) {
			//printf("%d\n", sieve[i]);
		}
	}
}

void printArr(void)
{
	int i;
	int count = 0;
	//printf("Printing the Prime Array\n");
	for (i=0; arr[i] != END; i++) {
		if (arr[i] != CROSSED) {
			count++;
			printf("%d\n", arr[i]);
		}
	}
	//("Number of primes:%d\n", count);
	printf("\n");
}

void prepareSieve(int min, int max)
{
	int i,j;

	initializeSieve(min, max);
	//printf("Determine Sieve\n");
	for (i=2; sieve[i] != END; i++) {
		if (sieve[i] != CROSSED) {
			//printf("Combing for %d\n", sieve[i]);
			for (j=2*i; j <= factorLimit; j=j+i) {
				sieve[j] = CROSSED;
			}
		}
	}
}

void findPrimes(uint min, uint max)
{

	int i, j, k, size;

	//printf("Finding primes from %d to %d\n", min, max);
	initializeArr(min, max);
	prepareSieve(min, max);
	printSieve();
	size = max - min + 1;
	for (i=0; arr[i] != END; i++) {
		if (arr[i] != CROSSED) { 
			//printf("Analyzing %d\n", arr[i]);
			for (j=2; sieve[j] != END; j++) {
				if ((sieve[j] != CROSSED) && (arr[i] > sieve[j])) {
					//printf("Checking factor %d %d\n", j, sieve[j]);
					if (arr[i]%sieve[j] == 0) {
						arr[i] = CROSSED;
						for (k=i; k < size; k=k+sieve[j]) {
							if (arr[k] != CROSSED) {
								//printf("Crossing out %d\n",arr[k]);
								arr[k] = CROSSED;
							}
						}
						sieve[j] = CROSSED;
						break;
					}
				}
			}
		}
	}
}

void verifyPrimes(int min, int max)
{
	int i, j, prime, size;
	printf("Verifying Primes\n");
	size = max - min + 1;
	for (i=0; i<size; i++) {
		if (arr[i] != CROSSED) {
			prime = arr[i];
			for (j = 2; j <sqrt(prime); j++) {
				if (arr[i]%j == 0) {
					printf("Error\n");
				}
			}
		}
	}
}

typedef struct __rangeType__ {
	uint min;
	uint max;
} rangeType;

int main(int argc, char **argv)
{
	int numTrials, trial;
	rangeType range[10];

	scanf("%d", &numTrials);

	trial = 0;
	while (trial < numTrials) {
		trial++;
		getLimits(&range[trial].min, &range[trial].max);
	}

	trial = 0;
	while (trial < numTrials) {
		trial++;
		findPrimes(range[trial].min, range[trial].max);
		printArr();
	}
	return 0;
}


// The input begins with the number t of test cases in a single line (t<=10). 
// In each of the next t lines there are two numbers m and n 
// (1 <= m <= n <= 1000000000, 
// n-m<=100000) 
// separated by a space.

// For every test case print all prime numbers p such that m <= p <= n, 
// one number per line, 
// test cases separated by an empty line.

