#include "comun.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RHO 0.1
#define MAX_OBJETOS 64
#define MAX_BITS 60

// Función para leer la instancia desde un archivo
instancia *leer_instancia(char *nombre_archivo) {
    srand(time(NULL)); // Inicializa la semilla para la generación de números aleatorios
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    instancia *inst = malloc(sizeof(instancia));

    fscanf(archivo, "%f %f %d %f", &inst->p_cruza, &inst->p_mutacion, &inst->n_objetos, &inst->maxima);
    inst->p_cruza /= 100.0; // Convertir a decimal
    inst->p_mutacion /= 100.0; // Convertir a decimal

    inst->area = malloc(MAX_OBJETOS * sizeof(float));
    inst->longitud = malloc(MAX_OBJETOS * sizeof(float));

    for (int i = 0; i < inst->n_objetos; i++) {
        fscanf(archivo, "%f %f", &inst->area[i], &inst->longitud[i]);
    }

    for (int i = inst->n_objetos; i < MAX_OBJETOS; i++) {
        int random_index = rand() % inst->n_objetos;
        inst->area[i] = inst->area[random_index];
        inst->longitud[i] = inst->longitud[random_index];
    }

    fclose(archivo);
    return inst;
}

// Regresa el apuntador a la copia de un cromosoma
void copiar_cromosoma(cromosoma *origen, cromosoma *destino) {
    destino->genotipo = origen->genotipo;
    destino->peso = origen->peso;
    destino->aptitud = origen->aptitud;
}

// Función para actualizar la aptitud de un cromosoma
void actualizar_aptitud(cromosoma *c, instancia *inst) {
    float peso_total = 0.0;
    for (int i = 0; i < 10; i++) {
        int indice = c->genotipo >> (6*i) & 0x3F; // Extrae el índice del objeto correspondiente
        peso_total += RHO * inst->area[indice]* inst->longitud[indice];
    }
    c->peso = peso_total;
    c->aptitud = 1.0/(1000*abs(inst->maxima - peso_total));
}

// Función para crear un arreglo de cromosomas aleatorios
cromosoma *crear_arreglo_cromosomas(int n, instancia *inst) {
    cromosoma *arreglo = malloc(n * sizeof(cromosoma));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            arreglo[i].genotipo |= ((long long int)(rand() % MAX_OBJETOS)) << (6*j);
        }
        actualizar_aptitud(&arreglo[i], inst);
    }
    return arreglo;
}

// Función de selección por ruleta
cromosoma *seleccion(cromosoma *poblacion, int n) {
    // Crear un arreglo para almacenar los cromosomas seleccionados
    cromosoma *seleccionado = malloc(sizeof(cromosoma)*n);
    float total_aptitud = 0.0;
    for (int i = 0; i < n; i++) {
        total_aptitud += poblacion[i].aptitud;
    }

    for (int i = 0; i < n; i++) {
        float r = ((float)rand() / RAND_MAX) * total_aptitud; // Genera un número aleatorio entre 0 y la suma total de aptitudes
        float acumulado = 0.0;
        for (int j = 0; j < n; j++) {
            acumulado += poblacion[j].aptitud;
            if (acumulado >= r) {
                copiar_cromosoma(&poblacion[j], &seleccionado[i]); // Retorna el cromosoma seleccionado
                break;
            }
        }
    }
    return seleccionado;
}

void cruzar(cromosoma *padre1, cromosoma *padre2, float pc) {
    int punto_cruce = rand() % MAX_BITS;
    long long int mascara = (1LL << punto_cruce);
    while (mascara) {
        float probabilidad = (float)rand() / RAND_MAX;
        if (probabilidad < pc) {
            long long int bit1 = padre1->genotipo & mascara;
            long long int bit2 = padre2->genotipo & mascara;
            padre1->genotipo = (padre1->genotipo & ~mascara) | bit2;
            padre2->genotipo = (padre2->genotipo & ~mascara) | bit1;
        }
        mascara >>= 1;
    }
}

void cruzar_poblacion(cromosoma *poblacion, int n, float pc) {
    for (int i = 0; i < n; i += 2) {
        cruzar(&poblacion[i], &poblacion[i + 1], pc);
    }
}

void mutar(cromosoma *poblacion, int n, float pm) {
    for (int i = 0; i < n; i++) {
        long long int mascara = 1;
        for (int j = 0; j < MAX_BITS; j++) {
            float probabilidad = (float)rand() / RAND_MAX;
            if (probabilidad < pm) {
                poblacion[i].genotipo ^= mascara; // Cambia el bit correspondiente
            }
            mascara <<= 1;
        }
    }
}

void limpiar_poblacion(cromosoma *poblacion, int n) {
    free(poblacion);
}

cromosoma *mejor_cromosoma(cromosoma *poblacion, int n) {
    cromosoma *mejor = malloc(sizeof(cromosoma));
    float mejor_aptitud = 0.0;
    for (int i = 1; i < n; i++) {
        if (poblacion[i].aptitud > mejor_aptitud) {
            mejor_aptitud = poblacion[i].aptitud;
            copiar_cromosoma(&poblacion[i], mejor);
        }
    }
    return mejor;
}

void imprimir_poblacion(cromosoma *poblacion, int n) {
    printf("Población:\n");
    printf("No.  | Bits                                                         | Peso    | Aptitud\n");
    printf("-----+--------------------------------------------------------------+---------+-------------\n");
    for (int i = 0; i < n; i++) {
        printf("[%2d] | ", i+1);
        imprimir_cromosoma(&poblacion[i]);
        printf(" | %.2f | %.15f\n", poblacion[i].peso, poblacion[i].aptitud);
    }
}

void imprimir_cromosoma(cromosoma *c) {
    long long int mascara = 1LL << (MAX_BITS - 1);
    for (int i = 0; i < MAX_BITS; i++) {
        if (c->genotipo & mascara) {
            printf("1");
        } else {
            printf("0");
        }
        mascara >>= 1;
    }
}