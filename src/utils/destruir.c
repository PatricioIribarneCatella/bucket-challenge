#include <stdlib.h>

#include "cola.h"
#include "vector.h"
#include "persona.h"

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

