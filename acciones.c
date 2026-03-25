#include <stdio.h>
#include "ficheros.h"

void menu_de_partida(char *Id_sala, Salas *salas, int num_salas, Objetos *objetos, int num_objetos, Conexiones *conexiones, int num_conexiones, Puzles *puzle, int num_puzles);void describir_sala(char *Id_sala, Salas sala_actual Objetos *objetos, int num_objetos);
void describir(char *Id_sala, Salas *salas, int num_salas);
void examinar(char *Id_sala, Salas *salas, int num_salas, Conexiones *conexiones, int num_conexiones, Objetos *objetos, int num_objetos)
void entrar_sala(char *Id_sala, Salas *salas, int num_salas, Conexiones *conexiones, int num_conexiones);
void coger_objeto(char *Id_sala, Objetos *objetos, int num_objetos);
void soltar_objeto(char *Id_sala, Objetos *objetos, int num_objetos);
void inventario(Objetos *objetos, int num_objetos);
void usar_objeto(char *Id_sala, Objetos *objeto, int num_objetos, Conexiones *conexion, int num_conexiones);
void resolver(char *Id_sala, Puzles *puzle, int num_puzles, Conexiones *conexion, int num_conexiones);

//Cabecera: void menu_de_partida(char *Id_sala, Salas *salas, int num_salas, Objetos *objetos, int num_objetos, Conexiones *conexiones, int num_conexiones, Puzles *puzle, int num_puzles);
//Precondici�n: Est�n almacenados en los registros los datos de la partida
//Postcondicion: Permite elegir las distintas acciones en el juego, incluyendo volver al men� principal
void menu_de_partida(char *Id_sala, Salas *salas, int num_salas, Objetos *objetos, int num_objetos, Conexiones *conexiones, int num_conexiones, Puzles *puzle, int num_puzles);{
    int regresar=0, accion, salir=0;
    do{

    printf("===================================================================\n");
    printf("Escriba el numero correspondiente a la accion que desea realizar:\n");
    printf("1. Describir sala\n");
    printf("2. Examinar (objetos y salidas)\n");
    printf("3. Entrar en otra sala\n"):
    printf("4. Coger objeto\n");
    printf("5. Soltar objeto\n");
    printf("6. Inventario\n");
    printf("7. Usar objeto\n");
    printf("8. Resolver puzzle/Introducir codigo\n");
    printf("9. Guardar partida\n");
    printf("10. Volver\n");
    do{
        scanf("%i", &accion);
    }while((accion<1)||(accion>10));
    switch(accion){
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;
    case 7:

        break;
    case 8:

        break;
    case 9:

        break;
    case 10:
        printf("�De verdad desea salir? Se perdera el progreso desde la ultima vez que se guardo partida.");
        printf("Introduzca 1 para salir de la partida al menu de inicio, introduzca cualquier otro numero para volver a la partida:\n");
        scanf("%i", &salir);
        if(salir){regresar=1;}
        break;
    }
    }while(regresar==0);
}

//Cabecera:
