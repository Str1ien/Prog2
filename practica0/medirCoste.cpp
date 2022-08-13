/******************************************************************************\
 * Programación 1. Práctica 0
 * Autor: Alain Villagrasa Labrador
 * Última revisión: 21 de febrero de 2022
 * Resumen: Fichero del programa "medirCoste" que, a partir de los datos 
 			introducidos por el usuario escribe en pantalla las primeras 20 y las 
 			últimas 20 líneas de la tabla generada con números aleatorios en el 
 			intervalo especificado, y las vuelve a escribir una vez ha ordenado
 			la tabla de menor a mayor.
 \******************************************************************************/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include "ordenar.hpp"

using namespace std;

const unsigned COL = 10;
const unsigned DATOS_MOSTRADOS = 20;
const unsigned ANCHO = 8;


/*
 * Pre:  a >= b
 * Post: Ha devuelto un número entero aleatorio en el intervalo [a, b].
 */
int randInt(const int a, const int b) {
    return a + rand() % (b - a + 1);
}

/*
 * Pre:  limInf >= limSup, n >= 0.
 * Post: Ha llenado el vector "v" con número enteros aleatorios en el intervalo
 *   	 [limInf, limSup].
 */
void llenarVector(int v[], const unsigned n, const int limInf, const int limSup) {
    for(unsigned i = 0; i < n; i++) {
        v[i] = randInt(limInf, limSup);
    }
}

/*
 * Pre:  n >= 1.
 * Post: Ha escrito en la terminal los primeros 20 y los últimos 20 elementos de la tabla. 
 */
void escribirDatos(const string mensaje, const int v[], const unsigned n) {
    cout << mensaje << endl;
    for(unsigned i = 0; i < DATOS_MOSTRADOS; i++) {
        cout << setw(ANCHO) << v[i];
        if((i + 1) % 10 == 0) {
            cout << endl;
        }
    }

    cout << endl;
    for(unsigned i = n - DATOS_MOSTRADOS; i < n; i++) {
        cout << setw(ANCHO) << v[i];
        if((i + 1) % 10 == 0) {
            cout << endl;
        }
    }
}

int main(int numArg, char* args[]) {

    int nDatos = stoi(args[1]);
    int limInf = stoi(args[2]);
    int limSup = stoi(args[3]);
    int vector[nDatos];
    time_t semilla = time(nullptr);
    srand(semilla);

    llenarVector(vector, nDatos, limInf, limSup);
    escribirDatos("Datos a ordenar:", vector, nDatos);
    cout << endl << "Ordenando " << nDatos << " datos enteros ..." << endl;
    
	//Calculo del tiempo de CPU que se tarda en ordenar
    clock_t t1 = clock();
    ordenar(vector, nDatos);
    clock_t t2 = clock();

    escribirDatos("Datos ordenados:", vector, nDatos);
    cout << endl << "Tiempo de CPU para ordenar " << nDatos << " enteros: "
         << float(t2 - t1) / CLOCKS_PER_SEC << " segundos" << endl;



    return 0;
}
