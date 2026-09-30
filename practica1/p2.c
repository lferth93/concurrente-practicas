#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define N 9

void printSudoku(int sudoku[N][N]) {
    printf("╔═════╦═════╦═════╗\n");
    for (int i = 0; i < N; i++) {
        if (i%3 == 1 || i%3 == 2) {
            printf("║─┼─┼─║─┼─┼─║─┼─┼─║\n");
        } else if (i != 0) {
            printf("╠═════╬═════╬═════╣\n");
        }
        for (int j = 0; j < N; j++) {
            if (j%3 == 1 || j%3 == 2) {
                printf("│");
            } else {
                printf("║");
            }
            if (sudoku[i][j] != 0) {
                printf("%d", sudoku[i][j]);
            } else {
                printf(" ");
            }
        }
        printf("║\n");
    }
    printf("╚═════╩═════╩═════╝\n");
}

int sudoku[N][N] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

// Función para verificar si es posible colocar un número en una celda
bool esSeguro(int sudoku[N][N], int fila, int col, int num) {
    // Verificacion de fila y columna
    for (int i = 0; i < N; i++) {
        if (sudoku[fila][i] == num || sudoku[i][col] == num) {
            return false;
        }
    }

    // Verificacion de bloque 3x3
    int it = fila - fila % 3;
    int jt = col - col % 3;
    for (int i = it; i < it + 3; i++) {
        for (int j = jt; j < jt + 3; j++) {
            if (sudoku[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}

// Función para resolver el sudoku usando backtracking
bool resolverSudoku(int sudoku[N][N]){
    bool encontrado = false;
    int fila = 0;
    int col = 0;

    // Busca una celda vacia en el sudoku 
    for (fila = 0; fila < N; fila++) {
        for (col = 0; col < N; col++) {
            if (sudoku[fila][col] == 0) {
                encontrado = true;
                break;
            }
        }
        if (encontrado) {
            break;
        }
    }

    if (!encontrado) {
        return true; // Sudoku resuelto
    }

    for (int num = 1; num <= 9; num++) {
        if (esSeguro(sudoku, fila, col, num)) {
            sudoku[fila][col] = num;
            if (resolverSudoku(sudoku)) {
                return true;
            }
            sudoku[fila][col] = 0;
        }
    }

    return false;
}


int main() {
    printf("\xF0\x9F\x94\xB9 Sudoku inicial:\n");
    printSudoku(sudoku);

    if (resolverSudoku(sudoku)) {
        printf("\n\xE2\x9C\x85 Solución del sudoku:\n");
        printSudoku(sudoku);
    } else {
        printf("\n\xE2\x9D\x8CNo se pudo resolver el Sudoku.\n");
    }

    return 0;
}