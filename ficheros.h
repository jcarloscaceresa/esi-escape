#ifndef FICHEROS_H
#define FICHEROS_H

typedef struct {
    int Id_jugador;            // 2 dígitos 
    char Nomb_jugador[21];     // 20 caracteres máximo
    char Jugador[11];          // 10 caracteres 
    char Contrasena[9];        // 8 caracteres 
    char **Inventario;         // Memoria dinámica para IDs de objetos 
} Jugadores;

typedef struct {
    int Id_sala;               // 2 dígitos 
    char Nomb_sala[31];        // 30 caracteres máximo 
    char Tipo[20];             // 20 caracteres máximo (Inicial, Normalo Salida)
    char Descrip[151];         // 150 caracteres máximo 
} Salas;

typedef struct {
    char Id_conexion[4];       // 3 caracteres máximo
    int Id_origen;             // 2 dígitos 
    int Id_destino;            // 2 dígitos 
    char Estado[15];           // Activa o Bloqueada 
    char Condicion[5];         // 0 si no aplica, Id_obj o Id_puzle 
} Conexiones;

typedef struct {
    char Id_obj[5];            // 4 caracteres 
    char Nomb_obj[16];         // 15 caracteres máximo
    char Descrip[51];          // 50 caracteres máximo 
    char Localiz[15];          // Id_sala o Inventario 
} Objetos;

typedef struct {
    char Id_puzle[4];          // 3 caracteres 
    char Nomb_puz[16];         // 15 caracteres máximo 
    int Id_sala;               // 2 dígitos 
    char Tipo[10];             // Código o Palabra 
    char Descrip[151];         // 150 caracteres máximo 
    char Sol[51];              // 50 caracteres máximo 
} Puzles;

typedef struct {
    Jugadores *jugadores;
    int num_jugadores;
    Salas *salas;
    int num_salas;
    Objetos *objetos;
    int num_objetos;
    Conexiones *conexiones;
    int num_conexiones;
    Puzles *puzles;
    int num_puzles;
    int sala_actual_id;      
    Jugadores *jugador_actual; 
} Partida;

#endif