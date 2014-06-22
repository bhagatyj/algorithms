// HDR : Euler P3
// 
// The prime factors of 13195 are 5, 7, 13 and 29.
// What is the largest prime factor of the number 600851475143 ?


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define isDivisor(number, dividend) (number%dividend ? 0 : 1)

int isPrime(int number)
{
	int i, max;

	if (number%2 == 0) {
		return 0;
	}

	if (number%3 == 0) {
		return 0;
	}

	max = sqrt(number);
	for (i=5; i<max; i+=2) {
		if (number%i == 0) {
			return 0;
		}
	}
	return 1;
}

int main(int argc, char **argv)
{
	unsigned long number = 600851475143;
	int i, max;

	max = sqrt(number);
	for (i = max; i>1; i--) {
		if (!isDivisor(number, i)) {
			continue;
		}
		if (isPrime(i)) {
			break;
		}
	}
	printf("%d is the largest prime factor of %lu \n", i, number);
}