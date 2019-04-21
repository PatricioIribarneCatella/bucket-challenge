#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cola.h"
#include "vector.h"
#include "persona.h"

#include "donar.h"
#include "tirar.h"
#include "nominar.h"

#define DONAR "donar"
#define NOMINAR "nominar"
#define TIRAR_BALDE "tirar_balde"

/* ******************************************************************
 *                         PROCESAR LINEA
 * *****************************************************************/

void procesar_linea(cola_t* cola, vector_t* vec_persona, cola_t* cola_balde) {

	if (!cola_esta_vacia(cola)) {
		
		char* persona_nombre = cola_desencolar(cola);
		char* comando = cola_desencolar(cola);

		if (strcmp(comando, DONAR) == 0) {

			if (!existe(vec_persona, persona_nombre)) {
				cargar_persona_en_sistema_y_en_cola_balde(vec_persona, cola_balde, persona_nombre);
			}

			char* cantidad = cola_desencolar(cola);
			donar(vec_persona, persona_nombre, cantidad);

		} else if (strcmp(comando, NOMINAR) == 0) {
			
			nominar(vec_persona, persona_nombre, cola, cola_balde);

		} else if (strcmp(comando, TIRAR_BALDE) == 0) {
			
			char *decision = cola_desencolar(cola);
			tirar_balde(vec_persona, persona_nombre, decision, cola_balde);
			free(decision);

		} else {
			
			printf("COMANDO INVALIDO\n");
		}

		free(persona_nombre);
		free(comando);
	}
}

