#include "practica.h"
#include "grafo.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring> //Para el uso de c_str()
#include <fstream> //Para trabajar con ficheros

#include <iostream>
using namespace std;



/*!
    Construye un objeto de la clase Practica.

 */
Practica::Practica ()
{
  bool grafoIntroducido = false;
  int opcion;

  do
  {
    opcion = menu();
    switch (opcion)
    {
      case 1:
        nuevo(); //Introducir grafo por teclado
        grafoIntroducido = true;
        getchar();
        getchar();
        break;

      case 2: //Guardar grafo en fichero
        if ( grafoIntroducido )
          guardarGrafo();
        else
          cout << "Primero tiene que introducir un grafo por teclado\n";
        getchar();
        getchar();
        break;

      case 3: // Cargar grafo desde fichero
	// Si hay un grafo introducido se libera.
        if ( grafoIntroducido ) 
	{
		_grafo->liberar(); 
		cout << "Grafo liberado \n";
	}
	//Se carga el grafo
        cargarGrafo();
        getchar();
        getchar();
        grafoIntroducido = true;
	cout << "Grafo cargado desde fichero \n";
        break;
     case 4: //Ver el grafo introducido en pantalla
	if ( grafoIntroducido )
	  verGrafo();	
	else 
          cout << "Primero tiene que introducir un grafo por teclado\n";
        getchar();
        getchar();
	break;
     case 5: //Ver los caminos minimos mediante Dijkstra
	if ( grafoIntroducido )
	  verDijkstra();	
	else 
          cout << "Primero tiene que introducir un grafo por teclado\n";
        getchar();
        getchar();
	break;
     case 6: //Ver los caminos minimos mediante Floyd
	if ( grafoIntroducido )
	  verFloyd();	
	else 
          cout << "Primero tiene que introducir un grafo por teclado\n";
        getchar();
        getchar();
	break;
     case 7: //Ver los ciclos de un determinado orden mediante potencias
	if ( grafoIntroducido )
	  verCiclos();	
	else 
          cout << "Primero tiene que introducir un grafo por teclado\n";
        getchar();
        getchar();
	break;
     case 8: //Ver si hay conexiones entre los nodos
	if ( grafoIntroducido )
	  verWarshall();	
	else 
          cout << "Primero tiene que introducir un grafo por teclado\n";
        getchar();
        getchar();
	break;

     case 9: //Realizar la busqueda en profundidad
	if ( grafoIntroducido )
	  verProfundidad();	
	else 
          cout << "Primero tiene que introducir un grafo por teclado\n";
        getchar();
        getchar();
	break;
     case 10: //Ver el arbol abarcador por el algoritmo de Prim
	if ( grafoIntroducido )
	  verPrim();	
	else 
          cout << "Primero tiene que introducir un grafo por teclado\n";
        getchar();
        getchar();
	break;
     case 11: //Ver el arbol abarcador por el algoritmo de Prim
	if ( grafoIntroducido )
	  verTopologica();	
	else 
          cout << "Primero tiene que introducir un grafo por teclado\n";
        getchar();
        getchar();
	break;
     case 12: //Ver el arbol abarcador por el algoritmo de Prim
        if ( grafoIntroducido ) 
	{
		_grafo->liberar(); 
		cout << "Grafo liberado \n";
	}	
        cargarProvincias();
        grafoIntroducido = true;
	ProvinciasDijkstra();
        getchar();
        getchar();
	break;
     case 13: //Ver el arbol abarcador por el algoritmo de Prim
        if ( grafoIntroducido ) 
	{
		_grafo->liberar(); 
		cout << "Grafo liberado \n";
	}	
        cargarProvincias();
        grafoIntroducido = true;
	ProvinciasFloyd();
        getchar();
        getchar();
	break;
    }
  }while (opcion!=0);
}

//! Destruye un objeto de la clase Practica.

/*!
    Destruye un objeto de la clase Practica.
 */

Practica::~Practica()
{

}

int Practica::menu()
{
  int opcion;
  
  system("clear");
  cout << "  0. ................................Salir\n";
  cout << "  1. .....................Introducir Grafo\n";
  cout << "  2. .............Guardar grafo en fichero\n";
  cout << "  3. ...........Cargar grafo desde fichero\n";
  cout << "  4. ...............Ver grafo por pantalla\n";
  cout << "  5. ................Algoritmo de Dijkstra\n";
  cout << "  6. ...................Algoritmo de Floyd\n";
  cout << "  7. .................Ver ciclos del grafo\n";	
  cout << "  8. ...............Ver matriz de Warshall\n";	
  cout << "  9. ..........Ver busqueda en Profundidad\n";	
  cout << " 10. ....................Ver arbol de Prim\n";
  cout << " 11. .............Clasificación Topológica\n";	
  cout << " 12. ...............Dijkstra en provincias\n";	
  cout << " 13. ..................Floyd en provincias\n";	

  cout << "Introduzca opcion...:";
  cin >> opcion;

  return opcion;  
}


//! Crea un nuevo grafo.

/*!
    Crea un nuevo grafo, introduciendo el tipo, numero de nodos y otro para introducir pesos.
 */
void Practica::nuevo()
{
  int numeroNodos;
  int dirigido;

  do
  {
    cout << "Numero de Nodos: ";
    cin >> numeroNodos;
  } while(numeroNodos <= 0);

  do
  {
    cout << "Tipo de grafo (dirigido = 1, no dirigido = 0): ";
    cin >> dirigido;
  } while (dirigido != 0 && dirigido != 1);
 
  _grafo = new Grafo(numeroNodos, dirigido);
  _grafo->introducirPesos();

}

void Practica::guardarGrafo()
{
  string nombreFichero;

  cout << "Nombre del fichero: ";
  cin >> nombreFichero;

  ofstream f(nombreFichero.c_str()); //Se define el stream de escritura y se abre el fichero. 
	//c_str convierte el string a cadena de c.

  f << _grafo->numeroNodos() << endl; //Se guarda el numero de nodos.
  f << _grafo->dirigido() << endl; //Se guarda el tipo de grafo.

  //Se guarda la matriz de conexion por filas.
  for(int i = 0; i < _grafo->numeroNodos(); i++)
  {
    for(int j = 0; j < _grafo->numeroNodos(); j++)
      f << _grafo->verPeso(i, j) << " ";
    f << endl;
  }

  f.close(); // Se cierra el fichero.
    
}


void Practica::cargarGrafo()
{
  string nombreFichero;
  cout << "Nombre del fichero: ";
  cin >> nombreFichero;

  ifstream f(nombreFichero.c_str()); //Se define el stream de lectura y se abre el fichero.
  //Se definen variables auxiliares para cargar el grafo.
  int nodos;
  int tipo;
  Grafo::TipoPeso aux;

  f >> nodos; //Se lee el numero de nodos.
  f >> tipo; //Se lee el tipo.

  _grafo = new Grafo(nodos, tipo); //Se reserva espacio para el grafo y se invoca al constructor.

  //Se carga la matriz de conexion desde el fichero.
  for(int i = 0; i < _grafo->numeroNodos(); i++)
    for(int j = 0; j < _grafo->numeroNodos(); j++)
    {
      f >> aux;
      _grafo->asignarPeso(i, j, aux);
    }

  f.close(); // Se cierra el fichero.
}

void Practica::cargarProvincias()
{
  ifstream f("matrizconexion.txt"); //Se define el stream de lectura y se abre el fichero.
  //Se definen variables auxiliares para cargar el grafo.
  int nodos;
  int tipo;
  Grafo::TipoPeso aux;

  f >> nodos; //Se lee el numero de nodos.
  f >> tipo; //Se lee el tipo.

  _grafo = new Grafo(nodos, tipo); //Se reserva espacio para el grafo y se invoca al constructor.

  //Se carga la matriz de conexion desde el fichero.
  for(int i = 0; i < _grafo->numeroNodos(); i++)
    for(int j = 0; j < _grafo->numeroNodos(); j++)
    {
      f >> aux;
      _grafo->asignarPeso(i, j, aux);
    }

  f.close(); // Se cierra el fichero.
}

void Practica::verGrafo()
{
	_grafo->verPesos();
}

void Practica::verDijkstra(){
	_grafo->algoritmoDijkstra();
}

void Practica::verFloyd(){
	_grafo->algoritmoFloyd();
}

void Practica::verCiclos(){
	_grafo->ciclosMatriz();
}

void Practica::verWarshall(){
	_grafo->algoritmoWarshall();
}

void Practica::verProfundidad(){
	_grafo->busquedaProfundidad();
}

void Practica::verPrim(){
	if(_grafo->dirigido()) cout << "\nEl grafo es dirigido, no es aplicable el algoritmo de Prim.";
	else _grafo->arbolPrim();
}

void Practica::verTopologica(){
	if(!_grafo->dirigido()) cout << "\nEl grafo es no dirigido, no es aplicable la clasificación topológica.";
	else _grafo->algoritmoTopologica();
}

void Practica::ProvinciasDijkstra(){
	_grafo->provDijkstra();
}

void Practica::ProvinciasFloyd(){
	_grafo->provFloyd();
}

