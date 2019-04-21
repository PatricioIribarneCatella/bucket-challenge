#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "persona.h"

// Crea una nueva persona con el nombre,
// y una pila vacia para las donaciones.
//
persona_t* crear_persona(char* nombre) {

	persona_t *persona = malloc(sizeof(persona_t));
	
	if (!persona)
		return NULL;
	
	persona->nombre = malloc(sizeof(char)*(strlen(nombre) + 1));
	
	if (!persona->nombre) {
		free(persona);
		return NULL;
	}
	
	strcpy(persona->nombre, nombre);
	
	persona->pila = pila_crear();
	persona->cantidad_balde = 0;
	
	return persona;
}

// Se fija si una persona existe o no en el sistema.
bool existe(vector_t* vec_persona, char* persona_nombre) {

	size_t cant = vector_obtener_cantidad(vec_persona);
	
	if (cant == 0)
		return false;
	
	for (int i = 0; i < cant; i++) {
		
		persona_t* persona = vector_obtener(vec_persona, i);

		if (strcmp(persona->nombre, persona_nombre) == 0)
			return true;
	}
	
	return false;
}

// Busca una persona en el sistema y devuelve su posición en el arreglo.
size_t busqueda_persona(vector_t* vec_persona, char* persona_nombre) {

	int i = 0;

	size_t cant = vector_obtener_cantidad(vec_persona);
	
	while (i < cant) {
		
		persona_t* persona = vector_obtener(vec_persona, i);
		
		if (strcmp(persona->nombre, persona_nombre) == 0)
			return i;
		
		i++;
	}

	return -1;
}

// Carga una nueva persona en el sistema y en la cola para tirarse el valde.
void cargar_persona_en_sistema_y_en_cola_balde(vector_t* vec_persona, cola_t* cola_balde, char* persona_nombre) {

	persona_t* nueva_persona = crear_persona(persona_nombre);
	
	size_t tope = vector_obtener_cantidad(vec_persona);
	
	vector_guardar(vec_persona, tope, nueva_persona);
	
	char* nombre = malloc(sizeof(char)*(strlen(persona_nombre) + 1));

	if (!nombre)
		return;
	
	strcpy(nombre, persona_nombre);
	
	cola_encolar(cola_balde, nombre);
}

// Destruye la estructura de la persona.
void destruir_persona(persona_t* persona) {

	while (!pila_esta_vacia(persona->pila)) {
		
		char* dato = pila_desapilar(persona->pila);
		free(dato);
	}

	pila_destruir(persona->pila);
	free(persona->nombre);
	free(persona);
}

// Destruye el arreglo donde se cargan las personas.
void destruir_vec_persona(vector_t* vec_persona) {

	for (int i = 0; i < vector_obtener_cantidad(vec_persona); i++) {
		
		persona_t* persona = vector_obtener(vec_persona, i);
		destruir_persona(persona);
		persona = NULL;
	}

	vector_destruir(vec_persona);
}

