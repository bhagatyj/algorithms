#include "wordTreeBuilder.h"

int mystrcmp(void *v1, void *v2)
{
	return (strcmp((char *)v1, (char *)v2));
}

void * buildTheWordTree(genValue_fn_t genValue)
{
	char word[WORDSIZE];
	int total = 0;
	symbol_table_t *st;
	void *node;
	int value;

	st = createST(mystrcmp, genValue);
	while (getword(word, WORDSIZE) != EOF) {
		if (isalpha(word[0])) {
			total++;
			value = genValue(word, 0);
			node = st->fnCreateNode(word, value);
			st->addNode(st, node);
			// process word
		}
	}
	return st;

}