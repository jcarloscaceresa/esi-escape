#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memoria.h"

// --- 1. CARGAR DATOS A LA MEMORIA ---
void cargarDatosMemoria(Partida *estado) {

    // ==========================================
    // CARGAR SALAS (Salas.txt)
    // ==========================================
    FILE *f_salas = fopen("Salas.txt", "r");
    if (f_salas == NULL) {
        printf("Error: No se encuentra Salas.txt\n");
    } else {
        char linea[256];
        estado->num_salas = 0; // Empezamos en 0
        estado->salas = NULL;  // Puntero limpio

        // Leemos línea a línea
        while (fgets(linea, sizeof(linea), f_salas)) {
            linea[strcspn(linea, "\r\n")] = 0; // Limpiar salto de línea

            // Usamos realloc para hacer la mochila más grande por cada sala que encontramos
            estado->num_salas++;
            estado->salas = (Salas *)realloc(estado->salas, estado->num_salas * sizeof(Salas));

            // Cortamos la línea por los guiones
            char *id_str = strtok(linea, "-");
            char *nombre = strtok(NULL, "-");
            char *tipo = strtok(NULL, "-");
            char *descrip = strtok(NULL, "-");

            // Guardamos en la última posición del vector que acabamos de crear
            int indice = estado->num_salas - 1;
            
            if (id_str != NULL && nombre != NULL && tipo != NULL && descrip != NULL) {
                estado->salas[indice].Id_sala = atoi(id_str);
                strncpy(estado->salas[indice].Nomb_sala, nombre, 30);
                strncpy(estado->salas[indice].Tipo, tipo, 20);
                strncpy(estado->salas[indice].Descrip, descrip, 150);

                // ¡LA MAGIA DE LA SALA INICIAL!
                // Si el tipo de sala que acabamos de leer es "INICIAL", colocamos al jugador aquí
                if (strcmp(estado->salas[indice].Tipo, "INICIAL") == 0) {
                    estado->sala_actual_id = estado->salas[indice].Id_sala;
                }
            }
        }
        fclose(f_salas);
    }

    // ==========================================
    // CARGAR OBJETOS (Objetos.txt)
    // ==========================================
    FILE *f_obj = fopen("Objetos.txt", "r");
    if (f_obj == NULL) {
        printf("Error: No se encuentra Objetos.txt\n");
    } else {
        char linea[256];
        estado->num_objetos = 0;
        estado->objetos = NULL;

        while (fgets(linea, sizeof(linea), f_obj)) {
            linea[strcspn(linea, "\r\n")] = 0;

            estado->num_objetos++;
            estado->objetos = (Objetos *)realloc(estado->objetos, estado->num_objetos * sizeof(Objetos));
            int i = estado->num_objetos - 1;

            // Formato según PDF: Id_obj-Nomb_obj-Descrip-Localiz [cite: 78-81]
            char *id_obj  = strtok(linea, "-");
            char *nombre  = strtok(NULL, "-");
            char *descrip = strtok(NULL, "-");
            char *localiz = strtok(NULL, "-");

            if (id_obj != NULL && nombre != NULL && descrip != NULL && localiz != NULL) {
                // Copiamos los datos a la estructura
                strncpy(estado->objetos[i].Id_obj, id_obj, 5);
                strncpy(estado->objetos[i].Nomb_obj, nombre, 15);
                strncpy(estado->objetos[i].Descrip, descrip, 50);
                strncpy(estado->objetos[i].Localiz, localiz, 15);
            }
        }
        fclose(f_obj);
    }

    // ==========================================
    // CARGAR CONEXIONES (Conexiones.txt)
    // ==========================================
    FILE *f_con = fopen("Conexiones.txt", "r");
    if (f_con == NULL) {
        printf("Error: No se encuentra Conexiones.txt\n");
    } else {
        char linea[256];
        estado->num_conexiones = 0;
        estado->conexiones = NULL;

        while (fgets(linea, sizeof(linea), f_con)) {
            linea[strcspn(linea, "\r\n")] = 0;
            
            // ESCUDO 1: Ignorar líneas en blanco
            if (strlen(linea) < 5) continue;

            estado->num_conexiones++;
            estado->conexiones = (Conexiones *)realloc(estado->conexiones, estado->num_conexiones * sizeof(Conexiones));
            int i = estado->num_conexiones - 1;

            char *id_con  = strtok(linea, "-");
            char *origen  = strtok(NULL, "-");
            char *destino = strtok(NULL, "-");
            char *estado_con = strtok(NULL, "-");
            char *condicion = strtok(NULL, "-");

            if (id_con != NULL && origen != NULL && destino != NULL && estado_con != NULL && condicion != NULL) {
                // ESCUDO 2: Usar sizeof para no desbordar JAMÁS la memoria
                strncpy(estado->conexiones[i].Id_conexion, id_con, sizeof(estado->conexiones[i].Id_conexion) - 1);
                estado->conexiones[i].Id_origen = atoi(origen);
                estado->conexiones[i].Id_destino = atoi(destino);
                strncpy(estado->conexiones[i].Estado, estado_con, sizeof(estado->conexiones[i].Estado) - 1);
                strncpy(estado->conexiones[i].Condicion, condicion, sizeof(estado->conexiones[i].Condicion) - 1);
            }
        }
        fclose(f_con);
    }

    // ==========================================
    // CARGAR PUZLES (Puzles.txt)
    // ==========================================
    FILE *f_puz = fopen("Puzles.txt", "r");
    if (f_puz == NULL) {
        printf("Error: No se encuentra Puzles.txt\n");
    } else {
        char linea[256];
        estado->num_puzles = 0;
        estado->puzles = NULL;

        while (fgets(linea, sizeof(linea), f_puz)) {
            linea[strcspn(linea, "\r\n")] = 0;
            
            // ESCUDO 1: Ignorar líneas en blanco
            if (strlen(linea) < 5) continue;

            estado->num_puzles++;
            estado->puzles = (Puzles *)realloc(estado->puzles, estado->num_puzles * sizeof(Puzles));
            int i = estado->num_puzles - 1;

            char *id_puzle = strtok(linea, "-");
            char *nombre   = strtok(NULL, "-");
            char *sala     = strtok(NULL, "-");
            char *tipo     = strtok(NULL, "-");
            char *descrip  = strtok(NULL, "-");
            char *solucion = strtok(NULL, "-");

            if (id_puzle != NULL && nombre != NULL && sala != NULL && tipo != NULL && descrip != NULL && solucion != NULL) {
                // ESCUDO 2: Límites de seguridad automáticos
                strncpy(estado->puzles[i].Id_puzle, id_puzle, sizeof(estado->puzles[i].Id_puzle) - 1);
                strncpy(estado->puzles[i].Nomb_puz, nombre, sizeof(estado->puzles[i].Nomb_puz) - 1);
                estado->puzles[i].Id_sala = atoi(sala);
                strncpy(estado->puzles[i].Tipo, tipo, sizeof(estado->puzles[i].Tipo) - 1);
                strncpy(estado->puzles[i].Descrip, descrip, sizeof(estado->puzles[i].Descrip) - 1);
                strncpy(estado->puzles[i].Sol, solucion, sizeof(estado->puzles[i].Sol) - 1);
            }
        }
        fclose(f_puz);
    }
}


// --- 2. GUARDAR DATOS EN FICHEROS ---
void guardarDatosFicheros(Partida *estado) {
    if (estado->jugador_actual == NULL) {
        printf("\nError: No hay un jugador activo para guardar la partida.\n");
        return;
    }

    int id_actual = estado->jugador_actual->Id_jugador;

    // 1. Abrimos el original para leer y el temporal para escribir
    FILE *f_orig = fopen("Partida.txt", "r");
    FILE *f_temp = fopen("Temp.txt", "w");

    if (f_temp == NULL) {
        printf("\nError: No se pudo crear el archivo de guardado.\n");
        if (f_orig != NULL) fclose(f_orig);
        return;
    }

    // 2. Si hay partidas previas, copiamos a los DEMÁS jugadores
    if (f_orig != NULL) {
        char linea[256];
        int copiando = 1; // 1 = Copiamos la línea, 0 = La ignoramos

        while (fgets(linea, sizeof(linea), f_orig)) {
            // Detectamos si empieza el bloque de un jugador [cite: 98]
            if (strncmp(linea, "JUGADOR:", 8) == 0) {
                int id_leido;
                // Extraemos el ID del jugador de esa línea
                sscanf(linea, "JUGADOR: %d", &id_leido);

                // Si es el jugador actual, dejamos de copiar (estamos borrando su partida vieja)
                if (id_leido == id_actual) {
                    copiando = 0;
                } else {
                    copiando = 1; // Si es otro jugador distinto, sí lo copiamos
                }
            }

            // Escribimos la línea en el temporal solo si pertenece a otro jugador
            if (copiando == 1) {
                fprintf(f_temp, "%s", linea);
            }
        }
        fclose(f_orig);
    }

    // 3. Añadimos la partida NUEVA del jugador actual al final del temporal
    // Nos aseguramos de poner un salto de línea por si el archivo anterior no lo tenía
    fprintf(f_temp, "\nJUGADOR: %02d\n", id_actual);
    fprintf(f_temp, "SALA: %02d\n", estado->sala_actual_id);

    // Guardar Objetos [cite: 100]
    for (int i = 0; i < estado->num_objetos; i++) {
        if (strcmp(estado->objetos[i].Localiz, "Inventario") == 0) {
            fprintf(f_temp, "OBJETO: %s-%s\n", estado->objetos[i].Id_obj, estado->objetos[i].Localiz);
        }
    }

    // Guardar Conexiones desbloqueadas [cite: 101]
    for (int i = 0; i < estado->num_conexiones; i++) {
        if (strcmp(estado->conexiones[i].Estado, "Activa") == 0) {
            fprintf(f_temp, "CONEXION: %s-%s\n", estado->conexiones[i].Id_conexion, estado->conexiones[i].Estado);
        }
    }

    fclose(f_temp);

    // 4. El truco final: Borramos el original y renombramos el temporal
    remove("Partida.txt");
    rename("Temp.txt", "Partida.txt");

    printf("\n¡Partida guardada correctamente respetando a los demas jugadores!\n");
}


// --- 3. LIBERAR MEMORIA (LIMPIEZA FINAL) ---
void liberarDatosMemoria(Partida *estado) {
    // Liberamos toda la memoria dinámica que pedimos con malloc y realloc
    if (estado->salas != NULL) {
        free(estado->salas);
        estado->salas = NULL;
    }
    if (estado->objetos != NULL) {
        free(estado->objetos);
        estado->objetos = NULL;
    }
    if (estado->conexiones != NULL) {
        free(estado->conexiones);
        estado->conexiones = NULL;
    }
    if (estado->puzles != NULL) {
        free(estado->puzles);
        estado->puzles = NULL;
    }
    if (estado->jugador_actual != NULL) {
        free(estado->jugador_actual);
        estado->jugador_actual = NULL;
    }
    
    printf("\nMemoria liberada con exito. ¡Adios!\n");
}