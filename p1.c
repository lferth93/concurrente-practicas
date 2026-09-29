#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Estructura para manejar cadenas y su hash, 
// el cual es la suma de los valores en ASCII.
typedef struct{
    char *cadena;
    int hash;
} Cadena;

// Función que regresa el apuntador a una cadena y calcula su hash.
Cadena *crearCadena(char *cadena){
    // Reserva memoria para una Cadena.
    Cadena *c = malloc(sizeof(Cadena));
    // Reserva memoria para la copia de la cadena.
    // Se usa la funcion strlen para obtener el tamanio 
    // de la cadena y se le suma 1 para el caracter nulo.
    c->cadena = malloc(sizeof(char) * (strlen(cadena) + 1));
    strcpy(c->cadena, cadena);
    // Calculo del hash.
    c->hash = 0;

    for(int i = 0; c->cadena[i] != '\0'; i++){
        c->hash += cadena[i];
    }
    return c;
}

// Función auxiliar para compara cadenas,
// devuelve: 
// <0 si c1 < c2, 
// 0 si son iguales
// >0 si c1 > c2
int compararCadenas(Cadena *c1, Cadena *c2){
    // Verifica si alguna de las cadenas es nula.
    if(c2 == NULL || c2->cadena == NULL) return -1;
    if(c1 == NULL || c1->cadena == NULL) return 1;
    //Si ambas cadenas son no nulas.
    return c2->hash - c1->hash;
}

void burbuja(Cadena **arr) {
    // Calcula el tamanio del arreglo de cadenas.
    int n = 0;
    while (arr[n] != NULL) {
        n++;
    }
    // Ejecucion del algoritmo burbuja.
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            // Verifica si las cadenas se tienen que intercambiar.
            // Se usa una variable temporal para hacer el intercambio.
            if (compararCadenas(arr[j], arr[j+1]) < 0) {
                Cadena *temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void imprimirCadenas(Cadena **arr) {
    // Imprimir las cadenas.
    int i = 0;
    while (arr[i] != NULL) {
        if (i > 0) {
            printf(" -> ");
        }
        printf("[ %s ]", arr[i]->cadena);
        i++;
    }
}

void imprimirHash(Cadena **arr) {
    // Imprimir los hash de las cadenas.
    int i = 0;
    while (arr[i] != NULL) {
        if (i > 0) {
            printf(" -> ");
        }
        printf("[ %d ]", arr[i]->hash);
        i++;
    }
}


int main() {
    int n; // Numero de cadenas.
    printf("Ingrese el numero de cadenas: ");
    scanf("%d", &n);

    // Reservar memoria para el arreglo de cadenas. 
    // La ultima posición se establece en NULL para indicar el final del arreglo.
    printf("Ingrese las cadenas, tamanio maximo 15 caracteres:\n");
    Cadena **arr = malloc(sizeof(Cadena*) * (n + 1));
    for (int i = 0; i < n; i++) {
        char cadena[10]; // Buffer para leer las cadenas.
        printf("Ingrese la cadena %d: ", i + 1);
        scanf("%s", cadena);
        // Se crea una nueva Cadena y se guarda en el arreglo.
        arr[i] = crearCadena(cadena);
    }
    arr[n] = NULL;

    // Imprimir cadenas.
    printf("\nCadenas antes de ordenar: ");
    imprimirCadenas(arr);

    // Imprimir hash de las cadenas.
    printf("\n\nHash de las cadenas: ");
    imprimirHash(arr);
    printf("\n\n");

    // Ordenar usando burbuja
    burbuja(arr);

    // Imprimir cadenas despues de ordenar.
    printf("Cadenas despues de ordenar: ");
    imprimirCadenas(arr);

    // Imprimir hash de las cadenas despues de ordenar.
    printf("\n\nHash de las cadenas despues de ordenar: ");
    imprimirHash(arr);
    printf("\n\n");
    
    return 0;
}
