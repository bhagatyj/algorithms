#include "wordTreeBuilder.h"
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

unsigned long lenValue (void *key, int currentValue)
{
	return (strlen(key));
}

int main(int argc, char **argv)
{
	int value;
	void *st;

	st = buildTheWordTree(lenValue);

	// The word tree has been built with length values.
	// Need to implement searching the tree 
	// to find the longest word.
	// Next requirements are
	// Search-tree-by-key
	// Search-tree-by-value (first match)
	// Search-tree-by-value (continue beyond first match)
	// Search-tree-for-condition (for e.g. largest value)

}

// int main(int argc, char **argv)
// {
// 	char word[WORDSIZE], *longestWord;
// 	int total = 0;
// 	int longest = 0;

// 	longestWord = NULL;
// 	while (getword(word, WORDSIZE) != EOF) {
// 		if (isalpha(word[0])) {
// 			total++;
// 			if (strlen(word) > longest) {
// 				longest = strlen(word);
// 				if (longestWord) {
// 					free(longestWord);
// 				}
// 				longestWord = strdup(word);
// 			} 
// 			// process word
// 		}
// 	}
// 	printf("Longest word is %s\n", longestWord);
// }