#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	int num;
	while (1) {
		scanf("%d", &num);
		if (num == 42) {
			exit(0);
		}
		printf("%d\n", num);
	}
}

// Your program is to use the brute-force approach in order to find the Answer to Life, the Universe, and Everything. 
// More precisely... rewrite small numbers from input to output. Stop processing input after reading in the number 42. 
// All numbers at input are integers of one or two digits.
