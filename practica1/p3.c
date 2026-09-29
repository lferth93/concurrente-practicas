#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>

#define N 9
#define Z 5

void generarSudoku(int sudoku[N][N]);
void printSudoku(int sudoku[N][N]);
bool esSeguro(int sudoku[N][N], int fila, int col, int num);
bool resolverSudoku(int sudoku[N][N]);

int sudoku[Z][N][N];

int valido[N][N] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9},
    {4, 5, 6, 7, 8, 9, 1, 2, 3},
    {7, 8, 9, 1, 2, 3, 4, 5, 6},
    {2, 3, 4, 5, 6, 7, 8, 9, 1},
    {5, 6, 7, 8, 9, 1, 2, 3, 4},
    {8, 9, 1, 2, 3, 4, 5, 6, 7},
    {3, 4, 5, 6, 7, 8, 9, 1, 2},
    {6, 7, 8, 9, 1, 2, 3, 4 ,5},
    {9 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8}
};

int perm[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

// Funcion para mezclar usando el algoritmo de Fisher-Yates
void shuffle(int perm[N]){
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = perm[i];
        perm[i] = perm[j];
        perm[j] = temp;
    }
}

// Genera un sudoku aleatorio
// Para generar el sudoku se parte de un tablero completo valido
// y se aplica una permutación aleatoria a los números del 1 al 9, luego
// se intercambian filas y columnas dentro del mismo bloque
// de forma aleatoria y se eliminan algunos números con probabilidad 1/2.
// Esto asegura que el sudoku generado sea valido pero no que tenga solución única.
void generarSudoku(int sudoku[N][N]) {
    srand(time(NULL));

    shuffle(perm);

    // Copia el tablero valido al sudoku y aplica la permutación
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sudoku[i][j] = perm[valido[i][j]-1]+1;
        }
    }

    // Hace un intercambio de filas por cada bloque 
    for(int i = 0; i < 3; i++) {
        int fila1 = rand() % 3;
        int fila2 = (fila1 + (rand() % 2) +1) % 3;
        for (int j = 0; j < N; j++) {
            int temp = sudoku[fila1][j];
            sudoku[fila1][j] = sudoku[fila2][j];
            sudoku[fila2][j] = temp;
        }
    }

    // Hace un intercambio de columnas por cada bloque
    for(int i = 0; i < 3; i++) {
        int col1 = rand() % 3;
        int col2 = (col1 + (rand() % 2) +1) % 3;
        for (int j = 0; j < N; j++) {
            int temp = sudoku[j][col1];
            sudoku[j][col1] = sudoku[j][col2];
            sudoku[j][col2] = temp;
        }
    }
   
    // Elimina algunos numeros del tablero con probabilidad 1/2
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (rand() % 2 == 0) {
                sudoku[i][j] = 0;
            }
        }
    }
}

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

bool esSeguro(int sudoku[N][N], int fila, int col, int num) {
    // Verificacion de fila y columna
    for (int i = 0; i < N; i++) {
        if (sudoku[fila][i] == num || sudoku[i][col] == num) {
            return false;
        }
    }

    // Verificacion de tablero
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
    for(int i = 0; i < Z; i++) {
        generarSudoku(sudoku[i]);
    }
    for(int i = 0; i < Z; i++){
        printf("\n\xF0\x9F\x94\xB9 Sudoku #%d:\n", i + 1);
        printSudoku(sudoku[i]);
        if (resolverSudoku(sudoku[i])) {
            printf("\n\xE2\x9C\x85 Solución:\n");
            printSudoku(sudoku[i]);
        } else {
            printf("\n\xE2\x9D\x8C No tiene solución.\n");
        }

    }

    return 0;
}