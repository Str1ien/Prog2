/******************************************************************************\
 * Programación 2. Práctica 0
 * Autor: Alain Villagrasa Labrador
 * Última revisión: 21 de febrero de 2022
 * Resumen: Fichero del programa "generarTabla01" que a a partir de los datos
 			introducidos por el usuario en la terminal al ejecutar el programa, 
 			muestra en la pantalla una tabla con números enteros aleatorios en 
 			ese intervalo.
\******************************************************************************/

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

const unsigned COL = 10;
const unsigned ANCHO = 4;


/*
 * Pre:  a y b son datos de tipo entero.
 * Post: Ha devuelto un número entero aleatorio en el intervalo [a, b]
 */
int randInt(const int a, const int b) {
    return a + rand() % (b - a + 1);
}

/*
 * Pre:  limInf y limSup son datos de tipo entero, nDatos >= 1.
 * Post: Ha escrito en la terminal la tabla con los números aleatorios generados
 		 en el intervalo [limInf, limSup].
 */
void escribirTabla(const int limInf, const int limSup, const unsigned nDatos) {
    for(unsigned i = 0; i < nDatos; i++) {
        cout << setw(ANCHO) << randInt(limInf, limSup);

        if((i + 1) % 10 == 0) {
            cout << endl;
        }
    }
}



int main(int numArg, char* args[]) {
    unsigned nDatos = stoi(args[1]);
    int limInf = stoi(args[2]);
    int limSup = stoi(args[3]);
    time_t semilla = time(nullptr);

    srand(semilla);
    escribirTabla(limInf, limSup, nDatos);

    return 0;
}
