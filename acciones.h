#ifndef ACCIONES_H
#define ACCIONES_H
#include "ficheros.h"

// Función principal del menú de la partida
void menu_de_partida(Partida *estado);

// Subacciones
void describir(Partida *estado);
void examinar(Partida *estado);
void entrar_sala(Partida *estado);
void coger_objeto(Partida *estado);
void soltar_objeto(Partida *estado);
void inventario(Partida *estado);
void usar_objeto(Partida *estado);
void resolver(Partida *estado);
void guardar_partida(Partida *estado);

#endif