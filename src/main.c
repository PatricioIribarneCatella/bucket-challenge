#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vector.h"
#include "pila.h"
#include "cola.h"

#define TAMANIO_INICIAL_BUFFER 10
#define TAM_INICIAL_VEC 50
#define SI "si"
#define NO "no"
#define DONAR "donar"
#define NOMINAR "nominar"
#define TIRAR_BALDE "tirar_balde"
#define FIN_LINEA '\n'
#define FIN_STRING '\0'
#define ESPACIO ' '

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct persona {
	pila_t *pila;
	char *nombre;
	size_t cantidad_balde;
} persona_t;

/* ******************************************************************
 *                FUNCION DE LECTURA DE COMANDOS
 * *****************************************************************/

cola_t* leer_linea() {

	char c;
	size_t tam = TAMANIO_INICIAL_BUFFER;
	int i;

	cola_t *cola = cola_crear();
	
	if (!cola) return NULL;

	c = getchar();
	
	while (c != FIN_LINEA && c != EOF) {

		char* buffer = malloc(sizeof(char)*(tam));
		
		if (!buffer) return NULL;
		
		i = 0;
		
		while (c != ESPACIO && c != FIN_LINEA) {

			if (i + 1 == tam) {
				
				tam += tam;
				char* aux = realloc(buffer, tam * sizeof(char));
				if (!aux) return NULL;
				buffer = aux;
			}
			
			buffer[i] = c;
			c = getchar();
			i++;
		}

		buffer[i] = FIN_STRING;
		cola_encolar(cola, buffer);
		
		if (c != FIN_LINEA) c = getchar();
	}

	return cola;
}


/* ******************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

// Crea una nueva persona con el nombre, y una pila vacia para las donaciones.
persona_t* crear_persona(char* nombre) {

	persona_t *persona = malloc(sizeof(persona_t));
	
	if (!persona) return NULL;
	
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
	
	if (cant == 0) return false;
	
	for (int i = 0; i < cant; i++) {
		
		persona_t* persona = vector_obtener(vec_persona, i);

		if (strcmp(persona->nombre, persona_nombre) == 0) return true;
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

	if (!nombre) return;
	
	strcpy(nombre, persona_nombre);
	
	cola_encolar(cola_balde, nombre);
}

// Imprime en una linea por salida estandar las cantidades donadas por la persona y el monto total de ellas.
void cantidad_donada(persona_t* persona) {

	printf("OK [");
	
	int total_donado = 0;
	
	while (!pila_esta_vacia(persona->pila)) {
		
		char* monto = pila_desapilar(persona->pila);
		total_donado = total_donado + atoi(monto);
		
		if (pila_esta_vacia(persona->pila)) {
			
			printf("%s", monto);

		}else{
			
			printf("%s, ", monto);
		}
		
		free(monto);
	}
	
	printf("] TOTAL : %d\n", total_donado);
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
 *                DONAR       TIRAR_BALDE     NOMINAR
 * *****************************************************************/

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

		}else {
			
			cargar_persona_en_sistema_y_en_cola_balde(vec_persona, cola_balde, nominado);
			printf("OK %s\n", nominado);
		}
		
		free(nominado);
	}
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

		} else{
			
			printf("COMANDO INVALIDO\n");
		}

		free(persona_nombre);
		free(comando);
	}
}


/* ******************************************************************
 *                              TP1
 * *****************************************************************/

void tp1() {

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
	
	tp1();
	return 0;
}
