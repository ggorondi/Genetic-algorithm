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

#define RECORRIDOS_POR_GENERACION 100

//es nada mas para devolver un array con ints igual a su posicion en sus elementos, para ir eligiendo i's y que no se repitan
vector<int> rangeVectorOfSize(int size) {
    vector<int> range;
    range.reserve(size);
    for (int value = 0; value < size; value ++)
        range.push_back(value);
    return range;
};

//compara la distancia de los recorridos
bool compararRecorridos(Recorrido* r1,Recorrido* r2) {//para funcion sort() de vectors para ordenatPoblacion. Nose si vale &, sino sacar
            return (r1->getDist()<r2->getDist());
};

double cambioPorcentual(double val1, double val2) {
    return fabs((val2 - val1) / val1);
};

//lee archivo csv y almacena los datos en vector de punteros a ciudades
void leerCsv(string csvName, vector<Ciudad*>& todasLasCiudades) {
    fstream csvFile;
    csvFile.open(csvName,ios::in);
    vector<string> row;
    string temp, line, word;
    while (!csvFile.eof()) {
            row.clear();  
            getline(csvFile, line);
            if (line[0] != '#' && line.length() != 0) {
                stringstream s(line);
                while (getline(s, word, ',')) {
                    row.push_back(word);
                }
                todasLasCiudades.push_back(new Ciudad(row[0],stod(row[1]),stod(row[2])));
            }
    }
    csvFile.close();
};

//escribir el archivo de salida
void escribirArchivoSalida(fstream& fout, int tipoArchSalida, int gen, Poblacion& pob) {
    fout << gen << " ";
    switch(tipoArchSalida) {
        case 1 :
            fout << pob.getMejorRec();
            break;
        case 2 :
            fout << pob.getPromedioDist();
            break;
        case 3 :
            fout << pob.getPeorRec();
            break;
    }
    fout << endl;
};

//imprime para cada generacion la distancia de cada recorrido
void imprimirPoblacion(Poblacion& pob) {
    for (int i = 0; i < RECORRIDOS_POR_GENERACION; i++) {
        cout << "rec " << i << "= " << pob.getRecorrido(i)->getDist() << endl;
    }
}