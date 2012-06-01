/*
 * Falla_test.cpp
 *
 *  Created on: May 21, 2012
 *      Author: matias_2
 */

#include "iostream"
#include "../src/campo/CampoCadena.h"
#include "../src/campo/Formacion.h"
#include "../src/campo/Accidente.h"
#include "../src/campo/Linea.h"
#include "../src/campo/Falla.h"
#include "../src/Byte.h"

void CampoCadenaTest() {
	std::cout << "Prueba Unitaria: Clase CampoCadena." << endl;

	/* FIXME Probar constructor copia de cada clase heredera de clase CampoCadena
	 *
	 */

	CampoCadena* campoCadena1 = new Falla("No cierran puertas.Cierra 50%.");
	Campo* campoCadena2 = new Falla ("Cierra 50%.");

	if (campoCadena1->comparar(campoCadena2) == MAYOR) {
		std::cout << "Ok.....comparacion mayor" << endl;
	} else {
		std::cout << "Fail...comparacion mayor" << endl;
	}

	if (campoCadena2->comparar(campoCadena1) == MENOR) {
		std::cout << "Ok.....comparacion menor" << endl;
	} else {
		std::cout << "Fail...comparacion menor" << endl;
	}

	delete campoCadena2;
	campoCadena2 = NULL;

	if (campoCadena1->comparar(campoCadena2) == MAYOR) {
		std::cout << "Ok.....comparacion mayor con null" << endl;
	} else {
		std::cout << "Fail...comparacion mayor con null" << endl;
	}

	Accidente* campoCadena3 = new Accidente("Incendio.");
	Accidente* campoCadena4 = new Accidente("Incendio.");

	if (campoCadena3->comparar(campoCadena4) == IGUAL) {
		std::cout << "Ok.....comparacion igual" << endl;
	} else {
		std::cout << "Fail...comparacion igual" << endl;
	}

	Formacion* otraFormacion = new Formacion(0);
	CampoCadena* campoCadena5 = new Linea("Sarmiento");

	if (campoCadena5->comparar(otraFormacion) == COMPARACION_NO_VALIDA) {
		std::cout << "Ok.....comparacion no valida" << endl;
	} else {
		std::cout << "Fail...comparacion no valida" << endl;
	}

	cout << "inicializarConRegistro" << endl;
	// seteo un registro de bytes que la clase linea deberia poder decodificar
	string unaLinea = "Sarmiento";
	int tamLinea = unaLinea.size();
	Byte * regTamDescripcion = new Byte[sizeof(int)];
	// guardo en bytes el tam del string
	*regTamDescripcion = tamLinea;
	Byte * regDescripcion = new Byte[tamLinea];
	int i;
	for (i=0; i<tamLinea; i++) {
		regDescripcion[i] = unaLinea[i];
	}
	Byte * regFormacion;
	obtenerSuma(&regFormacion, regTamDescripcion, sizeof(int), regDescripcion, tamLinea);
	// creo una linea vacia
	Linea * linea = new Linea();
	linea->inicializarConRegistro(regFormacion);
	string otraLinea = linea->getDescripcion();
	if (unaLinea == otraLinea) {
		cout << "ok...inicializarConRegistro" << endl;
	}
	else {
		cout << "fallo...inicializarConRegistro" << " devolvio: " << otraLinea << " en vez de: " << unaLinea << endl;
	}

	delete campoCadena1;
	delete campoCadena2;
	delete campoCadena3;
	delete campoCadena4;
	delete campoCadena5;
	delete otraFormacion;

	cout << endl;
}
