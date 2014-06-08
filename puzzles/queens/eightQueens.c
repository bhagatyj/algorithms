/*
  Eight Queens to be placed in a Chess board so that they can not
  cut each other.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Define markers for the queen positions.
 * FREE  --> Position is empty.
 * QUEEN --> QUEEN has been placed in this position.
 * CUTPOS -> This position is compromised. Queens cannot be 
 *           placed here. 
 */

#define QUEEN 1
#define CUTPOS 2
#define FREE 0

int numSolution = 0;
/*
 * Utility for printing the chess board onto the screen
 */
void printChessboard(int **chessboard)
{
	int i, j;
	printf("----\n");
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j ++) {
			printf("%4s", (chessboard[i][j] == QUEEN ? "Q" : "."));
		}
		printf("\n");
	}
	printf("----\n");
}

void addToSolutionList(int **chessboard)
{
	numSolution++;
	printf("----Solution %d ----\n", numSolution);
	printChessboard(chessboard);
}

void resetEffects(int **chessboard)
{
	int i, j;
	for (i=0; i<8; i++) {
		for (j=0; j<8; j++) {
			if (chessboard[i][j] == CUTPOS) {
				chessboard[i][j] = FREE;
			}
		}
	}
}

void checkAndWriteEffect(int row, int col, int queenX, int queenY, int **chessboard)
{
	// If the row/col has been marked, dont change it.
	if (chessboard[row][col]) {
		return;
	}
	if (row == queenX) {
		chessboard[row][col] = CUTPOS;
	}
	if (col == queenY) {
		chessboard[row][col] = CUTPOS;
	}
	if (abs(row-queenX) == abs(col-queenY)) {
		chessboard[row][col] = CUTPOS;
	}
}

void writePositionEffect(int **chessboard)
{
	int i, j, row, col;
	for (i=0; i<8; i++) {
		for (j=0; j<8; j++) {
			if (chessboard[i][j] == QUEEN) {
				// Found a Queen.
				// Now process its effects.
				for (row=0; row<8; row++) {
					for (col=0; col<8; col++) {
						checkAndWriteEffect(row, col, i, j, chessboard);
					}
				}
			}
		}
	}
}

void writePosition(int row, int col, int **chessboard)
{
	chessboard[row][col] = QUEEN;
	writePositionEffect(chessboard);
	//printf("Just filled row %d and col %d\n", row, col);
	//printChessboard(chessboard);
}

void erasePosition(int row, int col, int **chessboard)
{
	chessboard[row][col] = FREE;
	resetEffects(chessboard);
	writePositionEffect(chessboard);
}

void fillRow(int row, int** chessboard);

void fillPosition(int row, int col, int **chessboard)
{
	writePosition(row, col, chessboard);
	if (row == 7) {
		addToSolutionList(chessboard);
	} else {
		//printf("On to Row %d\n", row+1);
		fillRow(row+1, chessboard);
	}
}

void fillRow(int row, int **chessboard)
{
	int col;
	int choices[8];

	for (col=0; col < 8; col++) {
		if (chessboard[row][col] == FREE) {
			fillPosition(row, col, chessboard);
			//printf("Going back row %d col %d\n", row, col);
			erasePosition(row, col, chessboard);
		}
	}
	//printf("Exhausted options on row %d\n", row);
}

int main(int argc, char **argv)
{
	int **chessboard, row;
	chessboard = (int **)malloc(8*sizeof(int *));
	for (row = 0; row < 8; row++) {
		chessboard[row] = (int *)malloc(8*sizeof(int));
		memset(chessboard[row], 0, 8*sizeof(int));
	}
	//addToSolutionList(chessboard);
	fillRow(0, chessboard);
}
