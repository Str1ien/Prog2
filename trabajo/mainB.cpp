//*****************************************************************
// File:   mainB.cpp
// Author: Alain Villagrasa (NIP 816787) & Carlos de Vera (NIP 848481),
// 		   Programación II. Universidad de Zaragoza.
// Date:   mayo 2022
// Coms:   Fichero principal del trabajo práctico de la asignatura.
//		   En él se hace uso del módulo «betris» para implementar y 
//		   resolver el problema planteado.
//*****************************************************************

#include <iostream>
#include <ctime>
#include "betris.hpp"

using namespace std;

// Pre:  objetivo >= 0 ∧ nPiezas = 0
// Post: Ha leido los valores de objetivo, retardo, las fichas a colocar y el tamaño del tablero
//       por la entrada estándar
void tomarDatos(int &objetivo, int &retardo, int vEntrada[MAXENTRADA], int &nPiezas,
				tpTablero &tablero) {
	cin >> tablero.nfils >> tablero.ncols >> objetivo >> retardo >> vEntrada[0];
	
	while(vEntrada[nPiezas] >= 0) {
		cin >> vEntrada[nPiezas + 1];
		nPiezas++;
	}
}


// Pre:  a >= b
// Post: Ha devuelto un número entero pseudo-aleatorio en el intervalo [a, b].
int randInt(const int a, const int b) {
    return a + rand() % (b - a + 1);
}


// Pre:  0 < nPiezas < MAXENTRADA  
// Post: ∀ α ∊ [0,nPiezas]. ∃ β ∊ [0,PIEZASDEF].vEntrada[α] = β
void generarPiezas(int vEntrada[MAXENTRADA], const int nPiezas) {
	srand(time(nullptr));
	
	//Rellenamos el vector con las piezas aleatorias
	for (int i = 0; i < nPiezas; i++) {
		vEntrada[i] = randInt(0, PIEZASDEF - 1); 
	}
	
	//Finalizamos la secuencia con -1
	vEntrada[nPiezas] = -1;
}


// Pre:  0 < nPiezas <= MAXENTRADA ∧ -1 <= piezasColoc <= nPiezas
// Post: Ha escrito por terminal el numero de piezas colocadas y las columnas en
//		 las que se han colocado las piezas
void mostrarRes(const int vEntrada[MAXENTRADA], const int nPiezas, const int vSalida[MAXENTRADA],
				const int piezasColoc) {	
	cout << "Entrada (números de piezas): ";
	
	for (int i = 0; i < nPiezas; i++) {
		cout << vEntrada[i] << " ";  //Imprime en pantalla una lista de las piezas a colocar
	}
	
	cout << endl << "Número de piezas colocadas: " << piezasColoc << endl;
	cout << "Salida (número de columnas): ";
	
	if (piezasColoc != -1) {
		for (int i = 0; i < piezasColoc; i++) {  //Si las piezas se han podido colocar, 
			cout << vSalida[i] << " ";           //el vector vSalida se imprime en pantalla
		}
	}
	
	cout << endl;
}


// Pre:  true
// Post: Ha tomado los datos de la entrada de la linea de comandos
//       y ha intentado resolver el juego del betris con esos datos,
//       mostrando los resultados de dicha resolucion al final del programa.
int main() {
	int objetivo, retardo, nPiezas = 0;
	int vEntrada[MAXENTRADA] = {};
	tpTablero tablero;
	
	tomarDatos(objetivo, retardo, vEntrada, nPiezas, tablero);
	
	//Si en la entrada de la linea de comandos la primera pieza tiene un valor negativo
	//se generaran tantas piezas aleatorias como valor absoluto tenga esa primera pieza
	if (vEntrada[0] < 0) {
		nPiezas = -vEntrada[0];
		generarPiezas(vEntrada, nPiezas);
	}
	
	//Vector con las columnas donde se encuentran las piezas de la solucion
	int vSalida[MAXENTRADA]; 
	
	//Inicializamos el tablero, es decir rellenamos cada componente de la matriz con un -1
	inicializarTablero(tablero);
	
	//Buscamos la solución y guardamos el número de piezas colocadas
	int piezasColoc = buscaSolucion(tablero, vEntrada, vSalida, objetivo, 0, retardo);
	
	//Si el retardo es negativo, o no hemos encontrado solución, mostrara el tablero en su
	//estado final (o bien la solución, o bien el tablero vacío).
	if(piezasColoc == -1 || retardo <= 0) {
		mostrarTablero(tablero,vEntrada);
	}
	
	mostrarRes(vEntrada, nPiezas, vSalida, piezasColoc);
	
	return 0;
}
