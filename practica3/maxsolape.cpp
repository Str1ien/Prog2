//*****************************************************************
// File:   maxsolape.cpp
// Author: Alain Villagrasa, Programación II. Universidad de Zaragoza
// Date:   abril 2022
// Coms:   Fichero de implementación del módulo «maxsolape» para
//		   la práctica 3
//*****************************************************************
#include <iostream>
#include <iomanip>
#include "maxsolape.hpp"

using namespace std;

// calcSolape devuelve el solape entre los intervalos interA y interB
double calcSolape(const tpInter interA, const tpInter interB) {
	if ((interA.fin <= interB.ini) || (interA.ini >= interB.fin)) {
		return 0.0; // Los intervalos no se solapan
	}
	else {
		double l = max(interA.ini, interB.ini);
		double r = min(interA.fin, interB.fin);
		
		return r - l;
	}
}


// Pre:  0 <= i < N, inters[a][0] <= inters[a][1]
// Post: Devuelve en tpIntervalo correspondiente al especificado
//       por la fila ind de la matriz inters
tpInter leerInter(const double inters[N][2], const int i) {
    return {i, inters[i][0], inters[i][1]};
}


// maxSolFBruta devuelve un registro tpSolape en el que el campo solape
// es el maximo solape entre parejas de los n primeros intervalos de inters,
// y los campos interA e interB son los indices de dichos intervalos.
// Para la matriz inters de ejemplo, el resultado es solape=4.5, interA=0,
// interB=3
// (los valores de interA e interB pueden estar intercambiados, es decir,
// el resultado para el ejemplo anterior tambi�n puede ser solape=4.5,
// interA = 3, interB = 0).
tpSolape maxSolFBruta(double inters[N][2], int n) {
	tpSolape solapeMax = {-1, -1, 0};  // El solape máximo antes de mirar ningún intervalo es 0

	for (unsigned i = 0; i < n - 1; i++) { 	// Recorremos el vector comparando hasta encontrar 
		tpInter interA = leerInter(inters, i);
		for (unsigned j = i + 1; j < n; j++) {	// la pareja con mayor solape
			tpInter interB = leerInter(inters, j);
			double solape = calcSolape(interA, interB);
			
			if (solape > solapeMax.solape) {
				solapeMax.solape = solape;
				solapeMax.interA = i;
				solapeMax.interB = j;
			}
		}
	}
	return solapeMax;
}


// Crea un vector de tpInter con los n primeros intervalos de inters.
// Por ejemplo para la matrix inters de la funcion anterior y n=5, los
// valores de indinters seran:
// [{ind: 0, ini: 1.5, fin: 8.0},
//  {ind: 1, ini: 0.0, fin: 4.5},
//  {ind: 2, ini: 2.0, fin: 4.0},
//  {ind: 3, ini: 1.0, fin: 6.0},
//  {ind: 4, ini: 3.5, fin: 7.0}]
void crearvind(double inters[N][2], tpInter indinters[N], int n){
	for (unsigned i = 0; i < n; i++) {
		indinters[i] = leerInter(inters, i);
	}
}


// Pre:  0 <= p <= m <= f <= N
// Post: Ha ordenado el vector «indinters» de menor a mayor inicio de cada intervalo.
void merge(tpInter indinters[N], int p, int m, int f) {
	tpInter aux[N];
	int h = p, i = p, j = m + 1;
	while (h <= m && j <= f) {
		if (indinters[h].ini <= indinters[j].ini) {
			aux[i] = indinters[h];
			h++;
		}
		else {
			aux[i] = indinters[j];
			j++;
		}
		i++;
	}
	if (h > m) {
		for (int k = j; k <= f; k++) {
			aux[i] = indinters[k];
			i++;
		}
	}
	else {
		for (int k = h; k <= m; k++) {
			aux[i] = indinters[k];
			i++;
		}
	}
	for (int k = p; k <= f; k++) {
		indinters[k] = aux[k];
	}
}


// Ordena con el algoritmo mergesort los intervalos de indinters
// comprendidos entre las componentes indexadas por p y f, ambas incluidas,
// de acuerdo al valor de inicio de los intervalos (orden creciente).
// Por ejemplo, para el vector de la funcion anterior, p=0 y f=4, el vector
// ordenado sera:
// [{ind: 1, ini: 0.0, fin: 4.5},
//  {ind: 3, ini: 1.0, fin: 6.0},
//  {ind: 0, ini: 1.5, fin: 8.0},
//  {ind: 2, ini: 2.0, fin: 4.0},
//  {ind: 4, ini: 3.5, fin: 7.0}]
void mergesortIndInters(tpInter indinters[N], int p, int f) {
	if (p < f) {
		int medio = (p + f) / 2;
		mergesortIndInters(indinters, p, medio);
		mergesortIndInters(indinters, medio + 1, f);
		merge(indinters, p, medio, f);
	}
}

// Pre:  0 <= p <= m <= N ∧ ∀ α ∊ [p, m - 1]. indinters[α].ini <= indinters[α + 1].ini
// Post: Ha calculado el intervalo con mayor fin entre los índices p y m del vector, y ha
//		 devuelto el índice de dicho intervalo en el vector de intervalos «indinters».	 
int indMayorFin(tpInter indinters[N], int p, int m) {
	int max = p;	//El intervalo con mayor fin antes de empezar es el primero
	for (int i = p + 1; i <= m; i++) { 
		if (indinters[i].fin > indinters[max].fin) {
			max = i;
		}
	}
	return max;
}


// Pre:  0 <= p <= m <= f <= N
// Post: Ha devuelto el solape máximo entre el intervalo de mayor fin de la primera mitad 
//		 [p, m], y los intervalos de la segunda mitad [m, f] del vector de intervalos
//		 «indinters»
tpSolape interMax(tpInter indinters[N], int p, int m, int f) {
	int indMaxFin = indMayorFin(indinters, p, m);

	tpInter maxFinMitad1 = indinters[indMaxFin];
	tpSolape solapeMax = {0, 0, 0};
	for (int i = m + 1; i <= f; i++) {
		double solape = calcSolape(indinters[i], maxFinMitad1);
		if (solape > solapeMax.solape) {
			solapeMax.solape = solape;
			solapeMax.interA = i;
			solapeMax.interB = indMaxFin;
		}
	}

	return solapeMax;
}


// Pre:  «s1», «s2» y «s3» contienen solapes entre 2 intervalos.
// Post: Ha devuelto el solape máximo de los 3.
tpSolape maxSolape(tpSolape s1, tpSolape s2, tpSolape s3) {
	if (s1.solape > s2.solape && s1.solape > s3.solape) {
		return s1; //El mayor es «s1»
	}
	else if (s2.solape > s1.solape && s2.solape > s3.solape) {
		return s2; //El mayor es «s2»
	}
	else {
		return s3; //El mayor es «s3»
	}
}


// Dado un vector indinters, utiliza la tecnica de Divide y Venceras para
// devolver el maximo solape entre parejas de intervalos comprendidos
// entre las componentes indexadas por p y f, ambas incluidas.
// Por ejemplo, para el vector del procedimiento anterior,
// el resultado es solape=4.5, interA=0, interB=3
tpSolape maxSolDyV(tpInter indinters[N], int p, int f) {
	if (p == f) {
		return {p, f, 0};
	}
	else {
		int medio = (p + f) / 2;
		tpSolape maxMitad1 = maxSolDyV(indinters, p, medio);
		tpSolape maxMitad2 = maxSolDyV(indinters, medio + 1, f);
		tpSolape maxFin = interMax(indinters, p, medio, f);
		
		return maxSolape(maxMitad1, maxMitad2, maxFin);
	}
}

