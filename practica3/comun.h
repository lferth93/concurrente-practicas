typedef struct instancia{
    float p_cruza;
    float p_mutacion;
    float maxima;
    int n_objetos;
    float *area;
    float *longitud;
} instancia;

instancia *leer_instancia(char *nombre_archivo);

typedef struct cromosoma{
    long long int genotipo;
    float peso;
    float aptitud;
} cromosoma;

void copiar_cromosoma(cromosoma *origen, cromosoma *destino);

void actualizar_aptitud(cromosoma *c, instancia *inst);

cromosoma *crear_arreglo_cromosomas(int n, instancia *inst);

cromosoma *seleccion(cromosoma *poblacion, int n);

void cruzar(cromosoma *padre1, cromosoma *padre2, float pc);
void cruzar_poblacion(cromosoma *poblacion, int n, float pc);
void mutar(cromosoma *c, int n, float pm);

void limpiar_poblacion(cromosoma *poblacion, int n);

cromosoma *mejor_cromosoma(cromosoma *poblacion, int n);

void imprimir_poblacion(cromosoma *poblacion, int n);
void imprimir_cromosoma(cromosoma *c);
