#ifndef __ALGORITMOSGRAFOS_H__
#define __ALGORITMOSGRAFOS_H__

#include "grafo.h"

class AlgoritmosGrafos
{
  public:
    //Al definirlas como estáticas pueden ser invocadas sin crear un objeto de la clase AlgoritmosGrafos.
    static void dijkstra(Grafo *g, Grafo::TipoPeso *distancia, int *predecesor, int nodoOrigen);
    static void caminoDijkstra(int *predecesor, int nodoOrigen, int nodoDestino);
    static void caminoDijkstraProv(int *predecesor, int nodoOrigen, int nodoDestino, char **provincias);
    static void floyd(Grafo *g, Grafo::TipoPeso **distancia, int **intermedios);
    static void caminoFloyd(int **intermedios, int nodoOrigen, int nodoDestino);
    static void caminoFloydProv(int **intermedios, int nodoOrigen, int nodoDestino, char **provincias);
    void Warshall(Grafo *g, int **conexion);
    void profundidad(Grafo *g);
    void recorridoProfundidad(Grafo *g, int i, int *visitado, int *numeroProf, int *numeroDesc, int &contador, int **lados);
    void topologica(Grafo *g);
    void clasificacionTopologica(Grafo *g, int i, int *visitado);
    void algoritmoPrim(Grafo *g);
    void Prim(Grafo *g, Grafo::TipoPeso **arbol);	 
    void clasifComp(Grafo *g, int *numeroProf, int *numeroDesc, int **lados);	
};




#endif
