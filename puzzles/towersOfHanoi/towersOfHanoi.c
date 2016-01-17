// Implement an algorithm for Towers of Hanoii problem

#include <stdio.h>

void 
move( int numDiscs, char src, char dst, char spare )
{

	if ( numDiscs == 1 ) {
		printf("Move disc %d from %c to %c\n", numDiscs, src, dst);
		return;
	}

	move( numDiscs-1, src, spare, dst );
	printf("Move disc %d from %c to %c\n", numDiscs, src, dst);
	move( numDiscs-1, spare, dst, src );
}

int main(int argc, char **argv) {
	printf("\n\nSolution for 3 discs..\n");
	move( 3, 'a', 'b', 'c' );

	printf("\n\nSolution for 5 discs..\n");
	move( 5, 'a', 'b', 'c' );
	return 0;
}




