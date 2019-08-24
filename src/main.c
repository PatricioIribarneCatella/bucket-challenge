#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "vector.h"
#include "pila.h"
#include "cola.h"
#include "persona.h"

#include "lectura.h"
#include "procesar.h"
#include "destruir.h"

#define TAM_INICIAL_VEC 50

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

