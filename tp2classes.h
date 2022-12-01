#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <math.h> //para fabs(), absolute value de doubles
#include <time.h>
using namespace std;

class Ciudad {
    string nombre;
    double xCo, yCo;

    public:
        Ciudad(string nombre, double x, double y);

        double getx();

        double gety();
        
        double distanciaEntreDosCiudades(Ciudad* c2);
};


class Recorrido {
    vector<Ciudad*> ciudadesEnRec;
    double distRecorrido;

    public:
        Recorrido (vector<Ciudad*>& todasLasCiudades);
        
        double updateDistRecorrido();

        double getDist();

        int getCantCiudades();
        
        int ciudadEnParteDeRec(int index, int largoBloque, Ciudad* ciudad);

        Ciudad* getCiudad (int index);
    
        void setCiudad (Ciudad* ciudad, int index);

        void mutarSwap ();

};


class Poblacion{
    vector<Recorrido*> recorridos;
    double distTop20;
    int cant_Top20_upper;
    int remainderTop20;
    public:
        Poblacion(int cantRecorridos, vector<Ciudad*>& todasLasCiudades);

        ~Poblacion();

        double getDistTop20();

        void updateDistTop20();

        int cuantosSonTop20_upper();
        
        void ordenarPoblacionMenorAMayor();

        void cruzarRecorridos (Recorrido* rec1, Recorrido* rec2, Recorrido* recAns);
        
        //Reproduccion:
            //›reproducimos a los 20% mas fit del vector de recorridos ordenados:
            //>cada uno de estos recorridos se reproduce con 4 random recorridos de este segmento
            //y tambien pasa el padre
            //>cada hijo esta compuesto por un porcentaje definido de genes del padre mas fit de la pareja        //el lugar del bloque de genes que pasa se elige random
            //el resto de los genes se llena como indica el tp
            //siempre se dejan fijas la primera y ultima ciudad

            //for loop que recorre la cant top20_lower (cantRecorridos / 5) recorridos
                //> reproduce cada recorrido con 4 randoms de los top20_upper
                //> cada reproduccion la hace con dejando un porcentaje del mas fit fijo y llenando el resto
                // del espacio con el resto de las ciudades que faltan en el orden en que estan en el recorrido de abajo
                //> para cada reproduccion reescribe sobre el vector de recorridos a partir del recorrido top20_upper
                //> calcula la distancia del recorrido y actualiza el atributo dist de cada recorrido

            //actualiza la distTop20 de la poblacion
        void reproduccion ();

        double getPromedioDist();

        double getMejorRec ();

        double getPeorRec ();

        //PARA FLAGS
        Recorrido* getRecorrido (int i);

};