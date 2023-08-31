#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define GRID_SIZE 9

int loadBoard (const char *path, int sudoku[GRID_SIZE][GRID_SIZE]) {
	FILE *file = fopen(path, "r");
	
	if (!file)
		return 0;
	
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			fscanf(file, "%d", &sudoku[i][j]);
		}
	}
	
	fclose(file);
	
	return 1;
}

void printSudoku(int sudoku[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}

int isSafe(int sudoku[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
    for (int i = 0; i < GRID_SIZE; i++) {
        if (sudoku[row][i] == num || sudoku[i][col] == num) {
            return FALSE;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[i + startRow][j + startCol] == num) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

int solveSudoku(int sudoku[GRID_SIZE][GRID_SIZE]) {
    //system("clear");
    //printSudoku(sudoku);
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (sudoku[row][col] == 0) {
                for (int num = 1; num <= GRID_SIZE; num++) {
                    if (isSafe(sudoku, row, col, num)) {
                        sudoku[row][col] = num;
                        if (solveSudoku(sudoku)) {
                            return TRUE;
                        }
                        sudoku[row][col] = 0;
                    }
                }
                return FALSE;
            }
        }
    }
    return TRUE;
}

int main(void) {
    int sudoku_board[GRID_SIZE][GRID_SIZE];
    loadBoard("sudoku_sample_easy.txt", sudoku_board);
    printf("[Board loaded]\n");

    printf("Solving puzzle...\n\n");

    clock_t start_time = clock();

    int ret_solve = solveSudoku(sudoku_board);

    clock_t end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    if (!ret_solve)
        printf("No possible solution!\n");
    else
        printSudoku(sudoku_board);

    printf("\nTime taken: %.6f seconds\n", time_taken);

    return EXIT_SUCCESS;
}
