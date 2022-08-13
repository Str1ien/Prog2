//*****************************************************************
// File:   calmslope.cpp
// Author: Alain Villagrasa, Programación II. Universidad de Zaragoza
// Date:   abril 2022
// Coms:   Fichero de pruebas del módulo «maxsolape» para
//		   la práctica 3
//*****************************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include "maxsolape.hpp"

using namespace std;

const unsigned DEC = 1;

// Pre:  «indinters» contiene una serie de intervalos, y «msg» un mensaje adicional que
//		 se desea mostrar.
// Post: Ha mostrado por pantalla todos los intervalos contenidos en «intinters» junto
//		 al mensaje adicional.
void muestraInters(const tpInter indinters[N], const int n, const string msg) {
	cout << "Los intervalos a tratar son " << msg << ": " << endl;
	for (unsigned i = 0; i < n; i++) {
		cout << fixed << setprecision(DEC) << "Ind: " << indinters[i].ind << ", ini: "
			 << indinters[i].ini << ", fin: " << indinters[i].fin << endl << endl;
	}
}

// Pre:  n >= 0
// Post: Ha realizado las pruebas del cálculo de solape máximo de los intervalos de «intervalos»
//		 mediante el método de fuerza bruta.
void pruebasSolapeFBruta(double intervalos[N][2], const unsigned n) {	
	tpInter indinters[N];
	
	crearvind(intervalos, indinters, n); // Construimos el vector con los intervalos y sus índices
	muestraInters(indinters, n, ""); //Mostramos los intervalos
	
	tpSolape maxFBruta = maxSolFBruta(intervalos, n);
	cout << "Y la pareja con mayor solape calculado por fuerza bruta es: " << maxFBruta.interA
		 << " y " << maxFBruta.interB << ", con solape = " << maxFBruta.solape << endl;
}

// Pre:  n >= 0
// Post: Ha realizado las pruebas del cálculo de solape máximo de los intervalos de «intervalos»
//		 mediante el método de divide y vencerás.
void pruebasSolapeDyV(double intervalos[N][2], const unsigned n) {
	tpInter indinters[N];
	crearvind(intervalos, indinters, n); // Construimos el vector con los intervalos y sus índices
	mergesortIndInters(indinters, 0, n - 1); //Ordenamos el vector 

	muestraInters(indinters, n, "(ahora ordenados)");
	tpSolape maxDyV = maxSolDyV(indinters, 0, n - 1);
	
	cout << "Y la pareja con mayor solape calculado por D y V es: "
		 << indinters[maxDyV.interA].ind << " y " << indinters[maxDyV.interB].ind
		 << ", con solape = " << maxDyV.solape << endl;
}


int main() {

	double intervalos1[N][2] = {{1.5, 8.0}, {0.0, 4.5}, {2.0, 4.0},
							    {1.0, 6.0}, {3.5, 7.0}};
	double intervalos2[N][2] = {{2.0, 4.0}, {0.0, 1.5}, {1.5, 8.0}, 
								{1.0, 6.0}, {4.0, 7.5}, {3.0, 5.0}, 
								{3.5, 7.0}, {0.5, 2.5}};
	//Pruebas para «intervalos1» (fbruta y DyV respectivamente):
	unsigned n = 5;
	pruebasSolapeFBruta(intervalos1, n);
	pruebasSolapeDyV(intervalos1, n);
	cout << endl;
	
	//Pruebas para «intervalos2» (fbruta y DyV respectivamente):
	n = 8;
	pruebasSolapeFBruta(intervalos2, n);
	pruebasSolapeDyV(intervalos2, n);
	
	
	return 0;
}
