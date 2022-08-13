/******************************************************************************\
 * Programación 2. Práctica 0
 * Autor: Alain Villagrasa Labrador
 * Última revisión: 21 de febrero de 2022
 * Resumen: Fichero del programa "tiempoReaccion" que calcula el tiempo que
 			transcurre entre 2 pulsaciones del usuario en la terminal, 
 			tomando de terminal el número de veces que desea realizar el test.
\******************************************************************************/

#include <iostream>
#include <ctime>
#include <string>

using namespace std;


/*
 * Pre:  i >= 0
 * Post: Ha pedido al usuario que pulse la tecla de fin de línea.
 */
void pedirPulsacion(const int i) {
    cout << i << ") " << "Pulse la tecla de fin de línea, por favor..."
         << endl;
}

/*
 * Pre:  t >= 0
 * Post: Ha escrito en la terminal el tiempo de reacción del usuario.
 */
void tiempoReacc(const time_t t1, const time_t t2) {
    cout << "Su tiempo de reacción ha sido de " << (t2 - t1) << " segundos"
         << endl << endl;
}

/*
 * Pre:  n >= 1
 * Post: Ha calculado el tiempo de reacción del usuario, pidiendo que pulse la
 		 tecla de fin de línea, y ha escrito el resultado en la terminal.
 */
void calcTiempoReacc(const int n, string linea) {
    pedirPulsacion(n);
    time_t tiempo1 = time(nullptr);
    
    getline(cin, linea);
    time_t tiempo2 = time(nullptr);
    
    tiempoReacc(tiempo1, tiempo2);
}

int main(int numArg, char* args[]) {
    string linea;

    if(numArg == 1) {
        calcTiempoReacc(numArg, linea);
    }
    else {
        int n = stoi(args[1]);
        for(unsigned i = 1; i <= n; i++) {
            calcTiempoReacc(i, linea);
        }
    }

    return 0;
}
