#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

typedef struct __ufNode__ {
	int root;
	int size;
} ufNode;

ufNode *uf;
int numNodes;

void createUF(int count)
{

	int i;

	// Allocate
	numNodes = count;
	uf = (ufNode *)malloc(sizeof(ufNode) * count);
	if (!uf) {
		printf("Allocation Failure\n");
	}
	//printf("Allocation Success\n");

	// Initialize
	for (i=0; i<count; i++) {
		uf[i].root = i;
		uf[i].size = 1;
	}
	return;

}

int root(int p)
{
	int orig;
	orig = p;
	while (uf[p].root != p) {
		p = uf[p].root;
	}
	//printf("Root of %d is %d\n", orig, p);
	return p;
}

void addUnion(int p, int q)
{
	if ((p>numNodes) || (q>numNodes)) {
		printf("Illegal entry\n");
		return;
	}

	p = root(p);
	q = root(q);
	if (uf[p].size > uf[q].size) {
		// P-tree is larger.
		// Make q tree as a subset of p tree.
		uf[q].root = p;
		uf[p].size += uf[q].size;
	} else {
		uf[p].root = q;
		uf[q].size += uf[p].size;
	}
	return;
}

int isConnected(int p, int q)
{
	if (root(p) == root(q)) {
		return TRUE;
	}
	return FALSE;
}

#define MAXLEN 80
int main(int argc, char **argv)
{
	int conn, count, p, q;
	char str[MAXLEN], *s;
	char command;
	int keepReading = TRUE;

	do {
		//printf("Tell me what to do\n");
		scanf("%s", str);
		//printf("Scanned %s\n", str);
		sscanf(str, "%c:", &command);
		s = str+2;
		//printf("Command is %c\n", command);
		switch (command) {
			case 'T':
				sscanf(s, "%d\n", &count);
				createUF(count);
				break;
			case 'U':
				sscanf(s, "%d,%d\n", &p, &q);
				addUnion(p, q);
				break;
			case 'C':
				sscanf(s, "%d,%d\n", &p, &q);
				//printf("Check connection between %d and %d\n", p, q);
				conn = isConnected(p, q);
				if (conn) {
					printf("TRUE\n");
				} else {
					printf("FALSE\n");
				}
				fflush(stdout);
				break;
			case 'F':
			default:
				//printf("Quitting\n");
				keepReading = FALSE;
				break;
		}
	} while (keepReading);
}