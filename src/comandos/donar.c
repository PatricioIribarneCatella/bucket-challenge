#include <stdio.h>
#include <stdlib.h>

#include "persona.h"
#include "vector.h"
#include "pila.h"

void donar(vector_t* vec_persona, char* persona_nombre, char* cantidad) {


	int cant_donada = atoi(cantidad);
	size_t pos = busqueda_persona(vec_persona, persona_nombre);
	persona_t* persona = vector_obtener(vec_persona, pos);
	
	if (cant_donada <= 0 || persona->cantidad_balde != 0) {
		
		printf("ERROR1\n");
		return;
	}
	
	pila_apilar(persona->pila, cantidad);
	printf("OK\n");
}

