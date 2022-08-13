//*****************************************************************
// File:   betris.cpp
// Author: Alain Villagrasa (NIP 816787) & Carlos de Vera (NIP 848481), 
//		   Programación II. Universidad de Zaragoza.
// Date:   mayo 2022
// Coms:   Fichero de implementación del módulo «betris» del trabajo 
//		   práctico de la asignatura.
//*****************************************************************

#include <iostream>
#include <string>
#include "betris.hpp"
#include <unistd.h>

using namespace std;

//Constantes a utilizar
const int MICROS_TO_MILIS = 1000;	//Para convertir microsegundos a milisegundos
const string ESC_COLOR = "\033[";	//Inicio de secuencia ANSII para insertar colores
const string RESET = "m \033[0m";	//Reset de código ANSII (incluye el final de la
									//secuencia anterior y el carácter espacio ' ' para 
									//mostrar cada celda)


// Pre:  true
// Post: Todas las componentes de tablero.matriz son -1 (casilla vacía)
void inicializarTablero(tpTablero &tablero) {
	for (int i = 0; i < tablero.nfils; i++) {
		for (int j = 0; j < tablero.ncols; j++) {
			tablero.matriz[i][j] = -1;
		}
	}
}


// Pre:  -1 <= celda <= MAXENTRADA ∧ vEntrada contiene los números de las piezas que entran
// Post: Ha escrito por la salida estándar la celda con su color correspondiente,
// 		 o una casilla en negro si la celda no está ocupada.
void mostrarCelda(const int celda, const int vEntrada[MAXENTRADA]) {
	if (celda >= 0) {
	 	//Accedemos al color de la pieza mediante el vector «vPiezas» y el índice 
	 	//en «vEntrada»
		cout << ESC_COLOR << vPiezas[vEntrada[celda]].color << RESET;
	}
	else {
		cout << ESC_COLOR << NEGRO << RESET;
	}
}


// Pre:  vEntrada contiene los números de las piezas que entran y tablero contiene
//       el estado actual del tablero, en el que pueden estar colocadas algunas 
//       de dichas piezas.
// Post: Se ha mostrado el tablero por pantalla (cada pieza se ha dibujado con su color)
void mostrarTablero(const tpTablero & tablero, const int vEntrada[MAXENTRADA]) {
	system("clear");
	
	for (int i = 0; i < tablero.nfils; i++) {
		for (int j = 0; j < tablero.ncols; j++) {
			mostrarCelda(tablero.matriz[i][j], vEntrada);
			if (j == tablero.ncols - 1) {
				cout << endl;
			}
		}
	}
}


// Pre:  0 <= objetivo < tablero.nfils ∧ tablero contiene el estado actual del tablero
// Post: Ha devuelto true si el numero de filas completas sin huecos es igual a objetivo
bool esSolucion(const tpTablero &tablero, const int objetivo) {
	int filasLlenas = 0; //En principio hay 0 filas llenas 
	
	for (int i = 0; i < tablero.nfils; i++) {
		bool filaLlena = true;
		int j = 0;
		while (j < tablero.ncols && filaLlena) {
			if (tablero.matriz[i][j] == -1) {			
				filaLlena = false; //Si hay una celda de la fila que está vacía,
			}	                   //pasamos a la siguiente fila		
			j++;					   
		}
		
		if (filaLlena){	//Si la fila estaba llena incrementamos el nº de filas llenas
			filasLlenas++;
		}
	}
	
	return filasLlenas == objetivo; //Devolvemos si se ha cumplido objetivo filas
}									//para este estado del tablero


// Pre:  0 <= b < tablero.ncols ∧ 0 <= n < ∧ tablero contiene el estado actual del tablero
// Post: Ha devuelto true si en la posicion (a, b) de la matriz 
//       del tablero se puede colocar la pieza, es decir, no hay
//       celdas de la pieza fuera de rango o no estan en una posicion
//       ocupada por otra pieza; y ha guardado en «a» la mayor fila posible
//       en la cual se puede colocar la pieza. En caso contrario devuelve 
//       false y guarda -1 en «a»
int puedoColocar(const tpTablero &tablero, const int b, const int n, 
				 const int vEntrada[MAXENTRADA]) {
	bool puedoColocar = true;
	tpPieza piezaAColocar = vPiezas[vEntrada[n]]; //Pieza a tratar
	int a = -1;
	
	for (int i = 0; i < tablero.nfils; i++) {
		int j = 0;
		
		while (j < TAMPIEZA && puedoColocar) { //Iteramos para todas las celdas de la pieza  
		    //Las coordenadas de la celda relativas a la esquina sup izqda de ella (a, b)
			int coordenadaX = piezaAColocar.forma[j][0];
			int coordenadaY = piezaAColocar.forma[j][1];
			
			//Si esas coordenadas en el tablero están ocupadas o fuera de rango, 
			//no podemos colocar la pieza allí
			bool posicionOcupada = tablero.matriz[i + coordenadaX][b + coordenadaY] != -1;
			bool fueraRango = (i + coordenadaX >= tablero.nfils) ||
							  (b + coordenadaY >= tablero.ncols);

			if (posicionOcupada || fueraRango) {
				puedoColocar = false; 
			}
			j++;
		}
		
		if(puedoColocar) {
			a = i;
		}
	}
	//Si hemos podido colocar, devolvemos la fila de la columna «a» en la que podemos 
	//colocar la pieza, en caso contrario devolvemos -1.
	return a;
}


// Pre:  0 <= a < tablero.nfils ∧ 0 <= b < tablero.ncols ∧ 0 <= p <= MAXENTRADA
// Post: Ha colocado la pieza en la matriz del tablero
void colocarPieza(tpTablero &tablero, const int a, const int b, const int p,
				  const int vEntrada[MAXENTRADA]) {
	for (int i = 0; i < TAMPIEZA; i++) {
		int coordenadaX = vPiezas[vEntrada[p]].forma[i][0];
		int coordenadaY = vPiezas[vEntrada[p]].forma[i][1];
		
		//Colocamos la pieza (su índice en vEntrada) en el tablero, con las coordendas 
		//relativas a la posición (a, b)
		tablero.matriz[a + coordenadaX][b + coordenadaY] = p;
	}
}


// Pre:  0 <= a < tablero.nfils ∧ 0 <= b < tablero.ncols ∧ 0 <= p <= MAXENTRADA
//		 ∧ «vEntrada» contiene las piezas a utilizar en el juego ∧ tablero contiene
//		 el estado actual del tablero
// Post: Ha quitado la n-ésima pieza de la matriz del tablero
void quitarPieza(tpTablero &tablero, const int a, const int b, const int p, 
				 const int vEntrada[MAXENTRADA]) {
	for (int i = 0; i < TAMPIEZA; i++) {
		int coordenadaX = vPiezas[vEntrada[p]].forma[i][0];
		int coordenadaY = vPiezas[vEntrada[p]].forma[i][1];
		
		//Quitamos la pieza en el tablero, con las coordendas relativas a la posición
		//(a, b)
		tablero.matriz[a + coordenadaX][b + coordenadaY] = -1;
	}
}


// Pre:  En el tablero se han colocada las n primeras piezas de vEntrada,
//       en la columnas indicadas respectivamente en vSalida.
// Post: Si las piezas colocadas completan al menos objetivo filas sin huecos,
//       entonces devuelve el número de piezas colocadas, en vSalida las columnas
//       en las que se han colocado las piezas y el tablero con las piezas colocadas,
//       si no devuelve -1.
int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA],
				  const int objetivo, int n, const int retardo) {	  
	int res = -1;
	
	if (esSolucion(tablero, objetivo)) {
		return n;
	}
	
	else {	
		int col = 0;
		bool fin = false;
		while (col < tablero.ncols && !fin) {
			int fila = puedoColocar(tablero, col, n, vEntrada);
			//Si nos quedan piezas por colocar y la posicion es válida,
			if (fila != -1) {
				//la colocamos y ponemos en vSalida la columna donde la hemos colocado.
				colocarPieza(tablero, fila, col, n, vEntrada);
				vSalida[n] = col;
				if (retardo > 0) {
					//Si el usuario ha introducido retardo, vamos mostrando
					//el tablero en cada iteración y esperamos «retardo» milisegundos
					mostrarTablero(tablero, vEntrada);
					usleep(MICROS_TO_MILIS * retardo);
				}
				
				//Llamada recursiva con la pieza colocada (una pieza más = n + 1),
				//si no hemos encontrado solución quitamos la pieza, e iteramos
				res = buscaSolucion(tablero, vEntrada, vSalida, objetivo, n + 1, retardo);
				if (res == -1) {
					quitarPieza(tablero, fila, col, n, vEntrada);
				}
				
				else {
					fin = true; //De otra forma, finalizamos el bucle (cortocircuito)
				}				//y devolvemos el número de piezas colocadas
			}
			col++;
		}
		return res;
	}
}

