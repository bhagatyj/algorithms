
// HDR Euler P1 
//
// Problem Definition:
// If we list all the natural numbers below 10 that are 
// multiples of 3 or 5, we get 3, 5, 6 and 9. 
// The sum of these multiples is 23.
// Find the sum of all the multiples of 3 or 5 below 1000.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct __intList__ {
	int count;
	int *numbers;
}	intList;

intList * findMultiples(int above, int below, int factor)
{
	int i;
	int size;
	int *numbers;
	int start, index = 0;
	intList *iL;

	// Initialize DS
	size = (below-above-1)/factor;
	numbers = (int *)malloc(sizeof(int) * size);
	iL = (intList *) malloc(sizeof(intList));
	iL->count = 0;

	// Populate DS
	start = above + (factor - above%factor);
	for (i= start, index = 0; i < below; i += factor, index++)
	{
		numbers[index] = i;
	}

	// Return DS
	iL->count = size;
	iL->numbers = numbers;
	return iL;

}

void printList(intList *iL)
{

	int i;

	printf("Size of the List is : %d\n", iL->count);
	for (i = 0; i< iL->count; i++) {
		printf("%d ", iL->numbers[i]);
	}
	printf("\n");

}

unsigned long sumList(intList *iL)
{
	unsigned long sum = 0;
	int i;

	for (i=0; i<iL->count; i++)
	{
		sum += iL->numbers[i];
	}
	return sum;
}

intList * mergeLists(intList *iL1, intList *iL2)
{
	int iCidx, iL1idx, iL2idx;
	int iCsize, iL1size, iL2size;
	int n1, n2;
	intList *iC;
	int *numbers;

	// Allocate an array that is larger than required.
	iCidx = iL1idx = iL2idx = 0;
	iL1size = iL1->count;
	iL2size = iL2->count;
	iCsize = iL1size + iL2size;
	numbers = (int *) malloc(sizeof(int)*iCsize);
	iC = (intList *) malloc(sizeof(intList));

	while ((iL1idx < iL1size) && (iL2idx < iL2size)) {
		n1 = iL1->numbers[iL1idx];
		n2 = iL2->numbers[iL2idx];
		if (n1 == n2) {
			numbers[iCidx] = n1;
			iL2idx++;
			iL1idx++;
		}
		if (n1 > n2) {
			numbers[iCidx] = n2;
			iL2idx++;
		}
		if (n1 < n2) {
			numbers[iCidx] = n1;
			iL1idx++;
		}
		iCidx++;
	}

	while (iL1idx < iL1size) {
		numbers[iCidx] = iL1->numbers[iL1idx];
		iCidx++;
		iL1idx++;
	}

	while (iL2idx < iL2size) {
		numbers[iCidx] = iL2->numbers[iL2idx];
		iCidx++;
		iL2idx++;
	}

	// Free the larger array if there are elements in common.
	iC->count = iCidx;
	if (iCidx < iCsize) {
		iC->numbers = (int *)malloc(sizeof(int) * iCidx);
		memcpy(iC->numbers, numbers, sizeof(int)* iCidx);
		free(numbers);
	} else {
		iC->numbers = numbers;
	}
	return iC;

}


int main (int argc, char **argv)
{

	intList *iL1, *iL2, *iC;

	iL1 = findMultiples(0, 1000, 3);
	iL2 = findMultiples(0, 1000, 5);
	printList(iL1);
	printList(iL2);
	iC = mergeLists(iL1, iL2);
	printList(iC);
	printf("Sum of List iC is: %lu \n",sumList(iC));
}