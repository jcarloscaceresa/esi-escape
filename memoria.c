
#include "memoria.h"

/* Funciones para ampliar la memoria dinámica y almacenar un nuevo elemento */

Sala* agregar_sala_memoria(Salas* salas, int* num_salas, Sala nueva_sala) {
    salas = (Salas*)realloc(salas, (*num_salas + 1) * sizeof(Salas));
    salas[*num_salas] = nueva_sala;
    (*num_salas)++;
    return salas;
}

Conexiones* agregar_conexion_memoria(Conexiones* conexiones, int* num_conexiones, Conexiones nueva_conexion) {
    conexiones = (Conexiones*)realloc(conexiones, (*num_conexiones + 1) * sizeof(Conexiones));
    conexiones[*num_conexiones] = nueva_conexion;
    (*num_conexiones)++;
    return conexiones;
}

Objetos* agregar_objeto_memoria(Objeto* objetos, int* num_objetos, Objetos nuevo_objeto) {
    objetos = (Objeto*)realloc(objetos, (*num_objetos + 1) * sizeof(Objetos));
    objetos[*num_objetos] = nuevo_objeto;
    (*num_objetos)++;
    return objetos;
}

Puzles* agregar_puzle_memoria(Puzle* puzles, int* num_puzles, Puzles nuevo_puzle) {
    puzles = (Puzles*)realloc(puzles, (*num_puzles + 1) * sizeof(Puzles));
    puzles[*num_puzles] = nuevo_puzle;
    (*num_puzles)++;
    return puzles;
}

/* Funciones para liberar los bloques de memoria asignados */

void liberar_memoria_salas(Salas* salas) {
    if (salas != NULL) free(salas);
}

void liberar_memoria_conexiones(Conexiones* conexiones) {
    if (conexiones != NULL) free(conexiones);
}

void liberar_memoria_objetos(Objetos* objetos) {
    if (objetos != NULL) free(objetos);
}

void liberar_memoria_puzles(Puzles* puzles) {
    if (puzles != NULL) free(puzles);
}
