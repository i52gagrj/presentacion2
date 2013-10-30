#ifndef __PRACTICA_H__
#define __PRACTICA_H__

#include "grafo.h"

class Grafo;

//! Clase principal

/*!
    Esta es la clase principal del interfaz de usuario.
 */

class Practica
{

  public:
    Practica ();
    ~Practica();
    void nuevo();
    void guardarGrafo();
    void cargarGrafo();
    void verGrafo();
    void verDijkstra();
    void verFloyd();	
    void verCiclos();	
    void verWarshall();
    void verProfundidad();
    void verPrim();
    void verTopologica();
    void ProvinciasDijkstra();
    void ProvinciasFloyd();
    void cargarProvincias();		
    int menu();
   
  private:    
    //Grafo con el que trabajará la aplicación
    Grafo *_grafo;

};




#endif
