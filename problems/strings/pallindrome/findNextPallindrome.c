/*
 *
 * Problem: Given a number-string, find the next numerically higher number
 * that is a pallindrome.
 *
 *
 * Design:

	Given the number of digits can be as high as million, it is easier
	to manipulate this as a string as opposed to number.

	A good question to consider is whether there will be a need to increase
	the length of the number. 

	If the length increases, then the next biggest pall is simply
	1000..00001 where the ".." represents repeating chars.

	However, the biggest pall to anything below 999..999 would be
	999..999 of the same length. Hence there should be no reason
	to increase the length of given string to find the next biggest pall.

	There would be reasons to run the algo multiple times because a 9
	in the middle could change to 0 and cause a higher digit to change.
	Consider 
		43198995
		It will go through the following changes:
		43198995
		43199004
		43199134

	If we had done brute-force (go from element 1 and change mirrorPos), it would
	have resulted in the same answer
		43198995
		43198994
		43198934
		43198134
		43199134

	When the RHS side is more than the LHS side and they are bridged by 9-s, the
	change in RHS could cause a change in LHS. Otherwise, it will not cause a change
	in LHS.

	497 -> 505
	49997 -> 50005
	49897 -> 49904 -> 49994

	So, you could start with RHS, find the mPos, change it to RHS-value. 
		If the RHS-value is more than RHS &&
			LHS-to-RHS bridge is filled with 9-s,
				it will cause the LHS to increase as well
				and RHS has to re-increase to match LHS.

	Consider the case of
	444495 -> 444504 -> 445504 -> 445544

	Due to cased like this brute force method still needs increment. 
	Otherwise it would become
	444495 -> 444494 -> 444444

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1
#define MAXSIZE 1000002

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

int isBridgedBy9(char *s, int p1, int p2)
{
	int i;

	for (i=p1+1; i<p2; i++) {
		if (s[i] != '9') {
			return FALSE;
		}
	}
	return TRUE;
}

int incrPos(char *s, int pos, int len)
{
	int i;

	//printf("IncrPos str:%s pos:%d len:%d\n", s, pos, len);
	//sleep(1);
	// In this problem, we should never have to
	// increment the 0th digit from 9 to 10.
	if ((pos == 0) && (s[pos] == '9')) {
		// happens in a rare case where the given string
		// is already a pall filled with 9-s

		for (i=len-1; i>=0; i--) {
			s[i+1] = s[i];
		}
		s[0] = '0';
		return incrPos(s, 1, len+1);
	}
	if (s[pos] != '9') {
		s[pos] += 1;
		return pos;
	} else {
		s[pos] = '0';
		return incrPos(s, pos-1, len);
	}
}

void findNextPall(char *s, int lPos, int len)
{
	int rPos, changedPosition, i;

	// If we have reached midPosition, nothing more to do.
	if (lPos > len/2) {
		return;
	}

	rPos = len-1-lPos;
	if (rPos == lPos) {
		return;
	}

	if (s[rPos] <= s[lPos]) {
		s[rPos] = s[lPos];
		findNextPall(s, lPos+1, len);
	} else {
		if (rPos == lPos + 1) {
			s[rPos] = s[lPos] = s[lPos] + 1;
			return;
		}
		if (isBridgedBy9(s, lPos, rPos)) {
			s[rPos] = s[lPos] = s[lPos] + 1;
			for (i=lPos+1; i<rPos; i++) {
				s[i] = '0';
			}
			return;
		}
		s[rPos] = s[lPos];
		changedPosition = incrPos(s, rPos-1, len);
		if (changedPosition < lPos) {
			printf("Error case reached\n");
			exit(-1);
		} else {
			findNextPall(s, lPos+1, len);
		}
	}
}

char x[MAXSIZE*100];
int main(int argc, char **argv)
{

	int i, count, size, len, pos;
	//char *x;

	scanf("%d", &count);
	if (count > 100) {
		exit(1);
	}
	//size = sizeof(char)*MAXSIZE*count;
	//x = (char *) malloc(size);
	//memset(x, 0, size);
	for (i=0; i<count; i++) {
		scanf("%s", x+(i*MAXSIZE));
	}
	for (i=0; i<count; i++) {
		char *p = x+(i*MAXSIZE);
		len = strlen(p);
		if (isStringPallindrome(p)) {
			//printf("String is pall\n");
			pos = incrPos(p, len-1, len);
			if ((pos == 0) && (p[pos] == '1')) {
				len = len+1;
			}
		}
		//printf("String is %s\n",p);
		findNextPall(p, 0, len);
		printf("%s\n", p);
	}
	return 0;
}
