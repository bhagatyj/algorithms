// You have an array of integers(size N), such that 
// all the numbers except one are present even number
// of times. Find the odd-one.

// Solution:
// If you xor over the array, you should get the number
// that is present odd number of times.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// ARRAYSIZE should be odd number to allow for 
#define ARRAYSIZE 25
#define UNIQUENUM 345

int funcXor(int a, int b)
{
	return (a^b);
}

int funcPrint(int a, int b)
{
	return printf("%d\n", b);
}

int funcOverArray(int *arr, int count, int func(int, int))
{
	int i, final;
	final = 0;
	for (i=0; i<count; i++) {
		final = func(final, arr[i]);
	}
	return final;
}


int * getMyArray(int count, int unique)
{
	int *myArray;
	int halfCount, i;

	myArray = (int *)malloc(sizeof(int) * count);

	halfCount = count/2;
	srandomdev();
	for (i=0; i < halfCount; i++) {
		myArray[i] = random();
		myArray[count-i-1] = myArray[i];
	}
	myArray[i] = unique;

	return myArray;
}

int main(int argc, char **argv)
{
	int *myArray = getMyArray(ARRAYSIZE, UNIQUENUM);
	funcOverArray(myArray, ARRAYSIZE, funcPrint);
	int ans = funcOverArray(myArray, ARRAYSIZE, funcXor);
	printf("Xor-ed answer is %d. Xor-ed answer should be %d\n", ans, UNIQUENUM);
}