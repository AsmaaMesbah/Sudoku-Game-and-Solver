#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"
#define STR_MAX 256

int main(void) {
	// read sudoku board from file and store in an array 
	char filename[STR_MAX]; 
	printf("Enter the filename of the sudoku board: "); 
	scanf("%s", filename); getchar(); // consume the newline character left by scanf
	int board[9][9]; 
	int solvedBoard[9][9]; // to store the solved board
	int playBoard[9][9]; // to store the board for playing
	readBoardfromFile(filename, board); 

	copyArray(board, solvedBoard); // copy the original board to solvedBoard

	// solve sudoku board 
	if (solve(solvedBoard)) {
		printf("The board has a solution.\n");
	}
	else {
		printf("No solution exists for the given Sudoku board.\n");
		return 1; // Exit if no solution is found
	}

	// save solved sudoku board to file 
	char saveFilename[STR_MAX] = "solved_";
	strcat(saveFilename, filename);
	saveBoardtoFile(saveFilename, solvedBoard);

	printf("Click any key to start playing...\n");
	getchar(); // wait for user input to continue

	// display unsolved sudoku board (from array) 
	printf("\033[2J"); // clear the console
	moveTo(1, 1);  // move cursor to top left corner
	displayBoard(board); 
	displayInfo(); // display controls and info

	copyArray(board, playBoard); 
	
	int quit = 0; int ply = 1; // to track if the user wants to quit 
		
	while(1){
		while (ply) {
			play(&quit, playBoard, board); // play the game
			if (quit == 1) {
				printf("\033[2J"); // clear the console
				printf("Exiting the game. Goodbye!\n");
				return 0; // exit play loop if quit is set
			}
			else if (quit == 2) {
				ply = 0; // set play to 0 to end the game and check the solution
			}
		}

		printf("\033[2J"); // clear the console again
		if (compare(playBoard, solvedBoard)) {
			printf("Correct! You won.\n");
			return 0; // Exit successfully
		}
		else {
			printf("Wrong! Try again.\n");
			printf("Click any key to play again...\n");
			getchar(); getchar();  // wait for user input to continue
			quit = 0; // reset quit to allow playing again
			ply = 1; // reset play to allow playing again
			printf("\033[2J"); // clear the console
			moveTo(1, 1);  // move cursor to top left corner
			displayBoard(board);
			displayInfo(); // display controls and info again
			copyArray(board, playBoard); // reset the play board to the original board
		}
	}

	// displayBoard(solvedBoard); 

	return 0; 
}