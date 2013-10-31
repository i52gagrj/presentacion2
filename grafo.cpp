#include "grafo.h"
#include "algoritmosgrafos.h"

#include <iostream>
#include <fstream>

using namespace std;

//Constructor
Grafo::Grafo( int n , int dirigido)
{
    inicializar( n , dirigido );
}


void Grafo::inicializar( int n , int tipo)
{
 //Esta funci�n debe hacer lo siguiente:
 //1. Asignar el n�mero de nodos y el tipo de grafo. 
 //2. Reservar memoria para la matriz de conexi�n.
 //3. Inicializar los pesos de lados del grafo al valor INFINITO.
 numeroNodos(n);
 dirigido(tipo);
 _matriz = new TipoPeso* [_numeroNodos];
 for (int i = 0; i < _numeroNodos; i++) 
        _matriz[i] = new TipoPeso[_numeroNodos];
 for(int i = 0; i< _numeroNodos; i++)
 {
	for(int j = 0; j< _numeroNodos; j++)
	{
		asignarPeso(i,j,INFINITO);
	}
 }
}

Grafo::~Grafo( void )
{
  liberar( );
}

void Grafo::liberar( void )
{
  // Esta funci�n ha de liberar la matriz de conexi�n del grafo.
    for (int i = 0; i < numeroNodos(); i++) {
        delete[] _matriz[i];
    }
    delete[] _matriz;	
}

//Funciones de interfaz para el n�mero de nodos
int Grafo::numeroNodos( void ) const
{
  return _numeroNodos;
}

void Grafo::numeroNodos( int n )
{
  _numeroNodos=n;
}

// Tipo del grafo

//Funciones de interfaz para el tipo de grafo
int Grafo::dirigido( void )
{
  return _dirigido;
}

void Grafo::dirigido(int tipo)
{
  _dirigido=tipo;
}

//Funciones de interfaz para el peso de un lado
// Asigna un peso a un lado

/*
   i: Origen del lado.
   j: Destino del lado.
   valor: Peso del lado.
 */

void Grafo::asignarPeso( int i, int j, int valor )
{
  _matriz[i][j]=valor;
}

Grafo::TipoPeso Grafo::verPeso( int i, int j )
{
  return _matriz[i][j];
}

//Funciones de interfaz para los pesos de todos los lados del grafo.
void Grafo::introducirPesos( )
{
  TipoPeso x;
  
  if (dirigido())
  {
    for ( int i = 0; i < numeroNodos(); i++) 
    {
      for ( int j = 0; j < numeroNodos(); j++) 
      {
        cout << "Peso lado (32000 si no existe)" << i << "," << j <<" : ";
        cin >> x;
        asignarPeso(i, j, x);
      }
    }
  }
  else
  {
    for ( int i = 0; i < numeroNodos(); i++) 
    {
      for ( int j = i; j < numeroNodos(); j++) 
      {
        cout << "Peso lado (32000 si no existe)" << i << "," << j <<" : ";
        cin >> x;
        asignarPeso(i, j, x);
        asignarPeso(j, i, x);
      }
    }
  }
}

void Grafo::verPesos( )
{
  for(int i = 0; i< numeroNodos(); i++)
  {
	for(int j = 0; j< numeroNodos(); j++)
	{
		cout << verPeso(i,j)<< " ";
	}
	cout << endl;
  }
}


void Grafo::algoritmoDijkstra()
{
	TipoPeso *distancias;
	int *predecesores;
	int origen;
	AlgoritmosGrafos CamMin;
	 
	//Reservamos memoria para los vectores predecesores y distancias
	predecesores = new int[numeroNodos()+1];
	distancias = new TipoPeso[numeroNodos()+1];

	//Pedimos el nodo desde el que encontrar los caminos
	cout << "Nodo origen: ";
	cin >> origen;

	//Ejecutamos la funci�n Dijkstra
	CamMin.dijkstra(this, distancias, predecesores, origen);

	//Mostramos los caminos m�nimos obtenidos
	for(int i = 0; i < numeroNodos();i++)
	{
		cout << " La distancia minima al nodo "<< i << " es " << distancias[i] << endl;
		cout << " El camino minimo al nodo " << i  <<"  es: ";
		CamMin.caminoDijkstra(predecesores, origen, i);
	}
	
	//Eliminamos de memoria los vectores
	delete distancias;
	delete predecesores;
}


//Llamada al algoritmo Floyd contenido en algoritmosgrafos
void Grafo::algoritmoFloyd()
{
	TipoPeso **distanciasFloyd;
 	int **intermedios;
	AlgoritmosGrafos CamMin;
 	
	//Reservamos memoria para las matrices distanciasFloyd e intermedios
        //Esto se ha puesto para llamar al commit
	distanciasFloyd = new TipoPeso* [numeroNodos()];
 	for (int i = 0; i < numeroNodos(); i++) 
        	distanciasFloyd[i] = new TipoPeso[numeroNodos()];
 
	intermedios = new int* [numeroNodos()];
 	for (int i = 0; i < numeroNodos(); i++) 
        	intermedios[i] = new int[numeroNodos()];

	//Ejecutamos la funci�n floyd
  	CamMin.floyd(this, distanciasFloyd, intermedios);

	//Mostramos los caminos
  	for(int i = 0; i < numeroNodos(); i++)
	{
   		for(int j = 0; j < numeroNodos(); j++)
   		{
    			cout << " \nLa distancia minima entre " << i << " y " << j << " es " << distanciasFloyd[i][j] << endl;
    			cout << "El camino minimo entre " << i << " y " << j << " es:";
    			CamMin.caminoFloyd(intermedios,i,j);
   		}
	}

	//Borramos las matrices de memoria
  	for(int i = 0; i < numeroNodos(); i++)
  	{
   		delete distanciasFloyd[i];
   		delete intermedios[i];
  	}

  	delete distanciasFloyd;
  	delete intermedios;
}

void Grafo::algoritmoWarshall()
{
	int **matrizConexion;
	int n;
	AlgoritmosGrafos Conexiones;

	matrizConexion = new int* [numeroNodos()];
 	for (int i = 0; i < numeroNodos(); i++) 
        	matrizConexion[i] = new int[numeroNodos()];
	
	for (int i=0; i < numeroNodos(); i++)
	{
		for (int j=0; j < numeroNodos(); j++)
		{
			if(verPeso(i,j)==32000) matrizConexion[i][j]=0;
			else matrizConexion[i][j]=1;
		}
	}

	Conexiones.Warshall(this, matrizConexion);
	
	cout << "Matriz Warshall \n";
	for (int i=0; i < numeroNodos(); i++)
	{
		for (int j=0; j < numeroNodos(); j++)
		{
			cout << matrizConexion[i][j]<< " ";
		}
		cout << endl;
	}
 	
}







void Grafo::ciclosMatriz()
{
	int **matrizConexion;
	int n;
	matrizConexion = new int* [numeroNodos()];
 	for (int i = 0; i < numeroNodos(); i++) 
        	matrizConexion[i] = new int[numeroNodos()];
	
	for (int i=0; i < numeroNodos(); i++)
	{
		for (int j=0; j < numeroNodos(); j++)
		{
			if(verPeso(i,j)==32000) matrizConexion[i][j]=0;
			else matrizConexion[i][j]=1;
		}
	}
	
	cout << "Indique el orden de los ciclos que quiere hallar: ";
	cin >> n;
	
	potenciaMatriz(matrizConexion, n);

	cout << "Matriz de conexi�n elevada a " << n << endl;	
	for (int i=0; i < numeroNodos(); i++)
	{
		for (int j=0; j < numeroNodos(); j++)
		{
			cout << matrizConexion[i][j]<< " ";
		}
		cout << endl;
	}

  	for(int i = 0; i < numeroNodos(); i++)
  	{
   		delete matrizConexion[i];
  	}

  	delete matrizConexion;
}

void Grafo::potenciaMatriz(int **conexion, int n)
{
	int **original;
	int **pivote;

	original = new int* [numeroNodos()];
 	for (int i = 0; i < numeroNodos(); i++) 
        	original[i] = new int[numeroNodos()];

	pivote = new int* [numeroNodos()];
 	for (int i = 0; i < numeroNodos(); i++) 
        	pivote[i] = new int[numeroNodos()];

	for (int i=0; i < numeroNodos(); i++)
	{
		for (int j=0; j < numeroNodos(); j++)
		{
			original[i][j] = conexion[i][j];
		}
	}

	for(int l=0;l<n-1;l++)
	{
		for(int i=0; i < numeroNodos(); i++)
		{			
			for(int j=0; j < numeroNodos(); j++)
			{
				pivote[i][j]=0;
				for(int k=0; k < numeroNodos(); k++)
				{
					pivote[i][j]=(pivote[i][j]+(conexion[i][k]*original[k][j]));
				}
			}
		}	

		for (int i=0; i < numeroNodos(); i++)
		{
			for (int j=0; j < numeroNodos(); j++)
			{
				conexion[i][j] = pivote[i][j];
			}
		}
		
	}	

  	for(int i = 0; i < numeroNodos(); i++)
  	{
   		delete pivote[i];
   		delete original[i];
  	}

  	delete pivote;
  	delete original;
}

void Grafo::busquedaProfundidad(){
	AlgoritmosGrafos BusqProf;
	BusqProf.profundidad(this);
}

void Grafo::arbolPrim(){
	AlgoritmosGrafos BusqPrim;
	BusqPrim.algoritmoPrim(this);
}

void Grafo::algoritmoTopologica(){
	AlgoritmosGrafos BusqProf;
	BusqProf.topologica(this);
}

void Grafo::provDijkstra(){
	TipoPeso *distancias;
	int *predecesores;
	int origen;
	AlgoritmosGrafos CamMin;
	char **provincias;
	 
	//Reservamos memoria para los vectores predecesores y distancias
	predecesores = new int[numeroNodos()+1];
	distancias = new TipoPeso[numeroNodos()+1];

	//Reservamos memoria y Cargamos la matriz de provincias
	provincias = new char*[numeroNodos()];
 	for (int i = 0; i < numeroNodos(); i++) 
        	provincias[i] = new char[20];
	
	mostrarProvincias(provincias);
	
	
	//Pedimos el nodo desde el que encontrar los caminos
	cout << "\n\nProvincia origen: ";
	cin >> origen;

	//Ejecutamos la funci�n Dijkstra
	CamMin.dijkstra(this, distancias, predecesores, origen);

	//Mostramos los caminos m�nimos obtenidos
	for(int i = 0; i < numeroNodos();i++)
	{
		cout << " La distancia minima de " << provincias[origen] << " a "<< provincias[i] << " es " << distancias[i] << endl;
		cout << " El camino minimo a " << provincias[i] <<" es: ";
		CamMin.caminoDijkstraProv(predecesores, origen, i, provincias);
	}
	
	//Eliminamos de memoria los vectores
	delete distancias;
	delete predecesores;
	for(int i = 0; i < 20; i++) delete(provincias[i]);
	delete(provincias);
}

void Grafo::provFloyd()
{
	TipoPeso **distanciasFloyd;
 	int **intermedios;
	AlgoritmosGrafos CamMin;
	int origen, destino;
	char **provincias;

	//Reservamos memoria y Cargamos la matriz de provincias
	provincias = new char*[numeroNodos()];
 	for (int i = 0; i < numeroNodos(); i++) 
        	provincias[i] = new char[20];
	
	mostrarProvincias(provincias);

	//Pedimos las dos provincias de las que queremos la distancia minima y el camino	
	cout << "\n\nProvincia origen: ";
	cin >> origen;
	cout << "\nProvincia destino: ";
	cin >> destino;

	//Reservamos memoria para las matrices distanciasFloyd e intermedios
	distanciasFloyd = new TipoPeso* [numeroNodos()];
 	for (int i = 0; i < numeroNodos(); i++) 
        	distanciasFloyd[i] = new TipoPeso[numeroNodos()];
 
	intermedios = new int* [numeroNodos()];
 	for (int i = 0; i < numeroNodos(); i++) 
        	intermedios[i] = new int[numeroNodos()];

	//Ejecutamos la funci�n floyd
  	CamMin.floyd(this, distanciasFloyd, intermedios);

	//Mostramos los caminos
 	cout << " \nLa distancia minima entre " << provincias[origen] << " y " << provincias[destino] << " es " 
		<< distanciasFloyd[origen][destino] << endl;
    	cout << "El camino minimo entre " << provincias[origen] << " y " << provincias[destino] << " es: ";
	cout << provincias[origen] << " ";
    	CamMin.caminoFloydProv(intermedios,origen,destino,provincias);
	cout << " <- " << provincias[destino];

	//Borramos las matrices de memoria
  	for(int i = 0; i < numeroNodos(); i++)
  	{
   		delete distanciasFloyd[i];
   		delete intermedios[i];
  	}

  	delete distanciasFloyd;
  	delete intermedios;
	for(int i = 0; i < 20; i++) delete(provincias[i]);
	delete(provincias);
}

void Grafo::mostrarProvincias(char **provincias){
	int lineas=0;
	ifstream f("provincias.txt");
	int numProvincias;
	f >> numProvincias;

	for(int i = 0; i < numProvincias; i++)
    	{
      		f >> provincias[i];
    	}
	
  	f.close();

	for(int i=0;i<numProvincias;i++)
	{
		cout << i << " " << provincias[i] << "   ";
		lineas ++;
		if(lineas==3)
		{
			cout << endl;
			lineas=0;	
		}
	}
}
