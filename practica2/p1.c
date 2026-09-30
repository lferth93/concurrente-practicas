#include<stdio.h>
#include<stdlib.h>

// Función que implementa el cifrado Cesar
// Recibe la llave y el archivo de entrada
void cesar(int llave, FILE *entrada){
    char a, c;
    a = 0;
    // Mientras el caracter actual no sea EOF 
    while(!feof(entrada)){
        a = 0;
        // Se lee un caracter del archivo de entrada
        char c = fgetc(entrada);
        if(c == EOF) break; 

        // El caracter leido es una mayuscula
        if(c >= 'A' && c <= 'Z'){
            a = 'A';
        } else if(c >= 'a' && c <= 'z'){
            a = 'a';
        }
        if(a != 0){
            c = (c - a + llave) % 26 + a;
        }
        putchar(c);
    }
}

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Uso 1: %s <archivo>\n", argv[0]);
        printf("Uso 2: %s <archivo> <llave>\n", argv[0]);
        return 1;
    }
    char *archivo = argv[1];
    int llave = 6;

    // Se verifica si se proporcionó una llave como argumento, 
    // si es así, se convierte a entero y se toma el módulo 26
    if(argc >= 3){
        llave = atoi(argv[2]) % 26;
    }

    // Se abre el archivo de entrada en modo lectura
    FILE *entrada = fopen(archivo, "r");
    // Se verifica si el archivo se abrió correctamente
    if(entrada == NULL){
        printf("Error al abrir el archivo\n");
        return 1;
    }

    // Se imprime el mensaje cifrado
    printf("El mensaje cifrado del archivo %s es:\n", archivo);
    cesar(llave, entrada);
    printf("\n");
    // Se cierra el archivo de entrada
    fclose(entrada);

    return 0;

}