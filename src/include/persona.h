#ifndef PERSONA_H
#define PERSONA_H

typedef struct persona {
	pila_t *pila;
	char *nombre;
	size_t cantidad_balde;
} persona_t;

#endif // PERSONA_H
