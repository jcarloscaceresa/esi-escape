#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "memoria.h"
#include "acciones.h"

int iniciar_sesion(Partida *estado) {
    char usuario_input[11];
    char contrasena_input[9];

    printf("\n--- INICIO DE SESION ---\n");
    printf("Usuario: ");
    scanf("%10s", usuario_input);
    printf("Contrasena: ");
    scanf("%8s", contrasena_input);

    // 1. Abrimos el fichero directamente
    FILE *f = fopen("Jugadores.txt", "r");
    if (f == NULL) {
        printf("\nError: No se pudo abrir la base de datos de jugadores.\n");
        return 0; 
    }

    char linea[150];
    // 2. Leemos línea a línea hasta el final del fichero
    while (fgets(linea, sizeof(linea), f)) {
        // Limpiamos el salto de línea al final de la línea leída (¡SÚPER IMPORTANTE!)
        linea[strcspn(linea, "\r\n")] = 0;

        // 3. Cortamos la línea por los guiones. Suponiendo formato: Id-Nombre-Usuario-Contraseña
        char *id_str     = strtok(linea, "-");
        char *nombre_txt = strtok(NULL, "-");
        char *user_txt   = strtok(NULL, "-");
        char *pass_txt   = strtok(NULL, "-");

        // Verificamos que la línea tenía todas las partes antes de comparar
        if (user_txt != NULL && pass_txt != NULL) {
            
            // 4. Comparamos lo que hay en el .txt con lo que tecleó el usuario
            if (strcmp(user_txt, usuario_input) == 0 && strcmp(pass_txt, contrasena_input) == 0) {
                
                // ¡COINCIDENCIA! 
                // Reservamos memoria SÓLO para este jugador en la mesa de trabajo
                estado->jugador_actual = (Jugadores *)malloc(sizeof(Jugadores));
                
                // Copiamos los datos del txt a la memoria dinámica del jugador
                estado->jugador_actual->Id_jugador = atoi(id_str);
                strncpy(estado->jugador_actual->Nomb_jugador, nombre_txt, 20);
                strncpy(estado->jugador_actual->Jugador, user_txt, 10);
                strncpy(estado->jugador_actual->Contrasena, pass_txt, 8);
                estado->jugador_actual->Inventario = NULL; // Esto se cargará luego si carga partida

                printf("\n¡Bienvenido de nuevo, %s!\n", estado->jugador_actual->Nomb_jugador);
                
                fclose(f); // Cerramos el cajón
                return 1;  // Éxito
            }
        }
    }

    // Si el bucle termina y no ha devuelto 1, es que no lo encontró
    fclose(f);
    printf("\nError: Usuario o contrasena incorrectos.\n");
    return 0;
}

void mostrar_menu_principal(Partida *estado) {
    int opcion;
    do {
        printf("\n=========================\n");
        printf("   Bienvenido al juego   \n");
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
                if (iniciar_sesion(estado)) {
                    // void menu_de_partida(); Llamada a la función de acciones.c para abrir el menú de la sala.
                }
                break;
            case 2:
                printf("\n[Funcion de registro en construccion...]\n");
                // registrar_jugador(estado); 
                break;
            case 3:
                printf("\nSaliendo del juego... ¡Hasta la proxima!\n");
                break;
            default:
                printf("\nOpcion no valida. Intentalo de nuevo.\n");
        }
    } while (opcion != 3);
}