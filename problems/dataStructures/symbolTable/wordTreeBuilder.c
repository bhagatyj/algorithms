#include "wordTreeBuilder.h"

int mystrcmp(void *v1, void *v2)
{
	return (strcmp((char *)v1, (char *)v2));
}

void * buildTheWordTree()
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
	return symbolTable;

}