//*****************************************************************
// File:   pruebas01.cpp
// Author: Programación II. Universidad de Zaragoza
// Date:   febrero 2022
// Coms:   Programa de pruebas del comportamiento de las funciones
//         definidas en el módulo calculos para la práctica 1
//*****************************************************************

#include <iostream>
#include <cmath>
#include <string>
#include "calculos.hpp"

using namespace std;

const string red = "\033[0;31m";
const string green = "\033[0;32m";
const string yellow = "\033[0;33m";
const string reset = "\33[0m";

// Pre:  <b> es una base de representación.
// Post: Ha escrito en la terminal en color amarillo un mensaje informando al usuario
//		 de la base de representación que se va a utilizar.
void escribirBase(const unsigned b) {
	cout << yellow << "Para b = " << b << ":" << reset << endl;
}

// Pre:  <cifra> es el número de cifras de <n> cuando se escribe en base <b>
//       y <b> está comprendido entre 2 y 10
// Post: Informa si el valor devuelto al ejecutar numCifras(n, b) es igual
//       a <cifras> o no lo es
void probarNumCifras(const int n, const int b, const int cifras) {
    int r = numCifras(n, b);
    if (r == cifras) {	//Mensaje de éxito
        cout << green << "Ok." << reset <<  " numCifras(" << n << "," << b << ") = "
        	 << r << endl;
    } else {	//Mensaje de error
        cout << red << "Mal." << reset << " numCifras(" << n << "," << b << ") = " << r 
        	 << " pero debiera ser " << cifras << endl;
    }
}


// Prueba el comportamiento de numCifras(n,10) para los siguientes valores de n:
// 0, 1, 9, 10, 99, 100, 999, 1000, ... , 99999, 100000, 99999 y 1000000
// y prueba el comportamiento de numCifras(n,2) para los siguientes valores de n:
// 0, 1, 1, 2, 3, 4, 7, 8, 15, 16, 31, 32, ..., 4095, 4096, 8191 y 8192
void probarNumCifras() {
	cout << "Pruebas del comportamiento de la función numCifras(n, b):" << endl << endl;	
	
    // Prueba el comportamiento de numCifras(n, 10) para los siguientes valores de n:
    // 0, 1, 9, 10, 99, 100, 999, 1000, ..., 99999, 100000, 99999 y 1000000
    unsigned b = 10;
    escribirBase(b);
    
    probarNumCifras(0, b, 1);
    probarNumCifras(1, b, 1);
   	
    int n = 10;
    unsigned cifras = 2;
    while (n <= 1000000) {
        probarNumCifras(n - 1, b, cifras-1);
        probarNumCifras(n, b, cifras);
        n = b * n;
        cifras++;;
    }
    cout << endl;
    // Prueba el comportamiento de numCifras(n,2) para los siguientes valores de n:
    // 0, 1, 2, 3, 4, 7, 8, 15, 16, 31, 32, ..., 4095, 4096, 8191 y 8192
    b = 2;
    escribirBase(b);
    
    probarNumCifras(0, b, 1);
    
    n = 2;
    cifras = 2;
    while (n <= 10000) {
        probarNumCifras(n - 1, b, cifras-1);
        probarNumCifras(n, b, cifras);
        n = b * n;
        cifras++;
    }
    cout << endl;
}


// Pre:  <n> es el número natural y <b> está comprendido entre 2 y 10
// Post: Informa si los valores devueltos al ejecutar cifra(n, i, b) corresponden
//       o no a la i-ésima cifra de <n>, cuando este número se escribe en base <b>
void probarCifra(const int n, const int i, const int b, const int laCifra) {
	int r = cifra(n, i, b);
	if (r == laCifra) {	//Mensaje de éxito
		cout << green << "Ok." << reset << " cifra(" << n << ", " << i << ", " << b << ") = " 
			 << r << endl;
	}
	else {	//Mensaje de error
		cout << red << "Mal." << reset << " cifra(" << n << ", " << i << ", " << b << ") = " 
			 << r << " pero debería ser " << laCifra << endl;
	}
}

// Prueba el comportamiento de cifra(n,i,b) para diferentes números naturales
// en las bases de numeración 2 y 10
void probarCifra() {
	cout << "Pruebas del comportamiento de la función cifra(n, i, b):" << endl << endl;	
	
	// Prueba el comportamiento de cifra(n, i, 10) para los siguientes valores de n e i:
    // (0,1), (1, 1), (21, 1), (21, 2), (321, 1), (321, 2), (321, 3), (4321, 1), 
    // (4321, 2), (4321, 3), (4321, 4), ... , (87654321, 9).
    unsigned b = 10;
    escribirBase(b);
    
    probarCifra(0, 1, b, 0);
    probarCifra(1, 1, b, 1);
    
    int n = 21;
    while (n < 987654321) {
    	unsigned cifra = 1;
    	while (cifra <= numCifras(n, b)) {
        	probarCifra(n, cifra, b, cifra);
        	cifra++;
        }
        n += pow(b, cifra - 1) * cifra;
    }
    cout << endl;
    
    // Prueba el comportamiento de cifra(n, i, 2) para los siguientes valores de n e i:
    // (0,1), (1, 1), (5, 1) (5, 2), (9, 1), (9, 2), (17, 1), (17, 2), 33, 1), (33, 2), 
    // ((65, 1), (65, 2), ... , (1025, 1), (1025, 2).
    b = 2;
    escribirBase(b);
    
    probarCifra(0, 1, b, 0);
    probarCifra(1, 1, b, 1);
    
    n = 5;
    while (n < 2048) {
		int cifra = 1;
        probarCifra(n, cifra, b, cifra);   
        probarCifra(n, cifra + 1, b, cifra - 1);
        n = (n - 1) * b + 1;
    }
    cout << endl;
}


// Pre:  <n> es el número natural y <b> está comprendido entre 2 y 10 y <laMayor> es
//       el valor de la mayor de las cifras de <n> cuando se escribe en base <b>
// Post: Informa si el valor devuelto al ejecutar cifraMayor(n, b) coincide con el
//       de <laMyor>, cuando <n> se escribe en base <b>
void probarCifraMayor(const int n, const int b, const int laMayor) {
	int r = cifraMayor(n, b);
	if(r == laMayor) {	//Mensaje de éxito
		cout << green << "Ok." << reset << " cifraMayor(" << n << ", " << b << ") = "
			 << r << endl;
	}
	else {	//Mensaje de error
		cout << red << "Mal." << reset << " cifraMayor(" << n << ", " << b << ") = " << r 
			 << " pero debería ser " << laMayor << endl;
	}
}


// Prueba el comportamiento de cifraMayor(n,b) para diferentes números naturales
// en las bases de numeración 2, 8 y 10
void probarCifraMayor() {
	cout << "Pruebas del comportamiento de la función cifraMayor(n, b):" << endl << endl;	
	
	// Prueba el comportamiento de cifraMayor(n, 10) para los siguientes valores de n:
    // 0, 1, 21, 321, 4321, 54321, ... , 87654321
    unsigned b = 10;
    escribirBase(b);
    
    probarCifraMayor(0, b, 0);
    probarCifraMayor(1, b, 1);
    
    int n = 21;
    int cifra = 2;
    while (n < 987654321) {
        probarCifraMayor(n, b, cifra);
        cifra++;
        n += pow(b, cifra - 1) * cifra;
    }
    cout << endl;
    
    // Prueba el comportamiento de cifraMayor(n, 8) para los siguientes valores de n:
    // 0, 1, 66, 514, 4098, 32770, 262145, 2097154.
    b = 8;
    escribirBase(b);
    
    probarCifraMayor(0, b, 0);
    probarCifraMayor(1, b, 1);
    
    n = 66;
    while (n < 16777218) {
    	int cifra = 2;
        probarCifraMayor(n, b, cifra);
        n = (n - cifra) * b + cifra;
    }
    cout << endl;
    
    // Prueba el comportamiento de cifraMayor(n, 2) para los siguientes valores de n:
    // 0, 1, 4, 8, 16, 32, ... , 1024
    b = 2;
    escribirBase(b);
    
    probarCifraMayor(0, b, 0);
    probarCifraMayor(1, b, 1);
    
    n = 4;
    while (n < 10000) {
		int cifra = 1;
        probarCifraMayor(n, b, cifra);   
        n *= b;
    }
    cout << endl;
}


// Pre:  <n> es el número natural y <b> está comprendido entre 2 y 10 y <laMasSignificativa>
//       es el valor de cifra más significativa de <n> cuando se escribe en base <b>
// Post: Informa si el valor devuelto al ejecutar cifraMasSignificativa(n, b) coincide
//       con el de <laMasSignificativa>, cuando <n> se escribe en base <b>
void probarCifraMasSignificativa(const int n, const int b, const int laMasSignificativa) {
	int r = cifraMasSignificativa(n, b);
	if(r == laMasSignificativa) {	//Mensaje de éxito
		cout << green << "Ok." << reset << " cifraMasSignificativa(" << n << ", "
			 << b << ") = " << r << endl;
	}
	else {	//Mensaje de error
		cout << red << "Mal." << reset << " cifraMasSignificativa(" << n << ", "
			 << b << ") = " << r << " pero debería ser " << laMasSignificativa << endl;
	}
}


// Prueba el comportamiento de cifraMasSignificativa(n,b) para diferentes números naturales
// en las bases de numeración 2, 8 y 10
void probarCifraMasSignificativa() {
	cout << "Pruebas del comportamiento de la función cifraMasSignificativa(n, b):"
		 << endl << endl;	
	
	// Prueba el comportamiento de cifraMasSignificativa(n, 10) para los siguientes valores de n:
    // 0, 1, 21, 321, 4321, 54321, ... , 87654321
    unsigned b = 10;
    escribirBase(b);
    
    probarCifraMasSignificativa(0, b, 0);
    probarCifraMasSignificativa(1, b, 1);
    
    int n = 21;
    int cifra = 2;
    while (n < 987654321) {
    	
        probarCifraMasSignificativa(n, b, cifra);
        cifra++;
        n += pow(b, cifra - 1) * cifra;
    }
    cout << endl;
    
    // Prueba el comportamiento de cifraMasSignificativa(n, 8) para los siguientes valores de n:
    // 0, 1, 66, 514, 4098, 32770, 262145, 2097154.
    b = 8;
    escribirBase(b);
    
    probarCifraMasSignificativa(0, b, 0);
    probarCifraMasSignificativa(1, b, 1);
    
    n = 66;
    while (n < 16777218) {
    	int cifra = 1;
        probarCifraMasSignificativa(n, 8, cifra);
        n = (n - 2) * b + 2;
    }
    cout << endl;
    
    // Prueba el comportamiento de cifraMasSignificativa(n, 2) para los siguientes valores de n:
    // 0, 1, 4, 8, 16, 32, ... , 1024
    b = 2;
    escribirBase(b);
    
    probarCifraMasSignificativa(0, b, 0);
    probarCifraMasSignificativa(1, b, 1);
    
    n = 4;
    while (n < 2048) {
		int cifra = 1;
        probarCifraMasSignificativa(n, b, cifra);   
        n *= b;
    }
    cout << endl;
}


// Pre:  <n> es el número natural y <b> está comprendido entre 2 y 10 y <laSuma> es
//       el valor de las cifras de <n> cuando se escribe en base <b>
// Post: Informa si el valor devuelto al ejecutar sumaCifras(n, b) coincide
//       con el de <laSuma>, cuando <n> se escribe en base <b>
void probarSumaCifras(const int n, const int b, const int laSuma) {
	int r = sumaCifras(n, b);
	if(r == laSuma) {
		cout << green << "Ok." << reset << " sumaCifras(" << n << ", " << b << ") = "
			 << r << endl;
	}
	else {
		cout << red << "Mal." << reset << " sumaCifras(" << n << ", " << b << ") = "
			 << r << " pero debería ser " << laSuma << endl;
	}
}


// Prueba el comportamiento de sumaCifras(n,b) para diferentes números naturales
// en las bases de numeración 2, 8 y 10
void probarSumaCifras() {
	cout << "Pruebas del comportamiento de la función sumaCifras(n, b):" << endl << endl;	

	// Prueba el comportamiento de sumaCifras(n, 10) para los siguientes valores de n:
    // 0, 1, 8, 9, 99, 999, ... , 99999, y 999999.
    unsigned b = 10;
    escribirBase(b);
    
    probarSumaCifras(0, b, 0);
    probarSumaCifras(1, b, 1);
    
    unsigned n = 10;
    unsigned suma = 9;
    while (n < 100000000) {
    	probarSumaCifras(n - 1, b, suma);
        n *= 10;
        suma += 9;
    }
    cout << endl;
    
    // Prueba el comportamiento de sumaCifras(n, 8) para los siguientes valores de n:
    // 0, 1, 8, 9, 99, 999, ... , 99999, y 999999.
    b = 8;
    escribirBase(b);
    
    n = 66;
    suma = 3;
    while (n < 16777218) {
        probarSumaCifras(n, b, suma);
        n = (n - 2) * b + 2;
    }
    cout << endl;
    
    // Prueba el comportamiento de sumaCifras(n,2) para los siguientes valores de n:
    // 0, 1, 3, 5, 9, 17, 33, 65, 128, 257, 513, 1025, 2049, 4097, 8193.
    b = 2;
    escribirBase(b);
    
    probarSumaCifras(0, 2, 0);
    probarSumaCifras(1, 2, 1);
    
    n = 2;
    suma = 2;
    while (n < 10000) {
        probarSumaCifras(n + 1, b, suma);
        n *= b;
    }
    cout << endl;
}


// Ejecuta una secuencia de pruebas de las funciones definidas
// en el módulo cálculos
int main() {
    // Pruebas del comportamiento de numCifras(n,b)
    probarNumCifras ();
    // Pruebas del comportamiento de cifra(n,i,b)
    probarCifra();
    // Pruebas del comportamiento de cifraMayor(n,b)
    probarCifraMayor();
    // Pruebas del comportamiento de cifraMasSignificativa(n,b)
    probarCifraMasSignificativa();
    // Pruebas del comportamiento de sumaCifras(n,b)
    probarSumaCifras();
    
    // Fin del programa de pruebas
    return 0;
}

