#include "sudoku.h"

int checkRows(Square *** soduku, Box ** boxes){
	//Stupid penis
	printf("This runs like stupid");
	int i , j , k;

	int sum[9];

	int place[9];
	//all rows loop
	for(i = 0; i < 9; i++){

		//Initialize sum to zero
		for(j = 0; j < 9; j++){
			place[j] = 0;
			sum[j] = 0;
		}

		// each square in row loop
		for(j = 0; j < 9; j++){
		
			if(soduku[i][j]->number != 0){
				continue;
			}
			//each square all possibles
			for(k = 0; k < 9; k++){	
				//check number (k) possible
				if(soduku[i][j]->possible[k] == 0){
					sum[k]++;
					place[k] = j;
				}

			}
		}
	
	for(k = 0; k < 9; k++){
		if(sum[k] == 1){
			soduku[i][place[k]]->number = k + 1;
			soduku[i][place[k]]->solvable = 0;
			UNSOLVED--;

			updateSoduku(soduku, i, place[k]);

			updateBoxes(soduku, i, place[k]);

			return 1;
			
		}
	}
}
	return 0;
}