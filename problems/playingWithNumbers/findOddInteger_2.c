#include <stdio.h>
#include <stdlib.h>

// Time start: 10:50
// Finish 1st draft: 11:02
// Time end: 11:06 

// Find the two numbers with odd occurrences in an unsorted array


#define MAXSIZE 26 // Pick Even size
#define UNIQUEVALUE1 234

int findSetbit(int x)
{
	int i;
	for (i=0; i<32; i++) {
		if (x && (1<<i)) {
			return i;
		}
	}
	return 0;
}

void printArray(int *arr)
{
	for (int i=0; i< MAXSIZE; i++) {
		printf("arr[%4d] = %d\n", i, arr[i]);
	}
}
void findUniqueAndPrint(int *arr)
{
	int i, x, y, xorValue, pos, arbitrer;

	xorValue = 0;
	for (i=0; i<MAXSIZE; i++) {
		xorValue ^= arr[i]; 
	}
	// if xorValue is zero, then there are no
	// two unique values in the array.
	if (xorValue == 0) {
		printf("Two unique values not present\n");
	}
	// find one of the bits set in xorValue.
	pos = findSetbit(xorValue);

	arbitrer = 1 << pos;
	x = y = 0;
	for (i=0; i<MAXSIZE; i++) {
		if (arr[i] & arbitrer) {
			x ^= arr[i];
		} else {
			y ^= arr[i];
		}
	}
	printf("x is %d and y is %d\n", x, y );
}

int main (int argc, char **argv)
{
	int *myArray;
	int i, halfsize;

	// Fill the Array with paired values.
	myArray = (int *)malloc(sizeof(int) * MAXSIZE);
	halfsize = MAXSIZE/2;
	for (i=0; i < halfsize; i++) {
		myArray[i] = myArray[MAXSIZE-1-i] = random();
	}

	// Overwrite one item in a pair with UNIQUE VALUE.
	// Othe item in pair automatically becomes UNIQUE.
	myArray[0] = UNIQUEVALUE1;
	printArray(myArray);
	findUniqueAndPrint(myArray);

}

/*
XOR of all elements gives us XOR of x and y because of the following properties of XOR operation.
1) XOR of any number n with itself gives us 0, i.e., n ^ n = 0
2) XOR of any number n with 0 gives us n, i.e., n ^ 0 = n
3) XOR is cumulative and associative.

So we have XOR of x and y after the first step. Let the value of XOR be xor2. 
Every set bit in xor2 indicates that the corresponding bits in x and y have values
 different from each other. For example, if x = 6 (0110) and y is 15 (1111), 
 then xor2 will be (1001), the two set bits in xor2 indicate that the corresponding 
 bits in x and y are different. In the second step, we pick a set bit of xor2 and 
 divide array elements in two groups. Both x and y will go to different groups.
  In the following code, the rightmost set bit of xor2 is picked as it is easy 
  to get rightmost set bit of a number. If we do XOR of all those elements of 
  array which have the corresponding bit set (or 1), then we get the first odd 
  number. And if we do XOR of all those elements which have the corresponding bit 0, 

  then we get the other odd occurring number. This step works because 
  of the same properties of XOR. All the occurrences of a number will go in
   same set. XOR of all occurrences of a number which occur even number 
 number of times will result in 0 in its set.
   And the xor of a set will be one of the odd occurring elements.
   */





