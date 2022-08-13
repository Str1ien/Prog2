//*****************************************************************
// File:   funcionesPilaEnt.cpp
// Author: Alain Villagrasa, Programación II. Universidad de Zaragoza
// Date:   febrero 2022
// Coms:   Fichero de implementación del módulo funcionesPilaEnt 
//		   para la práctica 2
//*****************************************************************

#include <iostream>
#include <iomanip>

#include "funcionesPilaEnt.hpp"

using namespace std;

const char BARRA = '|';
const char GUION = '-';



// * Pre:  p = [d_1, d_2, ..., d_K] AND K >= 0
// * Post: p = [d_1, d_2, ..., d_K] AND numDatos(p) = K
int numDatos(PilaEnt &p){
	if (estaVacia(p)) {
		return 0;
	}
	else {
		int datoK = cima(p);
		desapilar(p);
		int cont = 1 + numDatos(p);
		apilar(p, datoK);
		return cont;
	}
}

// Pre:  p = [d_1, d_2, ..., d_K]  AND K >= 0 AND anchura >= 1
// Post: p = [d_1, d_2, ..., d_K] y presenta por pantalla un listado de
//       los datos apilados en la pila comenzando por la cima, d_K, y acabando
//       por el del fondo de la pila, d_1. Cada dato lo escribe en una línea,
//       empleando <anchura> caracteres y alineado a la derecha. Cada dato es
//       precedido por el carácter '|' y es seguido por los caracteres ' ' y
//       '|', tal como se  ilustra a continuación. Tras el último dato se
//       presenta una linea de la forma "+--...--+", seguida por una línea
//       en blanco:
//
//        |     d_K |
//        |     ... |
//        |     d_2 |
//        |     d_1 |
//        +---------+
void mostrar(PilaEnt &p, const int anchura) {
	if (estaVacia(p)) {
		cout << "+" << string(anchura + 1, GUION) << "+" << endl;
	}
	else {
		int datoK = cima(p);
		cout << BARRA << right << setw(anchura) << datoK << " " << BARRA << endl;
		desapilar(p);
		mostrar(p, anchura);
		apilar(p, datoK);
	}
}

// Pre:  p = [d_1, d_2, ..., d_K] AND K >= 0 AND anchura >= 1
// Post: p = [d_1, d_2, ..., d_K] y presenta por pantalla un listado de los
//       datos apilados en la pila comenzando por el del fondo de la pila, d_1,
//       y acabando por el de la cima de la pila, d_K. Cada dato lo escribe
//       en una línea, empleando anchura caracteres y alineado a la derecha.
//       Cada dato es precedido por el carácter '|' y es seguido por los
//       caracteres ' ' y '|', tal como se  ilustra a continuación. Antes
//       del primer dato se presenta una linea de la forma "+--...--+":
//
//        +---------+
//        |     d_1 |
//        |     d_2 |
//        |     ... |
//        |     d_K |
void mostrarInvertida(PilaEnt &p, const int anchura) {
	if (estaVacia(p)) {
		cout << "+" << string(anchura + 1, GUION) << "+" << endl;
	}
	else {
		int datoK = cima(p);
		desapilar(p);
		mostrarInvertida(p, anchura);
		cout << BARRA << right << setw(anchura) << datoK << " " << BARRA << endl;
		apilar(p, datoK);
	}
}



// Pre:  p = [d_1, d_2, ..., d_K] AND K >= 0
// Post: p = [d_2, ..., d_K]
void eliminarFondo(PilaEnt &p) {
	if (!estaVacia(p)) {
		int datoK = cima(p);
		desapilar(p);
		if (!estaVacia(p)) {
			eliminarFondo(p);
			apilar(p, datoK);
		}
	}
}

// Pre:  p = [d_1, ..., d_{(K-i)}, d_{(K-i+1)}, d_{(K-i+2)}, ..., d_K] AND 0<= K AND 1<= i <= K
// Post: p = [d_1, ..., d_{(K-i)}, d_{(K-i+2)}, ..., d_K]
void eliminar(PilaEnt &p, const int i) {
	if(!estaVacia(p)) {
		if (i == 1) {
			desapilar(p);
		}
		else {
			int datoK = cima(p);
			desapilar(p);
			eliminar(p, i - 1);
			apilar(p, datoK);
		}
	}
}

// Pre:  p = [d_1, d_2, ..., d_K] AND K >= 0
// Post: p = [nuevo, d_1, d_2, ..., d_K]
void insertarEnFondo(PilaEnt &pila, const int nuevo) {
	if (estaVacia(pila)) {
		apilar(pila, nuevo);
	}
	else {
		int datoK = cima(pila);
		desapilar(pila);
		insertarEnFondo(pila, nuevo);
		apilar(pila, datoK);
	}
}

