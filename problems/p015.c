/*
SPOJ : Classic-P4 
Transform the algebraic expression with brackets into RPN form (Reverse Polish Notation). 
Two-argument operators: +, -, *, /, ^ (priority from the lowest to the highest), brackets ( ). 
Operands: only letters: a,b,...,z. 
Assume that there is only one RPN form (no expressions like a*b*c).

Input

t [the number of expressions <= 100]
expression [length <= 400]
[other expressions]
Text grouped in [ ] does not appear in the input file.

Output

The expressions in RPN form, one per line.
Example

Input:
3
(a+(b*c))
((a+b)*(z+x))
((a+t)*((b+(a+c))^(c+d)))

Output:
abc*+
ab+zx+*
at+bac++cd+^*

http://en.literateprograms.org/Shunting_yard_algorithm_(C)

The algorithm
==============
The algorithm works by reading each token in order, and processing them by the following rules:
If it is a number token, it is pushed on a number stack (or the output queue, if we were generating RPN)
If it is an operator, pop operators from the operator stack and evaluate them with values from the number stack, until we reach one that has lower precedence. Then we push the original operator.
In the case of a right associative operator, we also stop if we reach an operator of the same precedence.
If it is a left parenthesis, just push it.
If it is a right parenthesis, we pop all operators (and evaluate them) until the matching left parenthesis. The parentheses are thrown away.
After all tokens are read, the remaining operators on stack are popped and evaluated.


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "p015_stack.h"

#define TRUE 1
#define FALSE 0
#define MAXSIZE 401
#define MAXWORKINGSIZE 3*MAXSIZE


char wSet[MAXWORKINGSIZE];

typedef struct __queue__ {
	char values[MAXWORKINGSIZE];
	int top;
} queue;

queue * createQueue()
{
	queue *q = malloc(sizeof(queue));
	memset(q, 0, sizeof(queue));
	return q;
}

void add(queue *q, char c)
{
	q->values[q->top] = c;
	q->top++;
}

void printQ(queue *q)
{
	int i;

	if (!DEBUG) {
		return;
	}
	printf("Queue is : ");
	for (i=0; i<q->top; i++) {
		printf("%c", q->values[i]);
	}
	printf("\n");
}

int isOneOf(char c, char * set)
{
	int i, len;
	len = strlen(set);
	for (i=0; i<len; i++) {
		if (set[i] == c) {
			return TRUE;
		}
	}
	return FALSE;
}

int popCMoreThanCurrent(char popC, char c)
{
	if (c == 0) {
		return TRUE;
	}
	switch(c) {
		case '+':
			return isOneOf(popC, "-*/^");
		case '-':
			return isOneOf(popC, "*/^");
		case '*':
			return isOneOf(popC, "/^");
		case '/':
			return isOneOf(popC, "^");
		case '^':
			return FALSE;
	}
	return FALSE;
}

void evaluateTillParen(queue *nq, stack *ost)
{
	char popC;

	while ((popC = pop(ost)) != 0) {
		if (popC == '(') {
			break;
		}
		add(nq, popC);
	}
}

void evaluate(queue *nq, stack *ost, char c)
{
	char popC;

	if (c == ')') {
		evaluateTillParen(nq, ost);
		return;
	}

	popC = pop(ost);

	// Check for End-Reached.
	if (DEBUG) {
		printf("Popped %c\n", popC);
	}
	if (popC == 0) {
		return;
	}


	if (popCMoreThanCurrent(popC, c)) {
		evaluate(nq, ost, popC);
	} else {
		push(ost, popC);
		return;
	}
	printf("Adding %c to queue\n", popC);
	add(nq, popC);
}

void convertToRPN(char *p)
{
	stack *ost;
	queue *nq;
	char dst[MAXSIZE], c;

	printf("Infix: %s\n", p);
	ost = createStack();
	nq = createQueue();

	while (*p) {
		c = *p++;
		if (DEBUG) {
			printf("\nEvaluating %c\n", c);
			printQ(nq); printStack(ost);
		}
		if (isalpha(c)) {
			add(nq, c);
			continue;
		}
		if (c == '(') {
			push(ost, c);
			continue;
		}
		if (c == ')') {
			evaluate(nq, ost, c);
			continue;
		}
		// c is an operator.
		evaluate(nq, ost, c);
		push(ost, c);
	}
	// Completed. Run an evaluation.
	evaluate(nq, ost, 0);
	printQ(nq);
}

void mainTest(int argc, char **argv)
{
	convertToRPN("(a+(b*c))");
	convertToRPN("a*b+c");
	convertToRPN("((a+t)*((b+(a+c))^(c+d)))");
}

int main(int argc, char **argv)
{
	int i, count, size;
	char *x;

	scanf("%d", &count);
	if (count > 100) {
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
		convertToRPN(p);
		printf("%s\n", p);
	}
	return 0;
}
