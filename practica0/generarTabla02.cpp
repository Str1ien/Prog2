/******************************************************************************\
 * Programación 2. Práctica 0
 * Autor: Alain Villagrasa Labrador
 * Última revisión: 21 de febrero de 2022
 * Resumen: Fichero del programa "generarTabla02" que, a partir de 2 números
 			suministrados por el usuario al ejecutar el programa en terminal, 
 			escribe una tabla de el número de datos que el usuario especifique
 			en ese intervalo.
\******************************************************************************/


#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

const unsigned COL = 10;
const unsigned ANCHO = 8;

/*
 * Pre:  a & b son dato de tipo double.
 * Post: Ha devuelto un número real aleatorio en el intervalo [a, b].
 */
double randDouble(const double a, const double b) {
    return a + (double(rand()) / RAND_MAX) * (b - a);
}

/*
 * Pre:  limInf <= limSup, nDatos >=1.
 * Post: Ha escrito en la terminal la tabla con los números reales aleatorios en 
 		 el intervalo [limInf, limSup] (con filas de 10 columnas). 
 */
void escribirTabla(const int limInf, const int limSup, const unsigned nDatos) {
    for(unsigned i = 0; i < nDatos; i++) {
        cout << setw(ANCHO) << fixed << setprecision(ANCHO - 5) << randDouble(limInf, limSup);

        if((i + 1) % 10 == 0) {
            cout << endl;
        }
    }
}

int main(int numArg, char* args[]) {
    unsigned nDatos = stod(args[1]);
    double limInf = stod(args[2]);
    double limSup = stod(args[3]);
    time_t semilla = time(nullptr);

    srand(semilla);
    escribirTabla(limInf, limSup, nDatos);

    return 0;
}
