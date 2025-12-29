#ifndef AI_H
#define AI_H

#include "board.h"

int getEasyMove(int board[ROWS][COLS]);
int getMediumMove(int board[ROWS][COLS], int computerPlayer);
int getHardMove(int board[ROWS][COLS], int computerPlayer); // רמת בונוס

#endif