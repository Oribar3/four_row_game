#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/board.h"
#include "../include/ai.h"

void playGame(int mode) {
    int board[ROWS][COLS];
    initBoard(board);
    int currentPlayer = PLAYER1, win = 0, col;
    srand(time(NULL));

    while (!win && !isBoardFull(board)) {
        printBoard(board);
        if (currentPlayer == PLAYER1) {
            printf("Your turn (0-6): ");
            fflush(stdout);
            if (scanf("%d", &col) != 1) { while(getchar() != '\n'); continue; }
        } else {
            if (mode == 1) {
                printf("Player 2 turn (0-6): ");
                fflush(stdout);
                if (scanf("%d", &col) != 1) { while(getchar() != '\n'); continue; }
            } else {
                if (mode == 2) col = getEasyMove(board);
                else if (mode == 3) col = getMediumMove(board, PLAYER2);
                else col = getHardMove(board, PLAYER2);
                printf("Computer chose column %d\n", col);
            }
        }

        if (dropPiece(board, col, currentPlayer)) {
            if (checkWin(board, currentPlayer)) {
                win = 1;
                printBoard(board);
                printf("Player %d Wins!\n", currentPlayer);
            } else currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
        }
    }
    if (!win) printf("It's a tie!\n");
}

int main() {
    int choice = 0;
    while (choice != 5) {
        printf("\n1. PvP\n2. Easy\n3. Medium\n4. Hard (Minimax)\n5. Exit\nChoice: ");
        fflush(stdout);
        if (scanf("%d", &choice) != 1) { while(getchar() != '\n'); continue; }
        if (choice >= 1 && choice <= 4) playGame(choice);
    }
    return 0;
}