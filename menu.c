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

int registrar_jugador(Partida *estado) {
    char nuevo_usuario[11];
    char nuevo_nombre[21];
    char nueva_contra[9];
    int max_id = 0;
    int falta_enter = 0;
    char linea[150];

    printf("\n--- REGISTRO DE NUEVO JUGADOR ---\n");
    printf("Elige un nombre de usuario (max 10 caracteres, sin espacios): ");
    scanf("%10s", nuevo_usuario);

    // PASO 1: Comprobar si el usuario ya existe y buscar el ID más alto
    FILE *f_lectura = fopen("Jugadores.txt", "r");
    if (f_lectura != NULL) {
        while (fgets(linea, sizeof(linea), f_lectura)) {
            if (linea[strlen(linea) - 1] != '\n') {
                falta_enter = 1; // Le falta el Enter
            } else {
                falta_enter = 0; // Sí lo tiene
            }

            linea[strcspn(linea, "\r\n")] = 0; // Limpiar salto de línea

            char *id_str     = strtok(linea, "-");
            char *nombre_txt = strtok(NULL, "-");
            char *user_txt   = strtok(NULL, "-");
            char *pass_txt   = strtok(NULL, "-");

            // Actualizamos el ID más alto encontrado
            if (id_str != NULL) {
                int id_actual = atoi(id_str);
                if (id_actual > max_id) {
                    max_id = id_actual;
                }
            }

            // Comprobamos si el usuario ya está pillado
            if (user_txt != NULL && strcmp(user_txt, nuevo_usuario) == 0) {
                printf("\nError: El usuario '%s' ya existe. Intenta con otro.\n", nuevo_usuario);
                fclose(f_lectura);
                return 0; // Fallo en el registro, devolvemos 0
            }
        }
        fclose(f_lectura);
    }

    // PASO 2: Pedir el resto de los datos
    while (getchar() != '\n'); // Limpiamos el buffer del teclado por el scanf anterior

    printf("Introduce tu nombre real o apodo (max 20 caracteres): ");
    // Usamos fgets para que el nombre pueda tener espacios (ej: "Paco Perez")
    fgets(nuevo_nombre, 21, stdin);
    nuevo_nombre[strcspn(nuevo_nombre, "\r\n")] = 0; // Limpiar el salto de línea del Enter

    printf("Elige una contrasena (max 8 caracteres, sin espacios): ");
    scanf("%8s", nueva_contra);

    // PASO 3: Guardar el nuevo jugador en el fichero
    // Usamos "a" (append) para añadir texto al final sin borrar lo que ya hay
    FILE *f_escritura = fopen("Jugadores.txt", "a");
    if (f_escritura == NULL) {
        printf("\nError: No se pudo guardar el registro en la base de datos.\n");
        return 0;
    }
    if (falta_enter == 1) {
        fprintf(f_escritura, "\n");
    }
    
    // Escribimos la línea con el formato exacto: ID-Nombre-Usuario-Contraseña
    // %02d asegura que el ID siempre tenga 2 dígitos (ej: 01, 05, 12)
    fprintf(f_escritura, "%02d-%s-%s-%s\n", max_id + 1, nuevo_nombre, nuevo_usuario, nueva_contra);
    fclose(f_escritura);

    printf("\n¡Registro completado con exito! Ya puedes iniciar sesion.\n");
    return 1; // Éxito
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
                    menu_de_partida(estado);
                }
                break;
            case 2:
                registrar_jugador(estado); 
                break;
            case 3:
                printf("\nSaliendo del juego... ¡Hasta la proxima!\n");
                break;
            default:
                printf("\nOpcion no valida. Intentalo de nuevo.\n");
        }
    } while (opcion != 3);
}

