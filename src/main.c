#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "persona.h"
#include "lectura.h"
#include "procesar.h"

#include "vector.h"
#include "pila.h"
#include "cola.h"

#define TAM_INICIAL_VEC 50

/* ******************************************************************
 *                          DESTRUCCION
 * *****************************************************************/

// Destruye la linea leída por entrada estandar.
void destruir_linea(cola_t* cola) {

	cola_destruir(cola, free);
}

// Destruye todos los datos almacenados a lo largo de la ejecución del programa.
void destruir_datos(cola_t* linea, cola_t* cola_balde, vector_t* vec_persona) {

	destruir_linea(linea);
	cola_destruir(cola_balde, free);
	destruir_vec_persona(vec_persona);
}

/* ******************************************************************
 *                      Ice-Bucket-Challenge
 * *****************************************************************/

void ice_bucket_challenge() {

	cola_t* linea = leer_linea();

	if (!linea) {
		
		printf("ERROR INESPERADO DE MEMORIA\n");
		destruir_linea(linea);
		return;
	}

	vector_t *vec_persona = vector_crear(TAM_INICIAL_VEC);
	cola_t *cola_balde = cola_crear();

	while (!cola_esta_vacia(linea)) {

		procesar_linea(linea, vec_persona, cola_balde);
		destruir_linea(linea);
		linea = leer_linea();

	}

	destruir_datos(linea, cola_balde, vec_persona);
}

int main(void) {
	
	ice_bucket_challenge();

	return 0;
}

