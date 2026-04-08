#ifndef FICHERO_H
#define FICHERO_H

// Incluimos el módulo de memoria para conocer las estructuras//
#include "memoria.h"
#include <stdio.h>

//LECTURA DE FICHEROS//
Salas* cargar_fichero_salas(const char* nombre_fichero, int* num_salas);
Conexiones* cargar_fichero_conexiones(const char* nombre_fichero, int* num_conexiones);
Objetos* cargar_fichero_objetos(const char* nombre_fichero, int* num_objetos);
Puzles* cargar_fichero_puzles(const char* nombre_fichero, int* num_puzles);

//ESCRITURA DE FICHEROS/
int guardar_fichero_objetos(const char* nombre_fichero, Objetos* objetos, int num_objetos);
int guardar_fichero_conexiones(const char* nombre_fichero, Conexiones* conexiones, int num_conexiones);

#endif
