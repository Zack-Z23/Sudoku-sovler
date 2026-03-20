#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdio.h>
#include <stdlib.h>

extern int UNSOLVED;
extern int SIZE_ROWS;
extern int SIZE_COLUMNS;

typedef struct Soduku{
	struct Square *** squares;
	struct Box ** boxes;
} Soduku;


typedef struct Box{

	struct Square ** squares;
	int numbers;
	int possible[9];
	int solvable;
	struct Box * next;


}Box;

typedef struct Square
{
	int number;
	/*[1][1][1][1][1][0	][1][1][1]
	  [9][8][7][6][5][4][3][2][1] index*/
	int possible[9];
	int solvable;	
	Box * box;
	int row;
	int column;


} Square;

int** createPuzzle();
void printPuzzle(Square *** puzzle);
Soduku * setUpPuzzle(int ** puzzle);

Soduku * createSoduku(Square *** puzzle, Box ** boxes);

int checkPuzzle(Square *** soduku, Box ** boxes);

int updateSoduku(Square *** soduku, int row, int column);

int solvedSquare(Square* square);


/*Box functions*/
Box ** createBoxes();

int updateBoxes(Square *** soduku, int row, int column);
int boxSingles(Square *** soduku, Box ** boxes);

int checkRows(Square *** soduku, Box ** boxes);
#endif