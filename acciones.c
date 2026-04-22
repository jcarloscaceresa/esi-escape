#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ficheros.h"
#include "acciones.h"
#include "memoria.h"

void menu_de_partida(Partida *estado){
    int regresar=0, accion, salir=0;
    char confirmar; // Añadimos esta para la opción 10
    do{

    printf("===================================================================\n");
    printf("Escriba el numero correspondiente a la accion que desea realizar:\n");
    printf("1. Describir sala\n");
    printf("2. Examinar (objetos y salidas)\n");
    printf("3. Entrar en otra sala\n");
    printf("4. Coger objeto\n");
    printf("5. Soltar objeto\n");
    printf("6. Inventario\n");
    printf("7. Usar objeto\n");
    printf("8. Resolver puzzle/Introducir codigo\n");
    printf("9. Guardar partida\n");
    printf("10. Volver\n");
    // Protección del scanf para evitar bucles infinitos con letras
        if (scanf("%d", &accion) != 1) {
            while (getchar() != '\n'); // Limpiar buffer
            accion = 0;
        }

        switch(accion){
            case 1:
                describir(estado);
                break;
            case 2:
                examinar(estado);
                break;
            case 3:
                entrar_sala(estado);
                break;
            case 4:
                coger_objeto(estado);
                break;
            case 5:
                soltar_objeto(estado);
                break;
            case 6:
                inventario(estado);
                break;
            case 7:
                usar_objeto(estado);
                break;
            case 8:
                resolver(estado);
                break;
            case 9:
                guardar_partida(estado);
                break;
            case 10:
                printf("\n¿De verdad desea salir? Se perdera el progreso no guardado.\n");
                
                // Bucle para obligar al usuario a introducir S o N
                do {
                    printf("Introduzca 'S' para salir al menu de inicio, o 'N' para cancelar: ");
                    scanf(" %c", &confirmar); 
                    
                    // Limpiamos el buffer siempre para evitar basura
                    while (getchar() != '\n');

                    // Si mete un caracter que NO es ni S ni N, le avisamos
                    if (confirmar != 'S' && confirmar != 's' && confirmar != 'N' && confirmar != 'n') {
                        printf("\nError: Caracter incorrecto. Por favor, introduzca unicamente 'S' o 'N'.\n");
                    }
                    
                // El bucle se repite MIENTRAS el caracter sea incorrecto
                } while (confirmar != 'S' && confirmar != 's' && confirmar != 'N' && confirmar != 'n');

                // Si llegamos a esta línea, es matemáticamente seguro que confirmar es S o N
                if (confirmar == 'S' || confirmar == 's') {
                    regresar = 1; // Rompemos el bucle principal de la partida
                    printf("\nSaliendo de la partida...\n");
                } else {
                    // Si es N o n
                    printf("\nCancelado. Volviendo a la sala...\n");
                }
                break;
        }
    } while(regresar == 0);
}

// --- DESARROLLO DE LAS SUB-ACCIONES ---

void describir(Partida *estado) {
    printf("\n--- MIRANDO ALREDEDOR ---\n");
    int encontrada = 0;

    for (int i = 0; i < estado->num_salas; i++) {
        if (estado->salas[i].Id_sala == estado->sala_actual_id) {
            printf("Te encuentras en: %s\n", estado->salas[i].Nomb_sala);
            // Mostrar descripción de la sala 
            printf("%s\n", estado->salas[i].Descrip); 
            
            // Si la sala es de tipo SALIDA, mostrar mensaje de victoria
            if (strcmp(estado->salas[i].Tipo, "SALIDA") == 0) {
                printf("\n==================================================\n");
                printf("  ¡ENHORABUENA! HAS ALCANZADO LA SALIDA Y ESCAPADO \n");
                printf("==================================================\n");
                printf("Por favor, selecciona la opcion '10. Volver' para regresar al menu.\n");
            }
            encontrada = 1;
            break;
        }
    }
    if (!encontrada) printf("Error: La sala actual no existe.\n");
}

void examinar(Partida *estado) {
    printf("\n--- EXAMINANDO LA SALA ---\n");
    char sala_str[3];
    sprintf(sala_str, "%02d", estado->sala_actual_id);

    printf("OBJETOS VISIBLES:\n");
    int hay_objetos = 0;
    for (int i = 0; i < estado->num_objetos; i++) {
        // Listar todos los objetos que están en la sala actual
        if (strcmp(estado->objetos[i].Localiz, sala_str) == 0) {
            printf(" - [%s] %s\n", estado->objetos[i].Id_obj, estado->objetos[i].Nomb_obj);
            hay_objetos = 1;
        }
    }
    if (!hay_objetos) printf(" No hay ningun objeto interesante aqui.\n");

    printf("\nSALIDAS DISPONIBLES:\n");
    int hay_salidas = 0;
    for (int i = 0; i < estado->num_conexiones; i++) {
        // Listar conexiones indicando si están bloqueadas o activas
        if (estado->conexiones[i].Id_origen == estado->sala_actual_id) {
            printf(" - Hacia la sala %02d | Estado: %s\n", 
                   estado->conexiones[i].Id_destino, 
                   estado->conexiones[i].Estado);
            hay_salidas = 1;
        }
    }
    if (!hay_salidas) printf(" No parece haber salidas desde aqui.\n");
}

void entrar_sala(Partida *estado) {
    int destino;
    printf("\n--- MOVERSE ---\n");
    printf("Introduce el numero de la sala a la que quieres ir: ");
    if (scanf("%d", &destino) != 1) {
        while (getchar() != '\n'); 
        printf("Entrada invalida.\n");
        return;
    }

    // Buscar si existe una conexión desde la sala actual al destino
    for (int i = 0; i < estado->num_conexiones; i++) {
        if (estado->conexiones[i].Id_origen == estado->sala_actual_id && 
            estado->conexiones[i].Id_destino == destino) {
            
            if (strcmp(estado->conexiones[i].Estado, "Activa") == 0) {
                estado->sala_actual_id = destino;
                printf("Te has movido a la sala %02d.\n", destino);
                return;
            } else {
                // Si la conexión está bloqueada, indicar la condición de desbloqueo
                printf("El acceso a la sala %02d esta %s.\n", destino, estado->conexiones[i].Estado);
                printf("Condicion para desbloquear: %s\n", estado->conexiones[i].Condicion);
                return;
            }
        }
    }
    printf("No hay ninguna conexion directa con esa sala desde aqui.\n");
}

void coger_objeto(Partida *estado) {
    char id_buscado[5];
    printf("\n--- COGER OBJETO ---\n");
    printf("Introduce el ID del objeto que quieres coger (ej. OB01): ");
    scanf("%4s", id_buscado);

    char sala_str[3];
    sprintf(sala_str, "%02d", estado->sala_actual_id);

    for (int i = 0; i < estado->num_objetos; i++) {
        // Validar que el objeto solicitado existe y está en la sala actual
        if (strcmp(estado->objetos[i].Id_obj, id_buscado) == 0) {
            if (strcmp(estado->objetos[i].Localiz, sala_str) == 0) {
                // Modificar la localización a "Inventario"
                strcpy(estado->objetos[i].Localiz, "Inventario");
                printf("Has recogido: %s\n", estado->objetos[i].Nomb_obj);
                return;
            } else if (strcmp(estado->objetos[i].Localiz, "Inventario") == 0) {
                printf("Ya tienes este objeto en tu inventario.\n");
                return;
            }
        }
    }
    printf("No veo ese objeto aqui.\n");
}

void soltar_objeto(Partida *estado) {
    char id_buscado[5];
    printf("\n--- SOLTAR OBJETO ---\n");
    printf("Introduce el ID del objeto a soltar: ");
    scanf("%4s", id_buscado);

    for (int i = 0; i < estado->num_objetos; i++) {
        if (strcmp(estado->objetos[i].Id_obj, id_buscado) == 0) {
            // Comprobar que realmente lo tiene en el inventario
            if (strcmp(estado->objetos[i].Localiz, "Inventario") == 0) {
                // Cambiar la localización al ID de la sala actual
                sprintf(estado->objetos[i].Localiz, "%02d", estado->sala_actual_id);
                printf("Has soltado: %s en la sala.\n", estado->objetos[i].Nomb_obj);
                return;
            }
        }
    }
    printf("No tienes ese objeto en tu inventario.\n");
}

void inventario(Partida *estado) {
    printf("\n--- TU INVENTARIO ---\n");
    int hay_objetos = 0;
    
    // Listar todos los objetos del inventario con sus descripciones
    for (int i = 0; i < estado->num_objetos; i++) {
        if (strcmp(estado->objetos[i].Localiz, "Inventario") == 0) {
            printf(" - [%s] %s: %s\n", 
                   estado->objetos[i].Id_obj, 
                   estado->objetos[i].Nomb_obj, 
                   estado->objetos[i].Descrip);
            hay_objetos = 1;
        }
    }
    if (!hay_objetos) printf("Tu inventario esta vacio.\n");
}

void usar_objeto(Partida *estado) {
    char id_buscado[5];
    printf("\n--- USAR OBJETO ---\n");
    printf("Introduce el ID del objeto que quieres usar: ");
    scanf("%4s", id_buscado);

    // 1. Verificar si el jugador tiene el objeto en el inventario
    int lo_tiene = 0;
    for (int i = 0; i < estado->num_objetos; i++) {
        if (strcmp(estado->objetos[i].Id_obj, id_buscado) == 0 && 
            strcmp(estado->objetos[i].Localiz, "Inventario") == 0) {
            lo_tiene = 1;
            break;
        }
    }

    if (!lo_tiene) {
        printf("No tienes ese objeto en tu inventario.\n");
        return;
    }

    // 2. Comprobar si desbloquea alguna conexión adyacente
    int usado = 0;
    for (int i = 0; i < estado->num_conexiones; i++) {
        if (estado->conexiones[i].Id_origen == estado->sala_actual_id &&
            strcmp(estado->conexiones[i].Estado, "Bloqueada") == 0 &&
            strcmp(estado->conexiones[i].Condicion, id_buscado) == 0) {
            
            // Cambiar el estado a ABIERTA / Activa
            strcpy(estado->conexiones[i].Estado, "Activa");
            printf("¡Exito! Has usado el objeto y la conexion hacia la sala %02d ahora esta Activa.\n", 
                   estado->conexiones[i].Id_destino);
            usado = 1;
        }
    }

    if (!usado) {
        // Informar si no es posible aplicarlo
        printf("No es posible aplicar este objeto aqui.\n"); 
    }
}

void resolver(Partida *estado) {
    printf("\n--- RESOLVER PUZLE / CODIGO ---\n");
    
    // Buscar si hay alguna conexión bloqueada por un puzle en esta sala
    for (int i = 0; i < estado->num_conexiones; i++) {
        if (estado->conexiones[i].Id_origen == estado->sala_actual_id &&
            strcmp(estado->conexiones[i].Estado, "Bloqueada") == 0) {
            
            // Si la condición empieza por 'P', es un puzle (ej. P01)
            if (estado->conexiones[i].Condicion[0] == 'P') {
                char *id_puzle = estado->conexiones[i].Condicion;
                
                // Buscar el puzle en el vector de puzles
                for (int j = 0; j < estado->num_puzles; j++) {
                    if (strcmp(estado->puzles[j].Id_puzle, id_puzle) == 0) {
                        
                        // Mostrar descripción y pedir solución
                        printf("\n[PUZLE ENCONTRADO]: %s\n", estado->puzles[j].Descrip);
                        printf("Introduce la solucion (%s): ", estado->puzles[j].Tipo);
                        
                        char respuesta[51];
                        while (getchar() != '\n'); // Limpiar buffer
                        fgets(respuesta, 51, stdin);
                        respuesta[strcspn(respuesta, "\r\n")] = 0;

                        if (strcmp(respuesta, estado->puzles[j].Sol) == 0) {
                            printf("¡Correcto! El acceso ha sido desbloqueado.\n");
                            strcpy(estado->conexiones[i].Estado, "Activa"); // Desbloqueo
                        } else {
                            printf("Respuesta incorrecta. Nada sucede.\n");
                        }
                        return; // Salimos de la función tras intentar el puzle
                    }
                }
            }
        }
    }
    printf("No hay ningun panel ni puzle que resolver en esta sala en este momento.\n");
}

void guardar_partida(Partida *estado) {
    printf("\n--- GUARDANDO PARTIDA ---\n");
    printf("Procesando tu progreso actual...\n");
    
    // Llamamos al módulo de memoria que es el que sabe cómo escribir en el .txt
    guardarDatosFicheros(estado);
    
    // Al volver, le confirmamos al jugador que puede seguir jugando o salir
    printf("Volviendo al menu de la sala...\n");
}