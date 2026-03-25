void menu_de_partida(char *Id_sala, Salas *salas, int num_salas, Objetos *objetos, int num_objetos, Conexiones *conexiones, int num_conexiones, Puzles *puzle, int num_puzles);
void describir(char *Id_sala, Salas *salas, int num_salas);
void examinar(char *Id_sala, Salas *salas, int num_salas, Conexiones *conexiones, int num_conexiones, Objetos *objetos, int num_objetos)
void entrar_sala(char *Id_sala, Salas *salas, int num_salas, Conexiones *conexiones, int num_conexiones);
void coger_objeto(char *Id_sala, Objetos *objetos, int num_objetos);
void soltar_objeto(char *Id_sala, Objetos *objetos, int num_objetos);
void inventario(Objetos *objetos, int num_objetos);
void usar_objeto(char *Id_sala, Objetos *objeto, int num_objetos, Conexiones *conexion, int num_conexiones);
void resolver(char *Id_sala, Puzles *puzle, int num_puzles, Conexiones *conexion, int num_conexiones);
