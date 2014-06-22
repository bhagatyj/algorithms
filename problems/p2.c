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

int main(int argc, char **argv)
{
	max = 100000;
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