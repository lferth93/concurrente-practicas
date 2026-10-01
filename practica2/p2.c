#include<stdio.h>
#include<stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *siguiente;
}nodo;

typedef struct {
    nodo *inicio;
}lista;

lista *crear_lista(){
    lista *l = (lista*)malloc(sizeof(lista));
    l->inicio = NULL;
    return l;
}

void insertar(lista *l, int dato){
    // Se reserva memoria para un nuevo nodo y se guarda el dato nuevo.
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->siguiente = NULL;

    // Si la lista es un apuntador vacío se reserva memoria para la lista
    if(l == NULL){
        l = crear_lista();
    }
    nodo *actual = l->inicio;

    // Si la lista está vacía o si el dato es menor que 
    // el primer elemento, se inserta el nodo al inicio
    if(actual == NULL || actual->dato > dato){
        l->inicio = nuevo;
        nuevo->siguiente = actual;
        return;
    } 

    // Se recorre la lista hasta encontrar su lugar 
    // o hasta llegar al final de la lista
    while(actual->siguiente != NULL){
        // Se verifica si el dato va en la posición siguiente de actual
        if(actual->siguiente->dato > dato){
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
            return;
        }
        actual = actual->siguiente;
    }
    actual->siguiente = nuevo;
    nuevo->siguiente = NULL;
}

void desplegar(lista *l){
    if(l == NULL || l->inicio == NULL){
        printf("NULL\n");
        return;
    }
    nodo *actual = l->inicio;
    while(actual != NULL){
        printf("[%d]->", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

// Regresa el nodo en el indice dado, o NULL si no existe
nodo * consultar(lista *l, int indice){
    if(l == NULL || l->inicio == NULL){
        return NULL;
    }
    nodo *actual = l->inicio;
    while(actual != NULL && indice > 0){
        actual = actual->siguiente;
        indice--;
    }
    return actual;
}

// Elimina el nodo con el dato dado, si existe
nodo *eliminar(lista *l, int dato){
    // Se verifica si la lista esta vacia
    if(l == NULL || l->inicio == NULL){
        return NULL;
    }

    nodo *actual = l->inicio;
    // Si el nodo a eliminar es el primero
    if(actual->dato == dato){
        l->inicio = actual->siguiente;
        return actual;
    }

    // Se recorre la lista hasta encontrar el nodo a eliminar
    nodo * eliminado = NULL;
    while(actual->siguiente != NULL){
        if(actual->siguiente->dato == dato){
            eliminado = actual->siguiente;
            actual->siguiente = eliminado->siguiente;
            eliminado->siguiente = NULL;
            return eliminado;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

// Función para buscar un elemento en la lista y devolver su índice, o -1 si no se encuentra
int buscar(lista *l, int dato){
    if(l == NULL || l->inicio == NULL){
        return -1;
    }
    nodo *actual = l->inicio;
    int indice = 0;
    while(actual != NULL){
        if(actual->dato == dato){
            return indice;
        }
        actual = actual->siguiente;
        indice++;
    }
    return -1;
}

// Funcion recursiva para buscar un elemento en la lista y devolver su índice, o -1 si no se encuentra
int buscar_recursivo(nodo *actual, int dato){
    if(actual == NULL){
        return -1;
    }
    if(actual->dato == dato){
        return 0;
    }
    int indice = buscar_recursivo(actual->siguiente, dato);
    return indice == -1 ? -1 : indice + 1;
}

void hacer_nula(lista *l){
    if(l == NULL || l->inicio == NULL){
        return;
    }

    nodo *actual = l->inicio;
    // Se recorre la lista liberando el nodo actual y avanzando al siguiente
    while(actual != NULL){
        nodo *temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    l->inicio = NULL;
}

void hacer_nula_recursivo(nodo *actual){
    if(actual == NULL){
        return;
    }
    hacer_nula_recursivo(actual->siguiente);
    free(actual);
}

int printMenu(){
    printf("1. Insertar elemento\n");
    printf("2. Desplegar lista\n");
    printf("3. Consultar elemento por índice\n");
    printf("4. Eliminar elemento\n");
    printf("5. Buscar elemento\n");
    printf("6. Buscar elemento recursivamente\n");
    printf("7. Hacer lista nula\n");
    printf("8. Hacer lista nula recursivamente\n");
    printf("9. Salir\n");
    printf("Ingrese una opción: ");
    int opcion;
    scanf("%d", &opcion);
    return opcion;
}


int main(){
    lista *l = crear_lista();
    int opcion = 0;

    while(opcion != 9){
        printMenu();
    }

    return 0;
}