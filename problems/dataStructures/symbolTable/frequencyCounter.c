#include "symbolTable.h"
#include "wordReader.h"
/*
 * This use-case of the symbol Table API is going to work on the following
 * problem.
 *
 * 1) Read-in a huge amount of text
 * 2) Each word is the key of the symbol
 * 3) The value is the number of times it has occurred so far.
 * 4) Print out the most occuring ten words.
*/

#define WORDSIZE 200

int main(int argc, char **argv)
{
	char word[WORDSIZE], *longestWord;
	int total = 0;
	int longest = 0;

	while (getword(word, WORDSIZE) != EOF) {
		if (isalpha(word[0])) {
			total++;
			if (strlen(word) > longest) {
				longest = strlen(word);
				printf("%s\n", word);
				longestWord = strdup(word);
			} 
			// process word
		}
	}
	printf("Total number of words is %d\n", total);
	printf("Longest word is %s\n", longestWord);
}