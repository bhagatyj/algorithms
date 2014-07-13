#include "wordReader.h"
#include "symbolTable.h"
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

int mystrcmp(void *v1, void *v2)
{
	return (strcmp((char *)v1, (char *)v2));
}

int main(int argc, char **argv)
{
	char word[WORDSIZE];
	int total = 0;
	void *symbolTable;
	void *node;

	symbolTable = createST(mystrcmp);
	while (getword(word, WORDSIZE) != EOF) {
		if (isalpha(word[0])) {
			total++;
			node = createNode(word, 1);
			addNodeToST(symbolTable, node);
			// process word
		}
	}
	dfs(symbolTable);
}