#include <stdlib.h>
#include <limits.h>
#include "../include/ai.h"
#include "../include/board.h"

/**
 * רמה קלה: מהלכים אקראיים.
 * המחשב בוחר עמודה באקראי עד שהוא מוצא עמודה שיש בה מקום פנוי.
 */
int getEasyMove(int board[ROWS][COLS]) {
    int col;
    do { 
        col = rand() % COLS; // בחירת עמודה אקראית בין 0 ל-6
    } while (getLowestEmptyRow(board, col) == -1);
    return col;
}

/**
 * רמה בינונית: אסטרטגיה בסיסית של חסימה וניצחון.
 * המחשב בודק אם הוא יכול לנצח במהלך אחד, ואם לא - הוא בודק אם עליו לחסום את היריב.
 */
int getMediumMove(int board[ROWS][COLS], int computerPlayer) {
    int opponent = (computerPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    for (int j = 0; j < COLS; j++) {
        int row = getLowestEmptyRow(board, j);
        if (row != -1) {
            // האם המחשב מנצח פה?
            board[row][j] = computerPlayer;
            if (checkWin(board, computerPlayer)) { board[row][j] = EMPTY; return j; }
            // האם היריב ינצח פה? (צורך לחסום)
            board[row][j] = opponent;
            if (checkWin(board, opponent)) { board[row][j] = EMPTY; return j; }
            board[row][j] = EMPTY;
        }
    }
    return getEasyMove(board);
}

/**
 * אלגוריתם Minimax: אסטרטגיה מתקדמת (בונוס).
 * אלגוריתם רקורסיבי המדמה מהלכים קדימה כדי לקבוע את הציון הטוב ביותר ללוח.
 * משתמש ב-Backtracking כדי לבחון מצבים עתידיים מבלי לשנות את הלוח בפועל.
 */
int minimax(int board[ROWS][COLS], int depth, int isMaximizing, int player) {
    int opponent = (player == PLAYER1) ? PLAYER2 : PLAYER1;
    if (checkWin(board, player)) return 100 + depth;
    if (checkWin(board, opponent)) return -100 - depth;
    if (isBoardFull(board) || depth == 0) return 0;

    if (isMaximizing) {
        int best = INT_MIN;
        for (int j = 0; j < COLS; j++) {
            int row = getLowestEmptyRow(board, j);
            if (row != -1) {
                board[row][j] = player;
                int score = minimax(board, depth - 1, 0, player);
                board[row][j] = EMPTY;
                if (score > best) best = score;
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int j = 0; j < COLS; j++) {
            int row = getLowestEmptyRow(board, j);
            if (row != -1) {
                board[row][j] = opponent;
                int score = minimax(board, depth - 1, 1, player);
                board[row][j] = EMPTY;
                if (score < best) best = score;
            }
        }
        return best;
    }
}

/**
 * רמה קשה: שימוש ב-Minimax.
 * מפעילה את האלגוריתם הרקורסיבי בעומק 5 כדי לבחור את העמודה הטובה ביותר.
 */
int getHardMove(int board[ROWS][COLS], int computerPlayer) {
    int bestScore = INT_MIN, bestCol = 0;
    for (int j = 0; j < COLS; j++) {
        int row = getLowestEmptyRow(board, j);
        if (row != -1) {
            board[row][j] = computerPlayer;
            int score = minimax(board, 5, 0, computerPlayer);
            board[row][j] = EMPTY;
            if (score > bestScore) { bestScore = score; bestCol = j; }
        }
    }
    return bestCol;
}