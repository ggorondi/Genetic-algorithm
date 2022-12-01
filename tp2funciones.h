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
#include "tp2classes.h"
using namespace std;

//es nada mas para devolver un array con ints igual a su posicion en sus elementos, para ir eligiendo i's y que no se repitan
vector<int> rangeVectorOfSize(int size);

//compara la distancia de los recorridos
bool compararRecorridos(Recorrido* r1,Recorrido* r2);

//calcula el cambio porcentual en valor absoluto entre dos valores double
double cambioPorcentual(double val1, double val2);

//lee archivo csv y almacena los datos en vector de punteros a ciudades
void leerCsv(string csvName, vector<Ciudad*>& todasLasCiudades);

//escribir el archivo de salida
void escribirArchivoSalida(fstream& fout, int tipoArchSalida, int gen, Poblacion& pob);

//imprime para cada generacion la distancia de cada recorrido
void imprimirPoblacion(Poblacion& pob);