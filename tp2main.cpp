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
#define CANT_CORRECT_ARGS 9
#define RECORRIDOS_POR_GENERACION 100

enum errors {ERR_HELP, ERR_CANT_ARGS};

int main (int argc, char * argv[]) {

string tipoSalida;  // flag que  indica  el tipo de archivo de salida
string csv_name;    //guardar el argv del csv filename.
int seed=0;         // seed para los rands
srand(time(NULL));

//PRIMERA PARTE: Checkeamos argumentos
//csv + umbral + cantGeneraciones + tipodesalida
//>Recibimos archivo csv 
    //se meten las ciudades en vector ciudades 
//>Leemos el tipo de archivo de retorno
    //crear archivo de retorno
//>Crea archivo de salida

int flagH = 0, flagU = 0, flagCantGen = 0, flagSalida = 0, flagCsv = 0;  // CHECK: capaz conviene q sean chars envez de ints
int i = 1;
if (!strcmp(argv[i],"-h")) {
        cout << "-u umbral, -cantGen cantidad generaciones, -csv archivoCsv, -tipoSalida tipoDeArchivoSalida" << endl;
        exit(ERR_HELP); // CHECK
    }
else if (argc != CANT_CORRECT_ARGS) {
    cout << "cantidad incorrecta de argumentos, -h para ayuda" << endl;
    exit(ERR_CANT_ARGS); // CHECK
}
double umbral;
int cantGeneraciones, tipoArchSalida;
string csvName;
while ((!flagU || !flagCantGen || !flagSalida || !flagCsv) && i < CANT_CORRECT_ARGS) {
    if (!flagU && !strcmp(argv[i],"-u")) {
        umbral = stod(argv[++i]);
        flagU = 1;
    }
    else if (!flagCantGen && !strcmp(argv[i],"-cantGen")) {
        cantGeneraciones = stoi(argv[++i]);
        flagCantGen = 1;
    }
    else if (!flagSalida && !strcmp(argv[i],"-tipoSalida")) {
        tipoArchSalida = stoi(argv[++i]);
        flagSalida = 1;
    }
    else if (!flagSalida && !strcmp(argv[i],"-csv")) {
        csvName.assign(argv[++i]);
        flagCsv = 1;
    }
    i++;
}
//leo archivo csv
vector<Ciudad*> todasLasCiudades;
leerCsv(csvName, todasLasCiudades);
//crear archivo salida
fstream fout;
fout.open("algoritmoGeneticoSalida.txt", ios::out);
    
    //SEGUNDA PARTE: Algoritmo
    //Creamos una primera poblacion aleatoria:
        //>llama al constructor de Poblacion que a su vez crea un vector Recorridos de objetos de la clase Recorrido
        //cada objeto Recorrido crea un vector de punteros a ciudad y asigna random el orden de ciudades en cada vector
    //Calcula el fitness de cada recorrido
        //>funciones adentro de la clase recorrido que calculan cada vez que se crea un recorrido
        //›ordena los recorridos en un vector de punteros a recorridos de tamaño de la cantidad de recorridos
        
        //for loop en main de la cantidad de generaciones-1
        
            //reproduccion
            //escribir archivo de salida (en ppblacion, una funcion que toma 2 argumentos, el puntero al archivo, y un int con el que hace switch y decide que formato printearle)
            //un if umbral>umbral y breakea si es mayor (compara ((disttop20-distTop20previo)/distTop20previo) > umbral )

            //guardar distTop20 para el if del prox loop del for

    Poblacion pob(RECORRIDOS_POR_GENERACION,todasLasCiudades); 
    pob.ordenarPoblacionMenorAMayor();
    double distTop20anterior = pob.getDistTop20();
    escribirArchivoSalida(fout,tipoArchSalida,0,pob);
    for (int i = 1; i <= cantGeneraciones; i++) {
        pob.reproduccion();
        pob.ordenarPoblacionMenorAMayor();
        pob.updateDistTop20();
        //escribir en el archivo de salida
        escribirArchivoSalida(fout,tipoArchSalida,i,pob);
        if (cambioPorcentual(distTop20anterior,pob.getDistTop20()) < umbral) break;
        distTop20anterior = pob.getDistTop20();
    }

    //liberar delete todo lo que haga falta

}