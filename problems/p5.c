// HDR : Split a line into words.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXWORDSIZE 24
#define MAXLINESIZE 500
#define MAXWORDS 50

#define TRUE 1
#define FALSE 0

char *delimiters = " \t\b\n\r.,\'\"";

int isDelimiter(char c)
{
	int i, max;
	max = strlen(delimiters);
	for (i=0; i<max; i++) {
		if (c == delimiters[i]) {
			return TRUE;
		}
	}
	return FALSE;
}

char ** getWords(char *line)
{
	char **words;
	char *word, c;
	unsigned int wordIndex;
	int i, lineLen, numWords;

	words = (char **)malloc(sizeof(char *) * MAXWORDS);
	memset(words, 0, sizeof(char *) * MAXWORDS);

	lineLen = strlen(line);
	wordIndex = 0;
	numWords = 0;
	// wordIndex also stands in for wordInProgress boolean.
	// wordIndex has to be non-zero for word to be InProgress.
	for (i=0; i<lineLen; i++) {
		c = *(line + i);
		if (isDelimiter(c)) {
			if (wordIndex) {
				// cut off word.
				// add last word to list of words.
				wordIndex = 0;
				words[numWords++] = word;
			} else {
				// ignore extra delimiters
				// do nothing.
			}
		} else {
			if (wordIndex) {
				// extend current word with char
				word[wordIndex++] = c; 

			} else {
				// start a new word
				word = (char *)malloc(sizeof(char)*MAXWORDSIZE);
				word[0] = c;
				wordIndex = 1;
			}

		}
	}
	// Account for the last word.
	if (wordIndex) {
		words[numWords++] = word;
	}

	return words;

}

int main(int argc, char **argv)
{
	int i;

	char **words = getWords("Here is an apple.");
	for (i=0; i<MAXWORDS; i++) {
		if (words[i]) {
			printf("%s\n", words[i]);
		} else {
			break;
		}
	}
	return 0;
}