#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/wait.h>

void initialize_vector(int *vector){
    for(int i=0; i < 5; i++){
        vector[i] = rand() % 100 + 1;
    }
}

void initialize_matrix(int **matriz){
    for(int i=0; i < 3; i++){
        for(int j=0; j < 3; j++){
            matriz[i][j] = rand() % 901 + 100;
        }
    }
}

void proceso_hijo(int *vector, int **matriz, float *prom){
    if(fork())
        return;

    for(int i=0; i < 5; i++){
        vector[i] *= 2;
    }

    int sum = 0;
    for(int i=0; i < 3; i++){
        for(int j=0; j < 3; j++){
            sum += matriz[i][j];
        }
    }

    *prom = (float)sum / 9;
    exit(0);
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    // Reservar memoria compartida para el vector, la matriz y el promedio
    int shm_id_vector = shmget(IPC_PRIVATE, 5*sizeof(int), IPC_CREAT | 0666);
    int *vector = (int *)shmat(shm_id_vector, NULL, 0);

    // Reservar memoria compartida para la matriz
    int shm_id_mat = shmget(IPC_PRIVATE, 3*sizeof(int), IPC_CREAT | 0666);
    int **matriz = (int **)shmat(shm_id_mat, NULL, 0);
    
    // Reservar memoria compartida para cada fila de la matriz
    for(int i = 0; i < 3; i++){
        int shm_id_fila = shmget(IPC_PRIVATE, 3*sizeof(int), IPC_CREAT | 0666);
        matriz[i] = (int *)shmat(shm_id_fila, NULL, 0);
    }
    
    int shm_id_prom = shmget(IPC_PRIVATE, sizeof(float), IPC_CREAT | 0666);
    float *prom = (float *)shmat(shm_id_prom, NULL, 0);

    initialize_vector(vector);
    printf("Vector: ");
    for(int i=0; i < 5; i++){
        printf("%d ", vector[i]);
    }
    printf("\n");

    initialize_matrix(matriz);
    printf("Matriz: \n");
    for(int i=0; i < 3; i++){
        for(int j=0; j < 3; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Llamada a la función que crea el proceso hijo y realiza las operaciones
    proceso_hijo(vector, matriz, prom);

    // Esperar a que el proceso hijo termine
    wait(NULL);

    printf("Vector: ");
    for(int i=0; i < 5; i++){
        printf("%d ", vector[i]);
    }
    printf("\n");
    printf("Promedio: %.2f\n", *prom);

    return 0;
}