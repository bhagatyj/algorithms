#include <stdio.h>
#include "sll.h"

int main (int argc, char **argv) 
{
	sllList * newSll = createSll();
	printf("Hello world %p\n", newSll);
}

