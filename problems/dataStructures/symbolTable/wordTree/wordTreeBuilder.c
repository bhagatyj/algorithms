#include "wordTreeBuilder.h"

int mystrcmp(void *v1, void *v2)
{
	return (strcmp((char *)v1, (char *)v2));
}

void * buildTheWordTree(genValue_fn_t genValue)
{
	char word[WORDSIZE];
	int total = 0;
	void *symbolTable;
	void *node;
	int value;

	symbolTable = createST(mystrcmp, genValue);
	while (getword(word, WORDSIZE) != EOF) {
		if (isalpha(word[0])) {
			total++;
			value = genValue(word, 0);
			node = createNode(word, value);
			addNodeToST(symbolTable, node);
			// process word
		}
	}
	return symbolTable;

}