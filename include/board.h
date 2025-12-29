#ifndef BOARD_H
#define BOARD_H

// הגדרת קבועים לפי דרישות המטלה
#define ROWS 6
#define COLS 7
#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

// חתימות פונקציות לניהול הלוח
void initBoard(int board[ROWS][COLS]);
void printBoard(int board[ROWS][COLS]);
int checkWin(int board[ROWS][COLS], int player);
int isBoardFull(int board[ROWS][COLS]);
int dropPiece(int board[ROWS][COLS], int col, int player);
int getLowestEmptyRow(int board[ROWS][COLS], int col);

#endif