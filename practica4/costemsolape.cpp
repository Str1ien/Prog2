//*****************************************************************
// File:   costemsolape.cpp
// Author: Alain Villagrasa, Programación II. Universidad de Zaragoza
// Date:   mayo 2022
// Coms:   Fichero de análisis de los algoritmos implementados en 
//		   el módulo «maxsolape»
//*****************************************************************

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <chrono>
#include "maxsolape.hpp"

const int DIF_CONJ = 50;
const int MIN_NINTER = 100;
const int MAX_NINTER = 4000;
//const string FICH_FBRUTA = "fbruta.txt";
//const string FICH_DYV = "dyv.txt";

using namespace std;


// Pre:  true
// Post: Ha devuelto un número real aleatorio entre «minini» y «maxfin».
double randDoubleIniFin() {
	return minini + double(rand()) / RAND_MAX * (maxfin - minini);
}

// Pre:  0 <= n <= MAX_INTER
// Post: Ha generado en «inters» n intervalos aleatorios entre
//		 «minini» y «maxfin»
void generarInters(double inters[N][2], const int n) {
	for (int i = 0; i < n; i++) {
		double num1 = randDoubleIniFin();
		double num2 = randDoubleIniFin();
	
		if (num1 < num2) {
			inters[i][0] = num1;
			inters[i][1] = num2;
		}
		else {
			inters[i][0] = num2;
			inters[i][1] = num1;
		}
	}
}


// Pre:  0 <= n <= MAX_INTER
// Post: Ha realizado el análisis en coste temporal de los dos métodos para calcular
//		 el solape máximo en un conjunto de «n» intervalos
void analisisConjunto(ofstream& fFBruta, ofstream& fDyV, double inters[N][2],
					  tpInter vInters[N], const int n) {
	//Generamos primero los intervalos aleatorios
	generarInters(inters, n);
	
	//Realizamos el análisis primero para el método de fuerza bruta
	auto iniFB = chrono::steady_clock::now();
	tpSolape solFBruta = maxSolFBruta(inters, n);
	auto finFB = chrono::steady_clock::now();
	
	//Escribimos los resultados en el fichero correspondiente
	fFBruta << n << " "
			<< chrono::duration_cast<chrono::microseconds>(finFB - iniFB).count() << endl;
	  		
	//Creamos el vector de «tpInter» que contendrá los intervalos y lo ordenamos
	crearvind(inters, vInters, n);
	mergesortIndInters(vInters, 0, n - 1);
	
	//Analizamos ahora el método que hace uso del esquema «Divide y Vencerás»
	auto iniDyV = chrono::steady_clock::now();
	tpSolape solDyV = maxSolDyV(vInters, 0, n - 1);
	auto finDyV = chrono::steady_clock::now();
	
	//Escribimos los resultados en el fichero correspondiente
	fDyV << n << " "
		 << chrono::duration_cast<chrono::microseconds>(finDyV - iniDyV).count() << endl;
}


// Pre:  
// Post: 
void analisisTotal(double inters[N][2], tpInter vInters[N]) {
	ofstream fFBruta("fbruta.txt");
	
	if (fFBruta.is_open()) {
		ofstream fDyV("dyv.txt");
		
		if (fDyV.is_open()) {
			for (int i = MIN_NINTER; i < MAX_NINTER; i += DIF_CONJ) {
				analisisConjunto(fFBruta, fDyV, inters, vInters, i);
			}
			
			fDyV.close();
		} else {
			cerr << "Error al escribir en el fichero \"" << "dyv.txt" << "\"" << endl;
		}
		
		fFBruta.close();
	} else {
		cerr << "Error al escribir en el fichero \"" << "fbruta.txt" << "\"" << endl;
	}
	
	//Creamos las gráficas con los costes temporales de ambos métodos para todos los 
	//conjuntos de intervalos aleatorios generados
	system("gnuplot -e \"set terminal gif; set style data lines; plot 'fbruta.txt'\" > fb.gif");
	system("gnuplot -e \"set terminal gif; set style data lines; plot 'dyv.txt'\" > dyv.gif");
}

// Programa que realiza un análisis del coste temporal de los algoritmos de resolución 
// de fuerza bruta y divide y vencerás para el problema del máximo solape entre intervalos 
// planteado en la práctica anterior
int main() {
	double inters[N][2];
	tpInter vInters[N];

    srand(time(nullptr));
	
	analisisTotal(inters, vInters);

    return 0;
}

