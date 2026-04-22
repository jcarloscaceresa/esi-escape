#ifndef MENU_H
#define MENU_H

#include "ficheros.h" // Imprescindible porque usamos la estructura "Partida"
#include "acciones.h"
#include "memoria.h"

// Prototipos de las funciones que gestionan la interfaz de usuario
int iniciar_sesion(Partida *estado);
void mostrar_menu_principal(Partida *estado);
int registrar_jugador(Partida *estado);

#endif