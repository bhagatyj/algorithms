/*
One part of the new WAP portal is also a calculator computing expressions with 
very long numbers. To make the output look better, the result is formated the 
same way as is it usually used with manual calculations.

Your task is to write the core part of this calculator. Given two numbers and 
the requested operation, you are to compute the result and print it in the 
form specified below. With addition and subtraction, the numbers are written
below each other. Multiplication is a little bit more complex: first of all,
we make a partial result for every digit of one of the numbers, and then 
sum the results together.

Input

There is a single positive integer T on the first line of input (equal to 
about 1000). It stands for the number of expressions to follow. Each 
expression consists of a single line containing a positive integer number,
an operator (one of +, - and *) and the second positive integer number. 
Every number has at most 500 digits. There are no spaces on the line. If
the operation is subtraction, the second number is always lower than the
first one. No number will begin with zero.

Output

For each expression, print two lines with two given numbers, the second 
number below the first one, last digits (representing unities) must be 
aligned in the same column. Put the operator right in front of the first 
digit of the second number. After the second number, there must be a 
horizontal line made of dashes (-).

For each addition or subtraction, put the result right below the horizontal
line, with last digit aligned to the last digit of both operands.

For each multiplication, multiply the first number by each digit of the 
second number. Put the partial results one below the other, starting with
the product of the last digit of the second number. Each partial result 
should be aligned with the corresponding digit. That means the last digit
of the partial product must be in the same column as the digit of the 
second number. No product may begin with any additional zeros. If a
particular digit is zero, the product has exactly one digit -- zero.
If the second number has more than one digit, print another horizontal
line under the partial results, and then print the sum of them.

There must be minimal number of spaces on the beginning of lines, with 
espect to other constraints. The horizontal line is always as long as 
necessary to reach the left and right end of both numbers (and operators) 
directly below and above it. That means it begins in the same column where 
the leftmost digit or operator of that two lines (one below and one above) 
is. It ends in the column where is the rightmost digit of that two numbers. 
The line can be neither longer nor shorter than specified.

Print one blank line after each test case, including the last one.

Example

Sample Input:

4
12345+67890
324-111
325*4405
1234*4

Sample Output:

 12345
+67890
------
 80235

 324
-111
----
 213

    325
  *4405
  -----
   1625
     0
 1300
1300
-------
1431625

1234
  *4
----
4936

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1
#define MAXDIGITS 1200
#define MAXSIZE (3*MAXDIGITS)
#define MAXCOUNT 1000

char op1[MAXSIZE];
char op2[MAXSIZE];
char result[MAXSIZE];

void printNumber (char *n, int startPos)
{
	int i, len, leading, printed;

	printed = 0;
	for (i=0; i<startPos; i++){
		printf(" ");
	}
	len = strlen(n);
	leading = TRUE;
	for (i=0; i<len; i++){
		if ((!printed) && (i == len-1)) {
			printf("0\n");
			return;
		}
		if ((leading) && (n[i] == '0')) {
			printf("%c", ' ');
		} else {
			leading = FALSE;
			printed += printf("%c", n[i]);
		}
	}
	printf("\n");
}

void addLeadingZeros(char *s, int clen, int len)
{
	int i, start, j;

	//printf("addLeadingZeros: %s clen:%d len:%d\n", s, clen, len);
	if (len != clen) {
		start = len-clen;
		for (i=len-1, j=clen-1; i>=start; i--, j--) {
			s[i] = s[j];
		}
		for (i=0; i<start; i++) {
			s[i] = '0';
		}
	}
	//printf("addLeadingZeros: %s\n", s);
}

void printDash(int start, int num)
{
	int i;
	for (i=0; i<num; i++) {
		printf("-");
	}
	printf("\n");
}

void reverse(char *s)
{
	int len = strlen(s);
	int i;
	char tmp;

	//printf("Original: %s\n", s);
	for (i=0; i<len/2; i++){
		tmp = s[i];
		s[i] = s[len-1-i];
		s[len-1-i] = tmp;
	}
	//printf("Reversed: %s\n", s);
}

int ctoi(char c)
{
	char tmp[2];
	tmp[1] = 0;
	tmp[0] = c;
	return atoi(tmp);
}

char itoc(int i)
{
	return ('0' + i);
}

void addNumbers(char *op1, char *op2, int len)
{
	char *ans;
	int n1, n2, n3, carry, i;

	// Add 2
	// During addition, the value could increase by 1 digit
	// Need an additional space for null char.
	ans = malloc(len+2);

	reverse(op1);
	reverse(op2);
	// printf("op1: %s op2: %s \n", op1, op2);
	carry = 0;
	for (i=0; i<len; i++) {
		n1 = ctoi(op1[i]);
		n2 = ctoi(op2[i]);
		n3 = n1 + n2 + carry;
		//printf("%d\n", n3);
		if (n3 > 9) {
			n3 = n3 - 10;
			carry = 1;
		} else {
			carry = 0;
		}
		ans[i] = itoc(n3);
		//printf("%c\n", ans[i]);
	}
	ans[i] = itoc(carry);
	//printf("Ans: %s\n", ans);
	reverse(ans);
	printNumber(ans, 0);
}

void subNumbers(char *op1, char *op2, int len)
{
	char *ans;
	int n1, n2, n3, borrow, i;

	// Add 2
	// During addition, the value could increase by 1 digit
	// Need an additional space for null char.
	ans = malloc(len+2);

	reverse(op1);
	reverse(op2);
	// printf("op1: %s op2: %s \n", op1, op2);
	borrow = 0;
	for (i=0; i<len; i++) {
		n1 = ctoi(op1[i]);
		n2 = ctoi(op2[i]);
		n3 = n1 - n2 - borrow;
		//printf("%d\n", n3);
		if (n3 < 0) {
			n3 = n3 + 10;
			borrow = 1;
		} else {
			borrow = 0;
		}
		ans[i] = itoc(n3);
		//printf("%c\n", ans[i]);
	}
	ans[i] = itoc(borrow);
	//printf("Ans: %s\n", ans);
	reverse(ans);
	printNumber(ans, 0);
}

void operation(char *op1, char *op2, char op)
{
	int l1 = strlen(op1);
	int l2 = strlen(op2);
	int lmax = (l2 > l1) ? l2 : l1;

	addLeadingZeros(op1, l1, lmax);
	addLeadingZeros(op2, l2, lmax);

	printNumber(op1,1);
	printf("%c", op);
	printNumber(op2,0);
	printDash(0, lmax+1);

	switch (op) {
		case '+':
			addNumbers(op1, op2, lmax);
			break;
		case '-':
			subNumbers(op1, op2, lmax);
			break;
	}
	
}



void calculate(char *s)
{
	char *op1, *op2, *op, oper[2];
	int op1Len;

	op = strchr(s, '+');
	if (!op) {
		op = strchr(s, '-');
	}
	oper[0] = op[0];
	oper[1] = 0;
	if (!op) {
		printf("Couldnt find the operators\n");
		return;
	}

	//printf("Input string: %s Operation: %s\n", s, op);
	op1 = strsep(&s, oper);
	op2 = s;

	strcpy(s+MAXDIGITS, op2);
	op1Len = strlen(op1);
	memset(op1+op1Len, 0, MAXDIGITS-op1Len-1);
	op2 = s+MAXDIGITS;
	operation(op1, op2, oper[0]);
}

int main(int argc, char **argv)
{

	int i, count, size;
	char *x;

	scanf("%d", &count);
	if (count > MAXCOUNT) {
		exit(1);
	}
	size = sizeof(char)*MAXSIZE*count;
	x = (char *) malloc(size);
	memset(x, 0, size);
	for (i=0; i<count; i++) {
		scanf("%s", x+(i*MAXSIZE));
	}
	for (i=0; i<count; i++) {
		char *p = x+(i*MAXSIZE);
		calculate(p);
	}
	return 0;
}

