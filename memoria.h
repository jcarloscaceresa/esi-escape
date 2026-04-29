#ifndef GESTIONMEMORIA_H
#define GESTIONMEMORIA_H
#include "ficheros.h"

// Funciones para volcar información de ficheros a memoria dinámica
void cargarDatosMemoria(Partida *estado);
void guardarDatosFicheros(Partida *estado);
void liberarDatosMemoria(Partida *estado);

#endif
