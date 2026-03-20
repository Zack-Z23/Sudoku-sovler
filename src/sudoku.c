
#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;
int main ()
{
	int ** puzzle;
	int progress;
	Soduku * soduku;

	puzzle = createPuzzle();

	soduku = setUpPuzzle(puzzle);

	printPuzzle(soduku->squares);
	while(UNSOLVED > 0 ){
		progress = checkPuzzle(soduku->squares, soduku->boxes);

		if(progress == 0){
			printf("didnt solve");
			break;
		}
	}
	printf("\n\n");

	printPuzzle(soduku->squares);


	return 0;
}