#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo_cola {
    void* *datos;
    struct nodo_cola *siguiente;
} nodo_cola_t;

typedef struct cola {
    nodo_cola_t *primero;
    nodo_cola_t *ultimo;
} cola_t;


cola_t* cola_crear(){

    cola_t *cola = malloc (sizeof(cola_t));
    if (cola == NULL){
        return NULL;
    }
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

bool cola_esta_vacia(const cola_t *cola){

    if (cola->primero == NULL && cola->ultimo == NULL){
        return true;
    }
    return false;
}

bool cola_encolar(cola_t *cola, void* valor){

    nodo_cola_t *nodo_cola = malloc (sizeof(nodo_cola_t));
    if (nodo_cola == NULL){
        return false;
    }
    nodo_cola->datos = valor;
    nodo_cola->siguiente = NULL;
    if (cola_esta_vacia(cola)){
        cola->primero = nodo_cola;
        cola->ultimo = nodo_cola;
        return true;
    }
    cola->ultimo->siguiente = nodo_cola;
    cola->ultimo = nodo_cola;
    return true;
}

void* cola_ver_primero(const cola_t *cola){
    if (cola_esta_vacia(cola)){
        return NULL;
    }
    return cola->primero->datos;
}

void* cola_desencolar(cola_t *cola){

    void* valor;
    if (cola_esta_vacia(cola)){
        return NULL;
    }
    valor = cola->primero->datos;
    nodo_cola_t* nodo_siguiente = cola->primero->siguiente;
    nodo_cola_t* nodo = cola->primero;
    free (nodo);
    cola->primero = nodo_siguiente;
    if (cola->primero == NULL){
        cola->ultimo = NULL;
    }
    return valor;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){

    void* dato;
    while (! cola_esta_vacia(cola)){
        dato = cola_desencolar(cola);
        if (destruir_dato != NULL){
            destruir_dato(dato);
        }
    }
    free (cola);
}

