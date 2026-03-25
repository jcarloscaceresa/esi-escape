#ifndef GESTIONMEMORIA_H
#define GESTIONMEMORIA_H
#include "ficheros.h"

// Funciones para volcar información de ficheros a memoria dinámica
void cargarDatosMemoria(Partida *Estado);
void guardarDatosFicheros(Partida *Estado);
void liberarDatosMemoria(Partida *Estado);

#endif
