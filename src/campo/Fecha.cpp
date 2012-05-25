/*
 * Fecha.cpp
 *
 *  Created on: May 23, 2012
 *      Author: matias_2
 */

#include "sstream"
#include "Fecha.h"

Fecha::Fecha() {

}

Fecha::Fecha(int dia, int mes, int anio) {
	this->setFecha(dia, mes, anio);
}

Fecha::~Fecha() {

}

bool Fecha::validarFecha(int fecha) {
//	Ejemplo valido de fecha = 20120523
	int dia = fecha % 100;
	int mes = fecha % 10000 / 100;
	int anio = fecha / 10000;

//	valida año con cuatro cifras.
	if (fecha / 100000000 != 0) {
		return false;
	}

//	validas mes y dia del mes
	switch (mes) {
		case 02:
			if (anio % 4 == 0) {
				//año bisiesto
				if (dia < 1 || dia > 29) {
					return false;
				}
			} else {
				//año comun no bisiesto
				if (dia < 1 || dia > 28) {
					return false;
				}
			}
		break;

		case 4:
		case 6:
		case 9:
		case 11:
			if (dia < 1 || dia > 30) {
				return false;
			}
			break;

		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (dia < 1 || dia > 31) {
				return false;
			}
			break;
		default:
			return false;
		break;
	}

	return true;

}

int Fecha::getFechaInt() {
	return this->fecha;
}

string Fecha::getFechaString() {
	int dia = this->fecha % 100;
	int mes = this->fecha % 10000 / 100;
	int anio = this->fecha / 10000;
	stringstream s;
	s << dia << "/" << mes << "/" << anio;
	return s.str();
}

void Fecha::setFecha(int dia, int mes, int anio) {
	int nuevaFecha = dia + mes*100 + anio*10000;

	if (this->validarFecha(nuevaFecha)) {
		this->fecha =  nuevaFecha;
	} else {
		this->fecha = 20120101;
	}
}

ResultadoComparacion Fecha::comparar(Fecha* otraFecha) {

	int dia = this->fecha % 100;
	int mes = this->fecha % 10000 / 100;
	int anio = this->fecha / 10000;

	int otroDia = otraFecha->getFechaInt() % 100;
	int otroMes = otraFecha->getFechaInt() % 10000 / 100;
	int otroAnio = otraFecha->getFechaInt() / 10000;

	if (anio > otroAnio) {
		return MAYOR;
	} else if (anio < otroAnio) {
		return MENOR;
	} else if (mes > otroMes) {
		return MAYOR;
	} else if(mes < otroMes) {
		return MENOR;
	} else if (dia > otroDia) {
		return MAYOR;
	} else if (dia < otroDia) {
		return MENOR;
	} else {
		return IGUAL;
	}
}
