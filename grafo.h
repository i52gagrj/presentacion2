#ifndef __GRAFO_H__
#define __GRAFO_H__

//! Clase grafo

/*!
    Esta es la clase que representa a un grafo, sea este dirigido
    o no dirigido.
 */
class Grafo 
{
  public:
    Grafo( int n, int dirigido = 0 /*parametro por defecto*/ );
    ~Grafo();

    //Funciones auxiliares para el constructor y destructor.
    void inicializar( int n , int tipo);
    void liberar();

    int numeroNodos() const;
    void numeroNodos(int n);
    int dirigido();
    void dirigido(int tipo);
    void algoritmoDijkstra();
    void algoritmoFloyd();
    void potenciaMatriz(int **conexion, int n);	
    void ciclosMatriz();
    void algoritmoWarshall();
    void busquedaProfundidad();
    void arbolPrim();
    void algoritmoTopologica();
    void provDijkstra();
    void provFloyd();
    void mostrarProvincias(char **provincias);

    typedef int TipoPeso;

    // Asigna un peso a un lado
    /*
        i: Nodo Origen.
        j: Nodo Destino.
        valor Peso del lado.
    */
    void asignarPeso( int i, int j, TipoPeso valor );
    
    // Muestra el peso de un lado
    TipoPeso verPeso( int i, int j );

    //Para introducir todos los pesos de los lados del grafo
    void introducirPesos();

    //Para ver todos los pesos de los lados del grafo
    void verPesos();
    
    // Valor del peso de un lado no existente
    static const TipoPeso INFINITO=32000;

    private:
      
      // Número de nodos del grafo.
      int _numeroNodos;
      int _dirigido;

      // Matriz de conexiones del grafo.
      TipoPeso **_matriz;
};

#endif
