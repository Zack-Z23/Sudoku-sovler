#include "sudoku.h"


Soduku * createSoduku(Square *** squares, Box ** boxes){
	Soduku * soduku;
	soduku = malloc(sizeof(Soduku));

	soduku->squares = squares;
	soduku->boxes = boxes;

	return soduku;
}


Soduku * setUpPuzzle(int ** puzzle){
	Square *** soduku;
	Box ** boxes; 
	int i, j, x;
	int currentBox = 0;


	soduku = (Square***)malloc(sizeof(Square***) * 9);
	boxes = createBoxes();


	for(i = 0; i < SIZE_ROWS; i++){
		soduku[i] = (Square**)malloc(sizeof(Square*)*9);
		for(j = 0; j < SIZE_COLUMNS; j++){
			soduku[i][j] = (Square*)malloc(sizeof(Square)*9);

			soduku[i][j] -> number = puzzle[i][j];

			soduku[i][j] -> row = i;

			soduku[i][j] -> column = j;

			soduku[i][j] -> solvable = 9;

			boxes[currentBox]->squares[boxes[currentBox]->numbers] = soduku[i][j];
			
			soduku[i][j]->box = boxes[currentBox];

			boxes[currentBox]->numbers++;



			for(x  = 0; x < SIZE_ROWS; x++){
				soduku[i][j]->possible[x] = 0;
				
			}
			if(j == 2)
				currentBox++;

			
			if(j == 5)
				currentBox++;
			


		}
		currentBox -= 2;
		if( i == 2)
		{
			currentBox = 3;
		}
		if( i == 5){
			currentBox = 6;
		}
	}

	for(i = 0; i < SIZE_ROWS; i++){
		for(j = 0; j < SIZE_COLUMNS; j++){
			if(soduku[i][j]->number != 0){
				soduku[i][j]-> solvable = 0;
				updateSoduku(soduku, i, j);
				updateBoxes(soduku, i ,j);
				UNSOLVED--;
			}
		}
	}
	return createSoduku(soduku, boxes);

}
int updateSoduku(Square *** soduku, int row, int column){
	int x;
	int number = soduku[row][column]->number;

	for(x = 0; x < SIZE_ROWS; x++){
		if(soduku[x][column]->possible[number - 1] == 0){
			soduku[x][column] -> solvable--;

		}
		soduku[x][column] -> possible[number -1] =1;
	}
	for(x = 0; x < SIZE_COLUMNS; x++){
		if(soduku[row][x]->possible[number - 1] == 0){
			soduku[row][x] -> solvable--;
		}
		soduku[row][x] -> possible[number -1] =1;
	}
	return 1;
}

int checkPuzzle(Square *** soduku, Box ** boxes){
	int i, j, x;
	for(i = 0; i < SIZE_ROWS; i++){

		for(j = 0; j < SIZE_COLUMNS; j++){
			if(soduku[i][j]->solvable == 1){
				solvedSquare(soduku[i][j]);
				updateSoduku(soduku, i, j);
				updateBoxes(soduku, i, j);

				return 1;
			}	
		}
	}

	if(boxSingles(soduku, boxes)){
		return 1;
	}

	return checkRows(soduku, boxes);

} 


int ** createPuzzle(){
	int ** puzzle;
	int i, j;

	int array[9][9] = {0,1,9,	0,0,2,	0,0,0,
					   4,7,0, 	6,9,0, 	0,0,1,
					   0,0,0,  	4,0,0, 	0,9,0,

					   8,9,4,    5,0,7,   0,0,0,
					   0,0,0,    0,0,0,   0,0,0,
					   0,0,0,    2,0,1,   9,5,8,
					   
					   0,5,0,    0,0,6,   0,0,0,
					   6,0,0,    0,2,8,   0,7,9,
					   0,0,0,    1,0,0,   8,6,0};
puzzle = (int**)malloc(sizeof(int*)*9);

for(i = 0; i < SIZE_ROWS; i++){
	puzzle[i] = (int*)malloc(sizeof(int)*9);

	for(j = 0; j < SIZE_COLUMNS; j++){
		puzzle[i][j] = array[i][j];
	}
}

return puzzle;

}

void printPuzzle (Square*** puzzle){
	int i, j;
	printf("------------------------------------\n");
	for(i = 0; i < SIZE_ROWS; i++){
		printf("|");
		/*print each rows*/
		for(j = 0; j< SIZE_COLUMNS; j++){
			printf(" %d ", puzzle[i][j]->number);
			if((j + 1) % 3 ==  0){
				printf("|");
			}
		}
		printf("\n");
		if( (i+1) % 3 == 0){
			printf("------------------------------------\n");
		}

	}
	
}
