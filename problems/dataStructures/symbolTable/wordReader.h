#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAXWORDSIZE 24
#define MAXLINESIZE 500
#define MAXWORDS 50

#define TRUE 1
#define FALSE 0


/*
 * getword, getch, ungetch from K & R C Programming Language Book.
 */

#define BUFSIZE 100

int getch(void);
void ungetch(int c);
int getword(char *word, int lim);