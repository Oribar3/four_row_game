#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/board.h"
#include "../include/ai.h"

/**
 * מנהלת את מהלך המשחק מקצה לקצה.
 * הפונקציה מנהלת את התורות, מקבלת קלט (מהמשתמש או מה-AI), בודקת ניצחון ומדפיסה הודעות סיום.
 * שינוי: הפונקציה מחזירה כעת int המייצג את המנצח (1 לשחקן 1, 2 לשחקן 2/מחשב, 0 לתיקו).
 */
int playGame(int mode) {
    int board[ROWS][COLS];
    initBoard(board);
    int currentPlayer = PLAYER1, win = 0, col;
    srand(time(NULL)); // אתחול מחולל מספרים אקראיים

    while (!win && !isBoardFull(board)) {
        printBoard(board);
        if (currentPlayer == PLAYER1) {
            printf("Your turn (0-6): ");
            fflush(stdout); // ניקוי באפר הפלט להצגת הודעה מיידית
            if (scanf("%d", &col) != 1) { 
                while(getchar() != '\n') { } 
                continue; 
            }
        } else {
            // ניהול תור היריב בהתאם למצב שנבחר (PvP או רמות קושי שונות)
            switch (mode) {
                case 1: // מצב שחקן נגד שחקן (PvP)
                    printf("Player 2 turn (0-6): ");
                    fflush(stdout);
                    // בדיקת קלט תקין וניקוי הבאפר במקרה של טעות
                    if (scanf("%d", &col) != 1) { 
                        while(getchar() != '\n') { } 
                        continue; // חזרה לתחילת לולאת ה-while של המשחק
                    }
                    break;

                case 2: // מחשב - רמה קלה
                    col = getEasyMove(board);
                    printf("Computer chose column %d\n", col);
                    break;

                case 3: // מחשב - רמה בינונית
                    col = getMediumMove(board, PLAYER2);
                    printf("Computer chose column %d\n", col);
                    break;

                case 4: // מחשב - רמה קשה (Minimax)
                    col = getHardMove(board, PLAYER2);
                    printf("Computer chose column %d\n", col);
                    break;
                    
                default:
                    // מקרה הגנה למקרה של מצב לא מוכר
                    continue;
            }
        }

        // ביצוע המהלך ובדיקת ניצחון
        if (dropPiece(board, col, currentPlayer)) {
            if (checkWin(board, currentPlayer)) {
                win = 1;
                printBoard(board);
                printf("Player %d Wins!\n", currentPlayer);
                return currentPlayer; // החזרת מספר השחקן שניצח לעדכון סטטיסטיקה
            } else {
                currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
            }
        }
    }
    
    if (!win) {
        printf("It's a tie!\n"); // סיום המשחק ללא מנצח
        return 0; // החזרת 0 במקרה של תיקו
    }
    return 0;
}

/**
 * נקודת הכניסה של התוכנית.
 * מציגה תפריט ראשי ממוספר המאפשר בחירת מצבי משחק, צפייה בסטטיסטיקה או יציאה.
 */
int main() {
    int choice = 0;
    
    // משתנים לשמירת סטטיסטיקת המשחקים (לא מתאפסים בין משחקים)
    int p1_wins = 0;
    int p2_wins = 0;
    int ties = 0;

    while (choice != 6) { // אופציה 6 היא כעת יציאה
        printf("\n======= CONNECT FOUR =======\n");
        printf("1. PvP (Player vs Player)\n");
        printf("2. Easy AI\n");
        printf("3. Medium AI\n");
        printf("4. Hard AI (Minimax)\n");
        printf("5. View Statistics\n"); // הצגת הניקוד המצטבר
        printf("6. Exit\n");
        printf("Choice: ");
        fflush(stdout);
        
        if (scanf("%d", &choice) != 1) { 
            while(getchar() != '\n') { } 
            continue; 
        }
        
        // בחירה במצב משחק
        if (choice >= 1 && choice <= 4) {
            int result = playGame(choice);
            // עדכון המונים לפי תוצאת המשחק שחזרה
            if (result == 1) p1_wins++;
            else if (result == 2) p2_wins++;
            else ties++;
        } 
        // הצגת סטטיסטיקה
        else if (choice == 5) {
            printf("\n--- GAME STATISTICS ---\n");
            printf("Player 1 Wins: %d\n", p1_wins);
            printf("Player 2 / Computer Wins: %d\n", p2_wins);
            printf("Ties: %d\n", ties);
            printf("Total Games Played: %d\n", p1_wins + p2_wins + ties);
            printf("-----------------------\n");
        }
    }
    printf("Goodbye!\n");
    return 0;
}