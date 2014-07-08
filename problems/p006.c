// Code a function that receives a string composed by words separated
// by spaces and returns a string where words appear in the same order 
// but than the original string, but every word is inverted. 

// For example "boy ran fast" becomes "yob nar tsaf"

// Same problem as P5. In this case, the reversal is done inline.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	int i,j, len;
	int wordIndex;
	char *line;
	char c;

	// Initialization
	line = "Here is an apple";
	wordIndex = 0;
	len = strlen(line);


	for (i=0; i<len; i++) {
		c = line[i];
		if (isalnum(c)) {
			// Either a word just started
			// Or a char is added to the word
			// Keep counting.
			wordIndex++;
		} else {
			// If a word just finished,
			// 		print it in reverse
			// else
			//		print and continue
			if (wordIndex) {
				for (j=1; j<=wordIndex; j++) {
					printf("%c", line[i-j]);
				}
				wordIndex = 0;
			}
			printf("%c", line[i]);
		}
	}
	// Handle the case where the line finishes without delimiter.
	if (wordIndex) {
		for (j=1; j<=wordIndex; j++) {
			printf("%c", line[i-j]);
		}
	}
	printf("\n");
	return 0;
}