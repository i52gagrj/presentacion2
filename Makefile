destinos: pgra4
pgra4: ppal.o practica.o grafo.o algoritmosgrafos.o
	g++ -o pgra4 ppal.o practica.o grafo.o algoritmosgrafos.o

ppal.o : ppal.cpp practica.h
	g++ -c -o ppal.o -I. ppal.cpp

practica.o : practica.cpp practica.h
	g++ -c -o practica.o -I. practica.cpp

grafo.o : grafo.cpp grafo.h
	g++ -c -o grafo.o -I. grafo.cpp

algoritmosgrafos.o : algoritmosgrafos.cpp algoritmosgrafos.h
	g++ -c -o algoritmosgrafos.o -I. algoritmosgrafos.cpp

clean:
	rm practica.o 
	rm ppal.o
	rm algoritmosgrafos.o
	rm grafo.o
