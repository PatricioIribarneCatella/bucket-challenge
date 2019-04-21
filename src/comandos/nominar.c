#include <stdio.h>
#include <stdlib.h>

#include "persona.h"
#include "vector.h"
#include "cola.h"
#include "pila.h"

void nominar(vector_t* vec_persona, char* persona_nombre, cola_t* cola, cola_t* cola_balde) {

	if (!existe(vec_persona, persona_nombre)) {
		
		printf("ERROR2\n");
		return;
	}

	size_t pos = busqueda_persona(vec_persona, persona_nombre);
	persona_t* persona = vector_obtener(vec_persona, pos);
	
	if (pila_esta_vacia(persona->pila)) {
		
		printf("ERROR3\n");
		return;
	}

	while (!cola_esta_vacia(cola)) {
		
		char* nominado = cola_desencolar(cola);
		
		if (existe(vec_persona, nominado)) {
			
			printf("ERROR4 %s\n", nominado);

		} else {
			
			cargar_persona(vec_persona, cola_balde, nominado);
			printf("OK %s\n", nominado);
		}
		
		free(nominado);
	}
}

