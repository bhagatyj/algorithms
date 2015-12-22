#include "sLStore.h"

int main (int argc, char **argv) {
	SLStore myLinkStore;

	myLinkStore.add( 1, "Hello");
	myLinkStore.add( 2, "World");
	myLinkStore.add(3, "Now");
	myLinkStore.remove(2);

	myLinkStore.print();
}