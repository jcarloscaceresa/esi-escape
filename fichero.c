
#include "fichero.h"

/* --- LECTURA DE FICHEROS Y EXTRACCIÓN DE DATOS --- */

Salas* cargar_fichero_salas(const char* nombre_fichero, int* num_salas) {
    FILE* f = fopen(nombre_fichero, "r");
    if (!f) return NULL;

    Salas* salas = NULL;
    *num_salas = 0;
    char linea[256];

    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0; // Quitar salto de línea
        if (strlen(linea) == 0) continue;

        Salas s;
        memset(&s, 0, sizeof(Salas)); // Inicializar

        char* token = strtok(linea, "-");
        if (token) strncpy(s.Id_sala, token, sizeof(s.Id_sala) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(s.Nomb_sala, token, sizeof(s.Nomb_sala) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(s.Tipo, token, sizeof(s.Tipo) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(s.Descrip, token, sizeof(s.Descrip) - 1);

        // Llamada al módulo de memoria
        salas = agregar_sala_memoria(salas, num_salas, s);
    }
    fclose(f);
    return salas;
}

Conexion* cargar_fichero_conexiones(const char* nombre_fichero, int* num_conexiones) {
    FILE* f = fopen(nombre_fichero, "r");
    if (!f) return NULL;

    Conexiones* conexiones = NULL;
    *num_conexiones = 0;
    char linea[256];

    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;

        Conexiones c;
        memset(&c, 0, sizeof(Conexion));

        char* token = strtok(linea, "-");
        if (token) strncpy(c.Id_conexion, token, sizeof(c.Id_conexion) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(c.id_origen, token, sizeof(c.Id_origen) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(c.Id_destino, token, sizeof(c.Id_destino) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(c.Estado, token, sizeof(c.Estado) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(c.Cond, token, sizeof(c.Cond) - 1);

        conexiones = agregar_conexion_memoria(conexiones, num_conexiones, c);
    }
    fclose(f);
    return conexiones;
}

Objetos* cargar_fichero_objetos(const char* nombre_fichero, int* num_objetos) {
    FILE* f = fopen(nombre_fichero, "r");
    if (!f) return NULL;

    Objetos* objetos = NULL;
    *num_objetos = 0;
    char linea[256];

    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;

        Objeto o;
        memset(&o, 0, sizeof(Objeto));

        char* token = strtok(linea, "-");
        if (token) strncpy(o.Id_obj, token, sizeof(o.Id_obj) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(o.Nomb_obj, token, sizeof(o.Nomb_obj) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(o.Descrip, token, sizeof(o.Descrip) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(o.Localiz, token, sizeof(o.Localiz) - 1);

        objetos = agregar_objeto_memoria(objetos, num_objetos, o);
    }
    fclose(f);
    return objetos;
}

Puzles* cargar_fichero_puzles(const char* nombre_fichero, int* num_puzles) {
    FILE* f = fopen(nombre_fichero, "r");
    if (!f) return NULL;

    Puzles* puzles = NULL;
    *num_puzles = 0;
    char linea[512];

    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;

        Puzles p;
        memset(&p, 0, sizeof(Puzle));

        char* token = strtok(linea, "-");
        if (token) strncpy(p.Id_puzle, token, sizeof(p.Id_puzle) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(p.Nomb_puz, token, sizeof(p.Nomb_puz) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(p.Id_sala, token, sizeof(p.Id_sala) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(p.Tipo, token, sizeof(p.Tipo) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(p.Descrip, token, sizeof(p.Descrip) - 1);

        token = strtok(NULL, "-");
        if (token) strncpy(p.Sol, token, sizeof(p.Sol) - 1);

        puzles = agregar_puzle_memoria(puzles, num_puzles, p);
    }
    fclose(f);
    return puzles;
}

//guarda los estados actualizados en los ficheros cuando el programa termine

int guardar_fichero_objetos(const char* nombre_fichero, Objetos* objetos, int num_objetos) {
    FILE* f = fopen(nombre_fichero, "w");
    if (!f) return 0;

    for (int i = 0; i < num_objetos; i++) {
        fprintf(f, "%s-%s-%s-%s\n", objetos[i].id_obj, objetos[i].nomb_obj, objetos[i].descrip, objetos[i].localiz);
    }

    fclose(f);
    return 1;
}

int guardar_fichero_conexiones(const char* nombre_fichero, Conexion* conexiones, int num_conexiones) {
    FILE* f = fopen(nombre_fichero, "w");
    if (!f) return 0;

    for (int i = 0; i < num_conexiones; i++) {
        fprintf(f, "%s-%s-%s-%s-%s\n", conexiones[i].id_conexion, conexiones[i].id_origen, conexiones[i].id_destino, conexiones[i].estado, conexiones[i].cond);
    }

    fclose(f);
    return 1;
}
