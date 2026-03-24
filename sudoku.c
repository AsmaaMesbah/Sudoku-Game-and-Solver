#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"

typedef struct xTor {
	int x; // x coordinate of the cursor
	int r; // row index in the array
} xTor;
typedef struct yTor {
	int y; // y coordinate of the cursor
	int c; // column index in the array
} yToc; 

void readBoardfromFile(char* filename, int board[9][9]) {
	FILE* file = fopen(filename, "r"); 

	if (file == NULL) {
		fprintf(stderr, "Error opening file %s\n", filename); 
		exit(1); 
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (fscanf(file, "%d,", &board[i][j]) != 1) {
				fprintf(stderr, "Error reading board from file\n"); 
				fclose(file); 
				exit(1); 
			}
		}
	}

	printf("Done reading the board from %s\n", filename);
	fclose(file); 
}

void displayBoard(int board[9][9]) {
	for (int row = 0; row < 9; row++) {
		if (row % 3 == 0) {
			printf("+-----------------------+\n"); 
		}
		for (int col = 0; col < 9; col++) {
			if(col % 3 == 0) {
				printf("| "); 
			}
			if (board[row][col] == 0) {
				printf(". "); 
			}
			else {
				printf("%d ", board[row][col]); 
			}
			if(col == 8) {
				printf("|"); 
			}
		}
		printf("\n"); 
		if (row == 8) {
						printf("+-----------------------+\n"); 
		}
	}
}

int solve(int board[9][9]) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			if (board[r][c] == 0) {
				// if the cell is empty, try all numbers from 1 to 9
				for (int i = 1; i <= 9; i++) {
					if (isValid(board, r, c, i)) {
						// if the num is valid, store it in the array 
						board[r][c] = i;
						// recursively call solve to continue solving the board
						if(solve(board)) {
							return 1; // if the board is solved, return 1
						}
						board[r][c] = 0; // backtrack if the board is not solved
					}
				}
				return 0; // if no number is valid, return 0
			}
		}
	}
	// no empty cells, board is solved
	return 1; 
}

int isValid(int board[9][9], int row, int col, int num) {
	// Check if num is not in the current row or column
	for (int i = 0; i < 9; i++) {
		if (board[row][i] == num || board[i][col] == num) {
			return 0; // Not valid
		}
	}

	// check if num is not in the current 3x3 subgrid
	int startRow = (row / 3) * 3; // get the starting row of the 3x3 subgrid 
	int startCol = (col / 3) * 3; // get the starting column of the 3x3 subgrid
	for (int i = startRow; i < startRow + 3; i++) {
		for (int j = startCol; j < startCol + 3; j++) {
			if (board[i][j] == num) {
				return 0; // Not valid
			}
		}
	}
	return 1; // Valid
}

void saveBoardtoFile(char* filename, int board[9][9]) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Error opening file %s for writing\n", filename);
		exit(1);
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fprintf(file, "%d", board[i][j]);
			if (j < 8) {
				fprintf(file, ",");
			}
		}
		fprintf(file, "\n");
	}
	printf("Done saving the board to %s\n", filename);

	fclose(file);
}

void copyArray(int source[9][9], int destination[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			destination[i][j] = source[i][j];
		}
	}
}

void play(int* quit, int board[9][9], int source[9][9]) {
	static int x = 3, y = 2; // initial position of the cursor 
	moveTo(x, y);

	char input = getch();
	switch (input) {
	case 'w':
		y--; 
		if (y > 1 && y < 13) {
			// prevent moving out of bounds
			moveTo(x, y);
		}
		else {
			y++; // reset y to stay within bounds
		}
		break;
	case 'W':
		y--; 
		if (y > 1 && y < 13) {
			moveTo(x, y);
		}
		else {
			y++; // reset y to stay within bounds
		}
		break;
	case 's':
		y++; 
		if (y > 1 && y < 13) {
			moveTo(x, y);
		}
		else y--; // reset y to stay within bounds
		break;
	case 'S':
		y++;
		if (y > 1 && y < 13) {
			moveTo(x, y);
		}
		else y--; // reset y to stay within bounds
		break;
	case 'a':
		x--; 
		if (x > 2 && x < 24) {
			moveTo(x, y);
		}
		else x++; // reset x to stay within bounds
		break;
	case 'A':
		x--; 
		if (x > 2 && x < 24) {
			moveTo(x, y);
		}
		else x++; // reset x to stay within bounds
		break;
	case 'd':
		x++; 
		if (x > 2 && x < 24) {
			moveTo(x, y);
		}
		else x--; // reset x to stay within bounds
		break;
	case 'D':
		x++; 
		if (x > 2 && x < 24) {
			moveTo(x, y);
		}
		else x--; // reset x to stay within bounds
		break;
	case 'q':
		*quit = 1;
		return; // exit play immediately
		break;
	case 'Q': 
		*quit = 1;
		return; // exit play immediately
		break; 
	case '0':
	case '\b': // handle backspace
		place(board, source, x, y, 0); // clear the cell
		break; 
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		int num = input - '0'; // convert char to int
		place(board, source, x, y, num);
		if (Full(board)) {
			*quit = 2;
			return; // exit play immediately
		}
		moveTo(x, y);
		break;
	}
	}
}

void place(int board[9][9], int source[9][9], int x, int y, int num) {
	// Mapping table from screen positions to array indexes
	yToc yMap[] = {
		{2, 0}, {3, 1}, {4, 2}, {6, 3}, {7, 4}, {8, 5},
		{10, 6}, {11, 7}, {12, 8}
	};

	xTor xMap[] = {
		{3, 0}, {5, 1}, {7, 2}, {11, 3}, {13, 4}, {15, 5},
		{19, 6}, {21, 7}, {23, 8}
	};

	int rowIndex = -1, colIndex = -1;

	// Find the corresponding row and column index in the array
	for(int i = 0; i < 9; i++) {
		if (x == xMap[i].x) {
			colIndex = xMap[i].r; // get the column index from the mapping
		}
		if (y == yMap[i].y) {
			rowIndex = yMap[i].c; // get the row index from the mapping
		}
	}

	if (rowIndex == -1 || colIndex == -1) {
		return; // Invalid position
	}

	if(source[rowIndex][colIndex] != 0) {
		return; // Cannot change a pre-filled cell
	}


	board[rowIndex][colIndex] = num; 
	moveTo(1, 1); 
	displayBoard(board); 

}

int compare(int board1[9][9], int solved[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board1[i][j] != solved[i][j]) {
				return 0; // Boards are not equal
			}
		}
	}
	return 1; // Boards are equal
}

int Full(int board[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == 0) {
				return 0; // Found an empty cell
			}
		}
	}
	return 1; // No empty cells found
}

void displayInfo() {
	int x = 30, y = 3; // position for displaying info
	moveTo(x, y); 
	printf("Controls:\n"); 
	moveTo(x, y + 1);
	printf("W/S: Move Up/Down\n");
	moveTo(x, y + 2);
	printf("A/D: Move Left/Right\n");
	moveTo(x, y + 3);
	printf("0/backspace: Clear Cell\n");
	moveTo(x, y + 4);
	printf("1-9: Place Number\n");
	moveTo(x, y + 5);
	printf("Q: Quit Game\n");
}