#include<stdio.h>
#include<stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *siguiente;
}nodo;

typedef struct {
    nodo *inicio;
}lista;

void insertar(lista *l, int dato){
    // Se reserva memoria para un nuevo nodo y se guarda el dato nuevo.
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato = dato;

    // Si la lista es un apuntador vacío se reserva memoria para la lista
    if(l == NULL){
        l = (lista*)malloc(sizeof(lista));
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
    nodo *actual = l->inicio;
    while(actual != NULL){
        printf("[%d]->", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

// Regresa el nodo en el indice dado, o NULL si no existe
nodo * consultar(lista *l, int indice){
    nodo *actual = l->inicio;
    while(actual != NULL && indice > 0){
        actual = actual->siguiente;
        indice--;
    }
    return actual;
}



int main(){
    lista l;
    insertar(&l, 3);
    desplegar(&l);
    insertar(&l, 7);
    desplegar(&l);
    insertar(&l, 1);
    desplegar(&l);
    insertar(&l, 5);
    desplegar(&l);
    nodo *res = consultar(&l, 1);
    if(res != NULL){
        printf("Nodo encontrado: %d\n", res->dato);
    } else {
        printf("Nodo no encontrado\n");
    }
    return 0;
}