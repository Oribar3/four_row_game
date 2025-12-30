#include <stdio.h>
#include "../include/board.h"

/**
 * מאתחלת את לוח המשחק לערך ריק.
 * הפונקציה עוברת על כל התאים במערך הדו-ממדי ומאפסת אותם לערך EMPTY (0).
 */
void initBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = EMPTY;
        }
    }
}

/**
 * מדפיסה את הלוח למסך בצורה ויזואלית (ממשק ASCII).
 * הפונקציה מוסיפה מספרי עמודות מעל הלוח לנוחות המשתמש ומפרידה בין התאים בעזרת קווים.
 */
void printBoard(int board[ROWS][COLS]) {
    printf("\n  0 1 2 3 4 5 6\n");
    printf("-----------------\n");
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == PLAYER1) printf("X|"); // שחקן 1 מיוצג ב-X
            else if (board[i][j] == PLAYER2) printf("O|"); // שחקן 2 מיוצג ב-O
            else printf(" |"); // תא ריק
        }
        printf("\n");
    }
    printf("-----------------\n");
}

/**
 * מחפשת את המיקום הפנוי הנמוך ביותר בעמודה נתונה.
 * הפונקציה סורקת את העמודה מלמטה למעלה (מהשורה ה-5 ל-0) ומחזירה את אינדקס השורה הפנויה.
 */
int getLowestEmptyRow(int board[ROWS][COLS], int col) {
    if (col < 0 || col >= COLS) return -1; // בדיקת חריגה מגבולות העמודות
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == EMPTY) return i;
    }
    return -1; // העמודה מלאה
}

/**
 * מכניסה דסקית ללוח בעמודה שנבחרה.
 * הפונקציה משתמשת ב-getLowestEmptyRow כדי למצוא מקום פנוי ומעדכנת את המערך בערך השחקן.
 */
int dropPiece(int board[ROWS][COLS], int col, int player) {
    int row = getLowestEmptyRow(board, col);
    if (row != -1) {
        board[row][col] = player;
        return 1; // הצלחה
    }
    return 0; // כישלון (עמודה מלאה)
}

/**
 * בודקת האם קיים רצף מנצח של 4 דסקיות עבור השחקן.
 * הסריקה מתבצעת בארבעה כיוונים: אופקי, אנכי, אלכסון יורד ואלכסון עולה.
 */
int checkWin(int board[ROWS][COLS], int player) {
    // בדיקה אופקית
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i][j+1] == player && 
                board[i][j+2] == player && board[i][j+3] == player) return 1;
        }
    }
    // בדיקה אנכית
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == player && board[i+1][j] == player && 
                board[i+2][j] == player && board[i+3][j] == player) return 1;
        }
    }
    // אלכסון יורד (\)
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i+1][j+1] == player && 
                board[i+2][j+2] == player && board[i+3][j+3] == player) return 1;
        }
    }
    // אלכסון עולה (/)
    for (int i = 3; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i-1][j+1] == player && 
                board[i-2][j+2] == player && board[i-3][j+3] == player) return 1;
        }
    }
    return 0;
}

/**
 * בודקת האם לוח המשחק מלא לחלוטין (מצב תיקו).
 * אם השורה העליונה (0) מלאה בכל העמודות, המשחק מסתיים ללא מנצח.
 */
int isBoardFull(int board[ROWS][COLS]) {
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == EMPTY) return 0;
    }
    return 1;
}