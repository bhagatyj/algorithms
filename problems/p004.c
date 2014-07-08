// HDR : Euler P4
//
// A palindromic number reads the same both ways. 
// The largest palindrome made from the product of 
// two 2-digit numbers is 9009 = 91 × 99.
// Find the largest palindrome made from the product 
// of two 3-digit numbers.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXCHAR 24
#define TRUE 1
#define FALSE 0

int isStringPallindrome(char *s)
{
	int len = strlen(s);
	int i;

	if (len <= 1) {
		return TRUE;
	}
	i = 0;

	while (i <= len/2) {
		if ( *(s+i) == *(s+len-1-i) ) {
			i++;
		} else {
			return FALSE;
		}
	}
	return TRUE;
}

int isIntPallindrome(int x)
{
	char s[MAXCHAR];
	sprintf(s, "%d", x);
	return isStringPallindrome(s);
}


void pallindromeTester()
{
	int list[] = {23, 30, 33, 343, 2,
					3456, 3223, 41214, 213, 99789};
	int i;
	for (i=0; i< 10; i++) {
		printf("%d %s pallindrome check.\n", list[i], 
			isIntPallindrome(list[i]) ? "passes" : "fails");
	}
}

int max = 999;

int main(int argc, char **argv)
{
	int row, col;
	int count = 0;
	int *list, i, number;

	list = (int *)malloc(sizeof(int)*max);
	memset(list, 0, sizeof(int)*max);
	for (row = max; row > 900; row--) {
		for (col = row; col <=max; col++) {
			number = col*row;
			if (isIntPallindrome(number)) {
				list[count] = number;
				count++;
			}
		}
	}

	for (i=0; i<count; i++) {
		printf(" %8d \n", list[i]);
	}
}