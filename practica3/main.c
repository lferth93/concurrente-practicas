#include"comun.h"
#include<stdio.h>
#include<stdlib.h>

int main(){

    char nombre_archivo[] = "prueba_1.dat";

    instancia *inst = NULL;
    while(inst == NULL){
        printf("Introdusca el nombre del archivo de datos: ");
        scanf("%s", nombre_archivo);
        inst = leer_instancia(nombre_archivo);
        if(inst == NULL){
            printf("Error al leer la instancia. Asegúrate de que el archivo '%s' exista y tenga el formato correcto.\n", nombre_archivo);
        }
    }

    int n = 20;
    int iteraciones = 20;

    printf("Introduzca el tamaño de la población (n): ");
    scanf("%d", &n);
    printf("Introduzca el número de iteraciones: ");
    scanf("%d", &iteraciones);

    cromosoma *mejor = NULL;
    cromosoma *poblacion = crear_arreglo_cromosomas(n, inst);

    mejor = mejor_cromosoma(poblacion, n);
    imprimir_poblacion(poblacion, n);

    printf("Mejor cromosoma: Genotipo = ");
    imprimir_cromosoma(mejor);
    printf(", Peso = %.2f, Aptitud = %.15f\n", mejor->genotipo, mejor->peso, mejor->aptitud);
    
    for(int i=0; i<iteraciones; i++){
        printf("\nIteración %d:\n", i+1);
        cromosoma *seleccionados = seleccion(poblacion, n);
        cruzar_poblacion(seleccionados, n, inst->p_cruza);
        mutar(seleccionados, n, inst->p_mutacion);
        for(int j=0; j<n; j++){
            actualizar_aptitud(&seleccionados[j], inst);
        }

        cromosoma *mejor_local = mejor_cromosoma(seleccionados, n);
        if (mejor_local->aptitud > mejor->aptitud) {
            copiar_cromosoma(mejor_local, mejor);
        }
        free(mejor_local);
        free(poblacion);
        poblacion = seleccionados;
        imprimir_poblacion(poblacion, n);
        printf("Mejor cromosoma hasta ahora: Genotipo = ");
        imprimir_cromosoma(mejor);
        printf(", Peso = %.2f, Aptitud = %.15f\n", mejor->genotipo, mejor->peso, mejor->aptitud);
    }

    printf("Peso máximo permitido: %.2f\n", inst->maxima);

}
