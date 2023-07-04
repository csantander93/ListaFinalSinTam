#include <stdlib.h>
#include "Lista.h"
#include "animal.h"

struct ListaE{
     PtrNodo primero;
};


struct NodoE {
    PtrDato dato; // dato almacenado
    struct NodoE * sgte; // puntero al siguiente
};

///Lista

PtrLista crearLista(){

    ///El constructor, lo de siempre :)
    PtrLista lista = malloc(sizeof(struct ListaE));
    lista->primero = NULL;


    return lista;
}

///NODO

PtrNodo crearNodo(PtrDato dato){

    PtrNodo nodo=(PtrNodo)malloc(sizeof(struct NodoE));
    nodo->dato = dato;
    nodo->sgte = NULL;

    return nodo;
}


PtrDato getDatoLista(PtrLista lista, int posicion){

    PtrNodo actual = lista->primero;
    int posicionActual = 0;

    if (actual != NULL) {
        while (posicionActual < posicion && actual->sgte != NULL) {
            posicionActual++;
            actual = actual->sgte;
        }
    }

    return actual->dato;
}


int longitudLista(PtrLista lista){
    // para obtener la longitud, debemos recorrer la lista.
    int longitud = 0;
    PtrNodo nodo = lista->primero;
    while(nodo != NULL){
        nodo = nodo->sgte;
        longitud++;
    }
    return longitud;
}

void insertarInicio(PtrLista lista, PtrDato dato) {
    // Creamos un nuevo nodo con el dato
    PtrNodo nuevoNodo = crearNodo(dato);

    // Si la lista está vacía, el nuevo nodo será el primero
    if (lista->primero == NULL) {
        lista->primero = nuevoNodo;
    } else {
        // Si la lista no está vacía, ajustamos los punteros
        nuevoNodo->sgte = lista->primero;
        lista->primero = nuevoNodo;
    }
}

void insertarFinal(PtrLista lista, PtrDato dato) {
    // Creamos un nuevo nodo con el dato
    PtrNodo nuevoNodo = crearNodo(dato);

    // Si la lista está vacía, el nuevo nodo será el primero
    if (lista->primero == NULL) {
        lista->primero = nuevoNodo;
    } else {
        // Si la lista no está vacía, recorremos hasta el último nodo
        PtrNodo nodoActual = lista->primero;
        while (nodoActual->sgte != NULL) {
            nodoActual = nodoActual->sgte;
        }
        // Asignamos el nuevo nodo al siguiente del último nodo
        nodoActual->sgte = nuevoNodo;
    }
}

void insertarOrdenado(PtrLista lista, PtrDato dato) {
    PtrNodo nuevoNodo = crearNodo(dato);

    // Si la lista está vacía o el dato es menor que el primer elemento
    if (lista->primero == NULL || dato < lista->primero->dato) {
        nuevoNodo->sgte = lista->primero;
        lista->primero = nuevoNodo;
    } else {
        PtrNodo nodoActual = lista->primero;
        PtrNodo nodoAnterior = NULL;

        // Recorremos la lista hasta encontrar la posición adecuada para el nuevo nodo
        while (nodoActual != NULL && dato >= nodoActual->dato) {
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->sgte;
        }

        // Insertamos el nuevo nodo en la posición adecuada
        nuevoNodo->sgte = nodoActual;
        nodoAnterior->sgte = nuevoNodo;
    }
}


void eliminarInicio(PtrLista lista) {

    if (lista->primero != NULL) {

        PtrNodo nodoAEliminar = lista->primero;
        lista->primero = lista->primero->sgte;
        free(nodoAEliminar);
    }
}

void vaciarLista(PtrLista lista){

    while(lista->primero != NULL){
    eliminarInicio(lista);
    }

}

void eliminarFinal(PtrLista lista){

    if(lista->primero != NULL){
        PtrNodo nodoActual = lista->primero;
        PtrNodo nodoAnterior = NULL;

        // Recorremos hasta el último nodo
        while(nodoActual->sgte != NULL){
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->sgte;
        }

        // Si hay un nodo anterior, ajustamos su puntero al siguiente
        if(nodoAnterior != NULL){
            nodoAnterior->sgte = NULL;
        }
        // Si no hay un nodo anterior, el último nodo es el primero de la lista
        else{
            lista->primero = NULL;
        }

        // Liberamos la memoria del nodo a eliminar
        free(nodoActual);
    }
}

void duplicarLista(PtrLista listaOriginal, PtrLista listaDuplicada) {
    PtrNodo nodoOriginal = listaOriginal->primero;

    while (nodoOriginal != NULL) {
        PtrDato datoOriginal = nodoOriginal->dato;
        PtrDato datoDuplicado = datoOriginal;  // Suponemos que el tipo de dato es un puntero

        insertarFinal(listaDuplicada, datoDuplicado);

        nodoOriginal = nodoOriginal->sgte;
    }
    ordenamiento(listaDuplicada);
}


void imprimirListaAnimal(PtrLista lista){

    printf("\n\n------ Lista con %d datos: ------\n",longitudLista(lista) );

    int i=0;

    for(i=0;i<longitudLista(lista);i++){
        mostrarAnimal( (Animal)  getDatoLista(lista,i) );

    }

}

void imprimirNumeros(PtrLista lista){

    printf("\n\n------ Lista con %d datos: ------\n",longitudLista(lista) );

    int i=0;

    for(i=0;i<longitudLista(lista);i++){
        printf(" %d  ", ( (int)  getDatoLista(lista,i) ));

    }

}

int busquedaSecuencial(PtrLista lista, int dato){

    int pos=-1;
    int i=0;

        while(i<longitudLista(lista) && pos == -1){
            if(dato == getDatoLista(lista, i)){
                pos = i;
        }
        i++;
}

return pos;

};


void ordenamiento(PtrLista lista){

int aux;
PtrNodo actual;

for(int i=0; i<longitudLista(lista); i++){

    actual = lista->primero;

    for(int j=0; j<longitudLista(lista)-1;j++){

        if(actual->dato > actual->sgte->dato ){

                aux = actual->dato;
                actual->dato = actual->sgte->dato;
                actual->sgte->dato = aux;

        }

        actual = actual->sgte;
        }
    }
}

void ordenamientoPorEdad(PtrLista lista) {
    Animal aux;
    PtrNodo actual;

    for (int i = 0; i < longitudLista(lista); i++) {

        actual = lista->primero;

        for (int j = 0; j < longitudLista(lista) - 1; j++) {

            if (getEdad((Animal)actual->dato) > getEdad((Animal)actual->sgte->dato)) {
                aux = actual->dato;
                actual->dato = actual->sgte->dato;
                actual->sgte->dato = aux;
            }

            actual = actual->sgte;
        }
    }
}

