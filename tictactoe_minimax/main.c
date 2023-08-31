#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char board[3][3];

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j != 2) printf("|");
        }
        if (i != 2) printf("\n---+---+---\n");
        else printf("\n");
    }
}

char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
            return board[0][j];
    }

    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
        return board[1][1];

    return ' ';
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

int minimax(bool isMaximizing) {
    char winner = checkWinner();

    if (winner == 'X') return -1; // Jogador X (humano) vence
    if (winner == 'O') return 1;  // Jogador O (IA) vence
    if (isBoardFull()) return 0;  // Empate

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(false);
                    board[i][j] = ' ';
                    bestScore = (score > bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(true);
                    board[i][j] = ' ';
                    bestScore = (score < bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
}

void performAIMove() {
    int bestScore = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }

    board[bestMoveRow][bestMoveCol] = 'O';
}

int main() {
    initializeBoard();
    int currentPlayer = 0;
    int totalMoves = 0;

    while (true) {
        system("clear");
        printf("Bem-vindo ao Jogo da Velha!\n");
        printf("Jogador 1: X\n");
        printf("Jogador 2: O (IA)\n");
        printBoard();

        if (currentPlayer == 1) {
            int row, col;
            printf("Jogador %d, entre com a linha (0-2) e coluna (0-2) da sua jogada: ", currentPlayer);
            scanf("%d %d", &row, &col);

            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
                printf("Jogada inválida! Tente novamente.\n");
                continue;
            }

            board[row][col] = 'X';
        } else {
            performAIMove();
        }

        totalMoves++;
        char winner = checkWinner();

        if (winner != ' ' || totalMoves == 9) {
            system("clear");
            printBoard();
            if (winner != ' ') {
                printf("Jogador %d venceu!\n", (winner == 'X') ? 1 : 2);
            } else {
                printf("Empate!\n");
            }
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    return 0;
}
