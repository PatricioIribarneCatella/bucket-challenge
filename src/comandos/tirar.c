#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "persona.h"
#include "pila.h"
#include "cola.h"
#include "vector.h"

#define SI "si"
#define NO "no"

// Imprime en una linea por salida estandar
// las cantidades donadas por la persona
// y el monto total de ellas.
//
static void cantidad_donada(persona_t* persona) {

	printf("OK [");
	
	int total_donado = 0;
	
	while (!pila_esta_vacia(persona->pila)) {
		
		char* monto = pila_desapilar(persona->pila);
		total_donado = total_donado + atoi(monto);
		
		if (pila_esta_vacia(persona->pila)) {
			
			printf("%s", monto);

		} else {
			
			printf("%s, ", monto);
		}
		
		free(monto);
	}
	
	printf("] TOTAL : %d\n", total_donado);
}

void tirar_balde(vector_t* vec_persona, char* persona_nombre, char* decision, cola_t* cola_balde) {

	if (strcmp((char*) cola_ver_primero(cola_balde), persona_nombre) != 0) {
		
		printf("ERROR5\n");
		return;
	}

	size_t pos = busqueda_persona(vec_persona, persona_nombre);
	persona_t* persona = vector_obtener(vec_persona, pos);
	
	if (strcmp(decision, NO) == 0) {
		
		if (pila_esta_vacia(persona->pila)) {
			
			printf("ERROR6\n");
			return;
		}
		
		printf("OK\n");

	} else if (strcmp(decision, SI) == 0) {
		
		cantidad_donada(persona);
		char* persona_balde = cola_desencolar(cola_balde);
		free(persona_balde);
	}
}

