#ifndef PERSONA_H
#define PERSONA_H

#include <stddef.h>
#include <stdbool.h>

#include "pila.h"
#include "cola.h"
#include "vector.h"

typedef struct persona {
	pila_t *pila;
	char *nombre;
	size_t cantidad_balde;
} persona_t;

persona_t* crear_persona(char* nombre);

bool existe(vector_t* vec_persona, char* persona_nombre);

size_t busqueda_persona(vector_t* vec_persona, char* persona_nombre);

void cargar_persona(vector_t* vec_persona, cola_t* cola_balde, char* persona_nombre);

void destruir_persona(persona_t* persona);

void destruir_vec_persona(vector_t* vec_persona);

#endif // PERSONA_H
