#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <math.h> //para fabs(), absolute value de doubles
#include <time.h>
#include "tp2funciones.h"
#include "tp2classes.h"
using namespace std;

#define RANDOM_SAMPLE 10
#define PORCENTAJE_FITTEST 0.2

//CLASE CIUDAD

Ciudad::Ciudad(string nombre, double x, double y): nombre(nombre), xCo(x), yCo(y) {}

double Ciudad::getx() {
    return xCo;
};
double Ciudad::gety() {
    return yCo;
};

double Ciudad::distanciaEntreDosCiudades(Ciudad* c2) {
    return (sqrt(pow((xCo - c2->getx()),2) + pow((yCo - c2->gety()),2)));
}

//CLASE RECORRIDO

Recorrido::Recorrido (vector<Ciudad*>& todasLasCiudades) {//crea recorrido random en base al vector de las ciudades (asigna random punteros a ciudades del vector ciudades)
    distRecorrido = 0;
    int n=0;
    int size = todasLasCiudades.size();
    ciudadesEnRec.reserve(size+1);
    vector<int> numberedArray = rangeVectorOfSize(size); //llama la funcion esa que da un vector {0,1,2,3,...,size} para ir eligiendo numeros random y ir sacandolos del vector para ir eligiendo punteros random del vector todasLasCiudades sin repetir.
    ciudadesEnRec.push_back(todasLasCiudades[numberedArray[0]]);
    numberedArray.erase(numberedArray.begin()+n);
    for(int i=0;i<(size-1);i++) {
        n=rand()%(size-1-i);
        ciudadesEnRec.push_back(todasLasCiudades[numberedArray[n]]);
        numberedArray.erase(numberedArray.begin()+n); //borra ese elemento del array asi no se repiten la ciudades
    }
    ciudadesEnRec.push_back(todasLasCiudades[numberedArray[0]]);
    numberedArray.clear();
    // llama a funcion que calcula distancia del recorrido y la guarda en el atributo
    updateDistRecorrido();
}

double Recorrido::updateDistRecorrido() {
// calcula la distancia entre cada par de ciudades en rec y las suma a distRecorrido
    distRecorrido = 0;
    for(int i=1;i<ciudadesEnRec.size();i++) {
        distRecorrido+=ciudadesEnRec[i]->distanciaEntreDosCiudades(ciudadesEnRec[i-1]); //distancia entre cada ciudad del recorrido y la anterior, las suma al distRecorrido
    }
    return distRecorrido;
}  

double Recorrido::getDist() {
    return distRecorrido;
}

int Recorrido::getCantCiudades() {
    return ciudadesEnRec.size();
}

int Recorrido::ciudadEnParteDeRec(int index, int largoBloque, Ciudad* ciudad) {
    return find(ciudadesEnRec.begin()+index,ciudadesEnRec.begin()+index+largoBloque,ciudad) != ciudadesEnRec.begin()+index+largoBloque;
}

Ciudad* Recorrido::getCiudad (int index) {
    return ciudadesEnRec[index];
}

void Recorrido::setCiudad (Ciudad* ciudad, int index) {
    ciudadesEnRec[index] = ciudad;
}

void Recorrido::mutarSwap () {
    int ran = rand() % (ciudadesEnRec.size()-2);
    ran++;
    Ciudad* temp = ciudadesEnRec[ran];
    int ran2;
    while ((ran2 = rand() % (ciudadesEnRec.size()-2)) == ran-1);
    ran2++;
    ciudadesEnRec[ran] = ciudadesEnRec[ran2];
    ciudadesEnRec[ran2] = temp;
}

//CLASE POBLACION

Poblacion::Poblacion(int cantRecorridos, vector<Ciudad*>& todasLasCiudades) {// crear poblacion con recorridos aleatorios, la cantidad que quieras en cada generacion
    recorridos.reserve(cantRecorridos); //asi los pushback no hacen q se vaya teniendo que mudar el vector a medida que crece
    for (int i = 0; i < cantRecorridos; i++) {    
        recorridos.push_back(new Recorrido(todasLasCiudades));
    }
    cant_Top20_upper = cuantosSonTop20_upper();
    updateDistTop20();
}
Poblacion::~Poblacion() {
    for(int i=0;i<recorridos.size();i++) { //delete los recorridos de memoria dinamica que hice new en el constructor random.
        delete recorridos[i];
    }
}

double Poblacion::getDistTop20() {
    return distTop20;
}

void Poblacion::updateDistTop20() {
    distTop20=0;
    for(int i=0;i<(recorridos.size()*PORCENTAJE_FITTEST);i++) {
        distTop20+=recorridos[i]->getDist();
    }
}

int Poblacion::cuantosSonTop20_upper() {
    return ((recorridos.size()*PORCENTAJE_FITTEST)+recorridos.size()%(int)(1/PORCENTAJE_FITTEST)); //11 recorridos tiene un 20% que es 2 (rounded down) y 3 (rounded up), esto devuelve 3.;
}

void Poblacion::ordenarPoblacionMenorAMayor() {
    sort(recorridos.begin(), recorridos.end(), compararRecorridos);
}

void Poblacion::cruzarRecorridos (Recorrido* rec1, Recorrido* rec2, Recorrido* recAns) {
    int cantBloque = (rec1->getCantCiudades()-2)*3/4;
    int index = rand() % (rec1->getCantCiudades()-cantBloque-1);
    index++;
    int j = 1;
    for (int i = 1; i < recAns->getCantCiudades()-1; i++) {
        if (i >= index && i < cantBloque+index)
            recAns->setCiudad(rec1->getCiudad(i),i);
        else {
            while (rec1->ciudadEnParteDeRec(index,cantBloque,rec2->getCiudad(j))) j++;
            recAns->setCiudad(rec2->getCiudad(j++),i);
        }
    }
}

void Poblacion::reproduccion () {
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
    int index = cant_Top20_upper;
    for (int i = 0; i < recorridos.size() * PORCENTAJE_FITTEST; i++) {
        for (int j = 0; j < (1/PORCENTAJE_FITTEST)-1; j++) {
            int ran;
            while((ran = rand() % cant_Top20_upper) == i); 
            cruzarRecorridos(recorridos[i],recorridos[ran],recorridos[index]);
            if (!(rand() % RANDOM_SAMPLE)) {
                recorridos[index]->mutarSwap();
            }
            recorridos[index]->updateDistRecorrido();
            index++;
        }
    }
}

double Poblacion::getPromedioDist() {
    double sum = 0;
    for (int i = 0; i < recorridos.size(); i++)
        sum += recorridos[i]->getDist();
    return sum / recorridos.size();
}

double Poblacion::getMejorRec () {
    return recorridos[0]->getDist();
}

double Poblacion::getPeorRec () {
    return recorridos[recorridos.size()-1]->getDist();
}

//PARA FLAGS
Recorrido* Poblacion::getRecorrido (int i) {
    return recorridos[i];
}
