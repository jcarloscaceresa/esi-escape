#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "memoria.h"
#include "acciones.h"

// 1. FUNCIÓN DE INICIO DE SESIÓN
int iniciarSesion(Partida *estado) {
    char usuario_input[11];
    char contrasena_input[9];

    printf("\n--- INICIO DE SESION ---\n");
    printf("Usuario: ");
    scanf("%10s", usuario_input);
    printf("Contrasena: ");
    scanf("%8s", contrasena_input);

    // Recorremos el vector dinámico de jugadores buscando coincidencia
    for (int i = 0; i < estado->num_jugadores; i++) {
        if (strcmp(estado->jugadores[i].Jugador, usuario_input) == 0 &&
            strcmp(estado->jugadores[i].Contrasena, contrasena_input) == 0) {
            
            // Si coincide, guardamos el puntero al jugaaador actual
            estado->jugador_actual = &estado->jugadores[i];
            printf("\n¡Bienvenido de nuevo, %s!\n", estado->jugador_actual->Nomb_jugador);
            return 1; // Éxito
        }
    }
    
    printf("\nError: Usuario o contrasena incorrectos.\n");
    return 0; // Fallo
}

// 2. MENÚ SECUNDARIO (Una vez iniciada la sesión)
void mostrarMenuPartida(Partida *estado) {
    int opcion;
    do {
        printf("\n--- MENU DE PARTIDA ---\n");
        printf("1. Nueva Partida\n");
        printf("2. Cargar Partida\n");
        printf("3. Cerrar Sesion\n");
        printf("Elige una opcion: ");
        
        // Comprobamos que el usuario meta un número
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n'); // Limpiamos el buffer si mete letras
            opcion = 0;
        }

        switch(opcion) {
            case 1:
                printf("\nPreparando nueva partida...\n");
                // iniciarNuevaPartida(estado); // (Esta función irá en acciones.c)
                // mostrarMenuAcciones(estado); // (El bucle del juego real)
                break;
            case 2:
                printf("\nCargando tu partida guardada...\n");
                // cargarPartidaGuardada(estado, "Partida.txt"); // (En gestionMemoria.c)
                // mostrarMenuAcciones(estado);
                break;
            case 3:
                printf("\nCerrando sesion de %s...\n", estado->jugador_actual->Jugador);
                estado->jugador_actual = NULL; // Borramos el rastro por seguridad
                break;
            default:
                printf("Opcion no valida. Intentalo de nuevo.\n");
        }
    } while (opcion != 3);
}

void mostrarMenuPrincipal(Partida *estado) {
    int opcion;
    do {
        printf("\n=========================\n");
        printf("       ESI ESCAPE        \n");
        printf("=========================\n");
        printf("1. Iniciar Sesion\n");
        printf("2. Registrarse\n");
        printf("3. Salir\n");
        printf("Elige una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = 0;
        }

        switch(opcion) {
            case 1:
                // Si el inicio de sesión devuelve 1 (Éxito), entramos al submenú
                if (iniciarSesion(estado)) {
                    mostrarMenuPartida(estado);
                }
                break;
            case 2:
                printf("\n[Funcion de registro en construccion...]\n");
                // registrarJugador(estado); 
                break;
            case 3:
                printf("\nSaliendo del juego... ¡Hasta la proxima!\n");
                break;
            default:
                printf("Opcion no valida. Intentalo de nuevo.\n");
        }
    } while (opcion != 3);
}


// 4. FUNCIÓN PRINCIPAL
int main() {
    Partida estado = {0}; // Inicializa la estructura a cero
    mostrarMenuPrincipal(&estado);
    return 0;
}