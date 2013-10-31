#include "algoritmosgrafos.h"
#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include <iostream>
using namespace std;

void AlgoritmosGrafos::dijkstra(Grafo *g, Grafo::TipoPeso *distancia, int *predecesor, int nodoOrigen)
{
	int i,j;
	int *s;
	Grafo::TipoPeso minimo;
	int x = 0;

	s = new int[g->numeroNodos()];

	for(i = 0; i < g->numeroNodos(); i++)
	{
		predecesor[i] = nodoOrigen;
		distancia[i] = g->verPeso(nodoOrigen,i);
		s[i] = 0;
	}

	s[nodoOrigen] = 1;

	 //Se calcula la distancia mínima a los n-1 nodos restantes
	for(i = 0; i < (g->numeroNodos()-1); i++)
	{
	 	/* Buscar Nodo de distancia minima */
		minimo = 31999;
	  	for(j = 0; j < g->numeroNodos(); j++)
	  	{
			if (distancia[j] <= minimo && s[j] == 0)
			{
				minimo = distancia[j];
				x = j;
			}
		}
	   	s[x] = 1; 		/* El nodo x pasa al conjunto s */
	  		  		/* Comprobamos si el nodo x acorta las dist */
	  	for(j = 0; j <= g->numeroNodos(); j++)
	  	{
	  		if (s[j] == 0 && distancia[j] > distancia[x] + g->verPeso(x,j))
	   		{
				distancia[j] = distancia[x] + g->verPeso(x,j);
				predecesor[j] = x;
			}
	  	}
	 }
	 delete(s);
}

//Función para mostrar los caminos obtenidos con el algoritmo de Dijkstra
void AlgoritmosGrafos::caminoDijkstra(int *predecesor, int nodoOrigen, int nodoDestino)
{
	int k;
	cout << nodoDestino << " <- " ;
	k = predecesor[nodoDestino];
	while(k != nodoOrigen)
	{
		cout << k << " <- ";
		k = predecesor[k];

	}
	cout << nodoOrigen << endl;
}

void AlgoritmosGrafos::caminoDijkstraProv(int *predecesor, int nodoOrigen, int nodoDestino, char **provincias)
{
	int k;
	cout << provincias[nodoDestino] << " <- " ;
	k = predecesor[nodoDestino];
	while(k != nodoOrigen)
	{
		cout << provincias[k] << " <- ";
		k = predecesor[k];

	}
	cout << provincias[nodoOrigen] << endl;
}

void AlgoritmosGrafos::floyd(Grafo *g, Grafo::TipoPeso **dist, int **intermed)
{
	int i, j, k;

	for(i = 0; i < g->numeroNodos(); i++)
	for(j = 0; j < g->numeroNodos(); j++)
	{
		dist[i][j] = g->verPeso(i,j);
		intermed[i][j] = -1;
	}
	for(k = 0; k < g->numeroNodos(); k++)
	{
		for(i = 0; i < g->numeroNodos(); i++)
		{
			for(j = 0; j < g->numeroNodos(); j++)
			{
				if (dist[i][j] > dist[i][k] + dist[k][j] && i != j)
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					intermed[i][j] = k;
				}
			}
		}
	}
}

void AlgoritmosGrafos::caminoFloyd(int **intermed, int nodoOrigen, int nodoDestino)
{
	int k;

	k = intermed[nodoOrigen][nodoDestino];

	if (k != -1)
	{
		caminoFloyd(intermed, nodoOrigen, k);
		cout << " " << k << " <- ";
		caminoFloyd(intermed, k, nodoDestino);
	}
}

void AlgoritmosGrafos::caminoFloydProv(int **intermed, int nodoOrigen, int nodoDestino, char **provincias)
{
	int k;

	k = intermed[nodoOrigen][nodoDestino];

	if (k != -1)
	{
		caminoFloydProv(intermed, nodoOrigen, k, provincias);
		cout << " <- " << provincias[k];
		caminoFloydProv(intermed, k, nodoDestino, provincias);
	}
}

void AlgoritmosGrafos::Warshall(Grafo *g, int **conexion)
{
	for(int k = 0; k < g->numeroNodos(); k++)
	{
		for(int i = 0; i < g->numeroNodos(); i++)
		{
			for(int j = 0; j < g->numeroNodos(); j++)
			{
				if (conexion[i][j] == 0 && i != j)
				{
					conexion[i][j] = conexion[i][k] * conexion[k][j];
				}
			}
		}
	}	
}

void AlgoritmosGrafos::profundidad(Grafo *g)
{
 	int *visitado;
	int *numeroProf;
	int *numeroDesc;
	int **lados;
	int Componentes=0;
	int contador=0;
	

	visitado = new int[g->numeroNodos()];
	numeroProf = new int[g->numeroNodos()];
	numeroDesc = new int[g->numeroNodos()];

	for(int i = 0; i < g->numeroNodos(); i++)
	{
		visitado[i] = 0;
		numeroProf[i] = 0;
		numeroDesc[i] = 0;
	}
	
	lados = new int* [g->numeroNodos()];
 	for (int i = 0; i < g->numeroNodos(); i++) 
        	lados[i] = new int[g->numeroNodos()];

 	for (int i = 0; i < g->numeroNodos(); i++) 
	{
  		for(int j = 0; j < g->numeroNodos(); j++)
		{
			lados[i][j] = 0;
		}
	}	

	for(int i = 0; i < g->numeroNodos(); i++)
	{
		if (visitado[i] == 0)
		{
			//cout << "\nEn el if.";
			Componentes++;
			cout << "\nComponente conexa " << i << endl;	
			recorridoProfundidad(g, i, visitado, numeroProf, numeroDesc, contador, lados);		
			
		}
	}
	cout << "\nHay un total de "<< Componentes << " componentes conexas en el grafo.";
	clasifComp(g, numeroProf, numeroDesc, lados); 
	delete(visitado);
	delete(numeroProf);
	delete(numeroDesc);
 	for(int i = 0; i < g->numeroNodos(); i++) delete(lados[i]);
	delete(lados);	
}

void AlgoritmosGrafos::recorridoProfundidad(Grafo *g, int i, int *visitado, int *numeroProf, int *numeroDesc, int &contador, int **lados)
{
	//cout << "\nEntramos a recorridoProfundidad";
	visitado[i] = 1;
	numeroProf[i]=contador;
	contador++;
 	cout << " " << i;
 	for(int j = 0; j < g->numeroNodos(); j++)
 	{
 		if (g->verPeso(i,j) != 32000 && visitado[j] == 0)
		{
			numeroDesc[i]=numeroDesc[i]++;
			lados[i][j]=1;
	   		recorridoProfundidad(g, j, visitado, numeroProf, numeroDesc, contador, lados);
		  	numeroDesc[i]=numeroDesc[i]+numeroDesc[j];
		}
 	}
}

void AlgoritmosGrafos::clasifComp(Grafo *g, int *numeroProf, int *numeroDesc, int **lados)
{
	for (int i = 0; i < g->numeroNodos(); i++) 
	{
		cout << "\nEl nodo " << i << " se visitó en la posición " << numeroProf[i];
		cout << " y tiene " << numeroDesc[i] << " descendientes ";
	}	
 	for (int i = 0; i < g->numeroNodos(); i++) 
	{
  		for(int j = 0; j < g->numeroNodos(); j++)
		{
			if(lados[i][j]==1) cout << "\nLado " << i <<", " << j << " es lado de árbol";
			else
			{
				if(g->verPeso(i,j)!=32000)
				{
					if(!g->dirigido()) cout << "\nLado " << i <<", " << j << " es lado de avance/retroceso";
					else
					{
						if(numeroProf[i] <= numeroProf[j] && numeroProf[j] <= numeroProf[i] + numeroDesc[i])
						{
							cout << "\n" << numeroProf[i] <<", " << numeroDesc[i] << ", ";
							cout << numeroProf[j] <<", " << numeroDesc[j] << " "; 	
							cout << "\nLado " << i <<", " << j << " es lado de avance";
						}
						if(numeroProf[j] <= numeroProf[i] && numeroProf[i] <= numeroProf[j] + numeroDesc[j])
						{	
							cout << "\n" << numeroProf[i] <<", " << numeroDesc[i] << ", ";
							cout << numeroProf[j] <<", " << numeroDesc[j] << " "; 	
							cout << "\nLado " << i <<", " << j << " es lado de retroceso";
						}
						if(numeroProf[i] >= (numeroProf[j] + numeroDesc[j]))
						{
							cout << "\n" << numeroProf[i] <<", " << numeroDesc[i] << ", ";
							cout << numeroProf[j] <<", " << numeroDesc[j] << " "; 		
							cout << "\nLado " << i <<", " << j << " es lado cruzado";
						}
					}	
				}
			}			
		}
	}	
}

void AlgoritmosGrafos::topologica(Grafo *g)
{
 	int *visitado;
    
 	visitado = new int[g->numeroNodos()];
	for(int i = 0; i < g->numeroNodos(); i++)
	{
		visitado[i] = 0;
	}

 	for(int i = 0; i < g->numeroNodos(); i++)
 	{
  		if (visitado[i] == 0)
  		{
   			clasificacionTopologica(g, i, visitado);
  		}
 	}
 	delete(visitado);
}

void AlgoritmosGrafos::clasificacionTopologica(Grafo *g, int i, int *visitado)
{
 	visitado[i] = 1;
	
 	for(int j = 0; j < g->numeroNodos(); j++)
 	{
  		if (g->verPeso(i, j) < 32000 && visitado[j] == 0)
		{
   			clasificacionTopologica(g, j, visitado);
		}
 	}
 	cout << i <<" ";
}

void AlgoritmosGrafos::algoritmoPrim(Grafo *g)
{ 
 	Grafo::TipoPeso **arbolACM; /*matriz de conexion para el arbol */

	arbolACM = new Grafo::TipoPeso* [g->numeroNodos()];
 	for (int i = 0; i < g->numeroNodos(); i++) 
        	arbolACM[i] = new Grafo::TipoPeso[g->numeroNodos()];

 	Prim(g, arbolACM);
 	cout << "ARBOL ABARCADOR DE COSTE MINIMO\n";
 	for (int i = 0; i < g->numeroNodos(); i++) 
 	{
		for(int k=0;k<i;k++) cout << "   ";
  		for(int j = i; j < g->numeroNodos(); j++)
		{
			cout << " ";
			if(arbolACM[i][j]==32000) cout << "* ";
			else cout << arbolACM[i][j];
		}
  		cout << endl;
 	}

 	for(int i = 0; i < g->numeroNodos(); i++) delete(arbolACM[i]);
	delete(arbolACM);
}

void AlgoritmosGrafos::Prim(Grafo *g, Grafo::TipoPeso **arbol)
{
	int *cercano;
	int k;
	Grafo::TipoPeso *coste;

 	cercano = new int[g->numeroNodos()];
 	coste = new Grafo::TipoPeso[g->numeroNodos()];

 	for (int i = 0; i < g->numeroNodos(); i++) 
	{
  		for(int j = 0; j < g->numeroNodos(); j++)
		{
  			 arbol[i][j] = 32000;
		}
	}	

 	for (int i = 1; i < g->numeroNodos(); i++) 
 	{
  		cercano[i] = 0;
  		coste[i] = g->verPeso(0, i);
 	}

	//Seleccion de los n-1 lados del arbol
 	for (int i = 1; i < g->numeroNodos(); i++) 
 	{
 	//Seleccion del nodo de menor coste 
  		k = 1;
  		for(int j = 2; j < g->numeroNodos(); j++)
  		{
   			if (coste[j] < 32000 && coste[j] < coste[k])
    			{
    				 k = j;
    			}
  		}
  		/* El nodo de menor coste pasa a formar parte del arbol */
  		coste[k] = 33000; //Este infinito tiene que ser de orden superior al peso de un lado que no exista.
  		arbol[k][cercano[k]] = g->verPeso(k,cercano[k]);
  		arbol[cercano[k]][k] = g->verPeso(k,cercano[k]);

  		/* Se corrige el vector cercano, considerando al nodo k */
  		for(int j = 1; j < g->numeroNodos(); j++)
   		{
    			if (coste[j] < 33000 && coste[j] > g->verPeso(j, k))
    			{
     				cercano[j] = k;
     				coste[j] = g->verPeso(j, k);
    			}
   		}
 	}
}
