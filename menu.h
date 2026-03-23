#ifndef MENU_H
#define MENU_H

#include "ficheros.h" // Imprescindible porque usamos la estructura "Partida"

// Prototipos de las funciones que gestionan la interfaz de usuario
int iniciarSesion(Partida *estado);
void mostrarMenuPartida(Partida *estado);
void mostrarMenuPrincipal(Partida *estado);
void registrarJugador(Partida *estado);

#endif