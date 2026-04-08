#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdlib.h>
#include <string.h>

//ESTRUCTURAS DE DATOS//

typedef struct {
    char Id_sala[3];       // 2 dígitos
    char Nomb_sala[31];    // 30 caracteres
    char Tipo[10];         // INICIAL, NORMAL O SALIDA
    char Descrip[151];     // 150 caracteres
} Salas;

typedef struct {
    char Id_conexion[4];   // 3 caracteres
    char Id_origen[3];     // 2 dígitos
    char Id_destino[3];    // 2 dígitos
    char Estado[11];       // Activa o Bloqueada
    char Cond[6];          // 0, Id_obj o Id_puzle
} Conexion;

typedef struct {
    char Id_obj[5];        // 4 caracteres
    char Nomb_obj[16];     // 15 caracteres
    char Descrip[51];      // 50 caracteres
    char Localiz[16];      // Id_sala o Inventario
} Objetos;

typedef struct {
    char Id_puzle[4];      // 3 caracteres
    char Nomb_puz[16];     // 15 caracteres
    char Id_sala[3];       // 2 dígitos
    char Tipo[10];         // Código o Palabra
    char Descrip[151];     // 150 caracteres
    char Sol[51];          // 50 caracteres
} Puzles;

//GESTIÓN DE MEMORIA DINÁMIC//
Salas* agregar_sala_memoria(Salas* salas, int* num_salas, Salas nueva_sala);
Conexiones* agregar_conexion_memoria(Conexiones* conexiones, int* num_conexiones, Conexiones nueva_conexion);
Objetos* agregar_objeto_memoria(Objetos* objetos, int* num_objetos, Objetos nuevo_objeto);
Puzles* agregar_puzle_memoria(Puzles* puzles, int* num_puzles, Puzles nuevo_puzle);

//LIBERACIÓN DE MEMORIA//
void liberar_memoria_salas(Salas* salas);
void liberar_memoria_conexiones(Conexiones* conexiones);
void liberar_memoria_objetos(Objetos* objetos);
void liberar_memoria_puzles(Puzles* puzles);

#endif

