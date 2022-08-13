//*****************************************************************
// File:   calculos.cpp
// Author: Alain Villagrasa, Programación II. Universidad de Zaragoza
// Date:   febrero 2022
// Coms:   Fichero de implementación de calculos.hpp
//         Para la práctica 1
//*****************************************************************

#include "calculos.hpp"

using namespace std;

// Pre:  n >= 0 ∧ 2 <= b <= 10
// Post: (n = 0 -> numCifras(n,b) = 1) ∧
//       (n > 0 -> numCifras(n,b) = NC ∧  n >= b^(NC-1) ∧ n < b^NC)
int numCifras(const int n, const int b) {
	if (n < b) {
		return 1; //Caso base
	}
	else {
		return 1 + numCifras(n / b, b); //Caso recurrente
	}
}

// Pre:  n >= 0 ∧ i >= 1 ∧ 2 <= b <= 10
// Post: cifra(n,b,i) = (n / b^(i-1)) % b
int cifra(const int n, const int i, const int b) {
	if (i == 1) {
		return n % b; //Caso base
	}
	else {
		return cifra(n / b, i - 1, b); //Caso recurrente
	}
}
// Pre:  n >= 0 ∧ 2 <= b <= 10
// Post: cifraMayor(n,b) = (Max α∊[1,∞].cifra(n,α,b))
int cifraMayor(const int n, const int b) {
	if(n < b) {
		return n; //Caso base
	}
	else {
		int ultimoDigito = n % b;
		int otroDigito = cifraMayor(n / b, b); //Caso recurrente
		
		if(ultimoDigito > otroDigito) { 
			return ultimoDigito;
		}
		else {
			return otroDigito;
		}	
	}
}
// Pre:  n >= 0 ∧ 2 <= b <= 10
// Post: cifraMasSignificativa(n) = n / b^(NC-1)
//       ∧ (n >= b^(NC-1) ∧ n < b^NC)
int cifraMasSignificativa(const int n, const int b) {
	if(n < b) {
		return n; //Caso base
	}
	else {
		return cifraMasSignificativa(n / b, b); //Caso recurrente
	}
}


// Pre:  n >= 0 ∧ 2 <= b <= 10
// Post: sumaCifras(n,b) = (∑ α∊[1,∞].cifra(n,α,b))
int sumaCifras(const int n, const int b) {
	if(n < b) {
		return n; //Caso base
	}
	else {
		return n % b + sumaCifras(n / b, b); //Caso recurrente
	}
}

