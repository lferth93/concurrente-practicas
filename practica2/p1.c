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
        printf("%c", c);
    }
}

void print_ayuda(char *programa){
    printf("Uso 1: %s <opcion> <archivo>\n", programa);
    printf("Uso 2: %s <opcion> <archivo> <llave>\n", programa);
    printf("Opciones:\n");
    printf("  -c: Cifrar el archivo\n");
    printf("  -d: Descifrar el archivo\n");
}


int main(int argc, char *argv[]) {
    int llave = 6;
    char *archivo = NULL;
    if(argc < 3){
        print_ayuda(argv[0]);
        return 1;
    }

    if(argv[1][0] != '-' || (argv[1][1] != 'c' && argv[1][1] != 'd')){
        print_ayuda(argv[0]);
        return 1;
    }
    archivo = argv[2];

    // Se verifica si se proporcionó una llave como argumento, 
    // si es así, se convierte a entero y se toma el módulo 26
    if(argc >= 4){
        llave = atoi(argv[3]) % 26;
    }

    // Para decifrar es suficiente con ejecutar el cifrado, 
    // pero con la llave 26 - llave
    if (argv[1][1] == 'd') {
        llave = 26 - llave;
    }

    // Se abre el archivo de entrada en modo lectura
    FILE *entrada = fopen(archivo, "r");
    // Se verifica si el archivo se abrió correctamente
    if(entrada == NULL){
        printf("Error al abrir el archivo\n");
        return 1;
    }

    // Se imprime el mensaje cifrado
    if (argv[1][1] == 'c') {
        printf("El mensaje cifrado del archivo %s es:\n", archivo);
    } else {
        printf("El mensaje descifrado del archivo %s es:\n", archivo);
    }
    cesar(llave, entrada);
    printf("\n");
    // Se cierra el archivo de entrada
    fclose(entrada);

    return 0;

}