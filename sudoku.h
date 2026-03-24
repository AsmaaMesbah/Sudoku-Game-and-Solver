#pragma once

#define moveTo(x, y) printf("\033[%d;%dH", (y), (x))

void readBoardfromFile(char* filename, int board[9][9]); 
void displayBoard(int board[9][9]); 
int solve(int board[9][9]);
static int isValid(int board[9][9], int row, int col, int num);
void saveBoardtoFile(char* filename, int board[9][9]); 
void copyArray(int source[9][9], int destination[9][9]);
void play(int *quit, int board[9][9], int source [9][9]);
static void place(int board[9][9], int source[9][9], int x, int y, int num); 
int compare(int board1[9][9], int solved[9][9]); 
static int Full(int board[9][9]); 
void displayInfo(); 