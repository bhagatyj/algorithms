// HDR: Prime Number Generation : Sieve of Eratosthenes
//
// Store all the numbers till the max number - with flag.
// Doesnt use any form of multiplication/division.
// Uses plain and simple addition.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define CROSSED 1
int max = 0;

typedef struct _nCell_ {
	int value;
	int flag;
} nCell;

void crossOut(nCell *nList, int index)
{
	assert(index < max);
	nList[index].flag = CROSSED;
}

int isCrossedOut(nCell *nList, int index)
{
	assert(index < max);
	return (nList[index].flag & CROSSED);
}

void printPrimes(nCell *nList)
{
	int i, count;
	printf("Printing List of primes till %d:\n", max);
	count = 0;
	for (i=0; i<max; i++) {
		if (isCrossedOut(nList, i)) {
			continue;
		}
		printf(" %6d ", i);
		count++;
		if (count%8 == 0) {
			printf("\n");
		}
	}
	printf("\n");
	printf("Found %d primes till %d\n",count, max);
}

int generatePrimes(unsigned int max)
{
	nCell *nList;
	int i, j;

	nList = (nCell *) malloc(sizeof(nCell) *max);
	for (i=0; i<max; i++) {
		nList[i].value = i;
		nList[i].flag = 0;
	}
	crossOut(nList, 0);
	crossOut(nList, 1);

	for (i=0; i<max; i++) {
		if (isCrossedOut(nList, i)) {
			continue;
		}
		for (j=2*i; j<max; j+=i) {
			crossOut(nList, j);
		}
	}
	printPrimes(nList);
}


/*
Peter wants to generate some prime numbers for his cryptosystem. 
Help him! Your task is to generate all prime numbers 
between two given numbers!

Input

The input begins with the number t of test cases in a 
single line (t<=10). In each of the next t lines there are 
two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) 
separated by a space.

Output

For every test case print all prime numbers p such that m <= p <= n, 
one number per line, test cases separated by an empty line.

Example

Input:
2
1 10
3 5

Output:
2
3
5
7

3
5
*/