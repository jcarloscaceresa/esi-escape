#include "ficheros.h"
#include "menu.h"
#include "memoria.h"

int main() {
    Partida estado = {0}; // Inicializamos todo a cero/NULL

    // 1. Cargamos todo lo necesario para que el juego funcione
    //cargarDatosMemoria(&estado);

    // 2. Lanzamos el menú principal (que ya se encarga de llamar al resto) (menu.h)
    mostrar_menu_principal(&estado);

    // 3. Al salir del menú, limpiamos la RAM antes de cerrar (memoria.h)
    //liberarDatosMemoria(&estado);

    return 0;
}