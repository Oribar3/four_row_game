#include <stdio.h>
#include "../include/board.h"

void initBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void printBoard(int board[ROWS][COLS]) {
    printf("\n  0 1 2 3 4 5 6\n");
    printf("-----------------\n");
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == PLAYER1) printf("X|");
            else if (board[i][j] == PLAYER2) printf("O|");
            else printf(" |");
        }
        printf("\n");
    }
    printf("-----------------\n");
}

int getLowestEmptyRow(int board[ROWS][COLS], int col) {
    if (col < 0 || col >= COLS) return -1;
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == EMPTY) return i;
    }
    return -1;
}

int dropPiece(int board[ROWS][COLS], int col, int player) {
    int row = getLowestEmptyRow(board, col);
    if (row != -1) {
        board[row][col] = player;
        return 1;
    }
    return 0;
}

int checkWin(int board[ROWS][COLS], int player) {
    // אופקי
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i][j+1] == player && 
                board[i][j+2] == player && board[i][j+3] == player) return 1;
        }
    }
    // אנכי
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == player && board[i+1][j] == player && 
                board[i+2][j] == player && board[i+3][j] == player) return 1;
        }
    }
    // אלכסון יורד
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i+1][j+1] == player && 
                board[i+2][j+2] == player && board[i+3][j+3] == player) return 1;
        }
    }
    // אלכסון עולה
    for (int i = 3; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i-1][j+1] == player && 
                board[i-2][j+2] == player && board[i-3][j+3] == player) return 1;
        }
    }
    return 0;
}

int isBoardFull(int board[ROWS][COLS]) {
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == EMPTY) return 0;
    }
    return 1;
}