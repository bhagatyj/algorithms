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

static unsigned long currentLongestValue = 0;
static char *currentLongestKey;


int findLongestWord (void *key, unsigned long value)
{

	if (value > currentLongestValue) {
		currentLongestValue = value;
		currentLongestKey = key; 
	}
	return currentLongestValue;
}


int main(int argc, char **argv)
{
	int value;
	symbol_table_t *st;

	st = buildTheWordTree(lenValue);
	st->walkTreeFn(st, findLongestWord);
	printf("%s:%4lu\n", currentLongestKey, strlen(currentLongestKey));
	return 0;
}
