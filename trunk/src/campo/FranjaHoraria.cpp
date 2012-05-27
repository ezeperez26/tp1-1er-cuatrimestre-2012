/*
 * Implementacion de la clase FranjaHoraria, que hereda de Campo y forma una de las dimensiones
 * de Clave
 *
 *  Created on: 21/05/2012
 *      Author: ezequiel
 */

#include "FranjaHoraria.h"
#include "Campo.h"


FranjaHoraria::FranjaHoraria() {
	this->fecha = new Fecha();
	this->horario = new Horario();
}

FranjaHoraria::FranjaHoraria(Fecha* fecha, Horario* horario) {
	this->fecha = fecha;
	this->horario = horario;
}

FranjaHoraria::FranjaHoraria(Campo* campo){
	// TODO Implementar constructor copia
}

FranjaHoraria::~FranjaHoraria() {
	delete this->fecha;
	delete this->horario;
}

Fecha* FranjaHoraria::getFecha() {
	return this->fecha;
}

void FranjaHoraria::setFecha(Fecha* fecha) {
	if (this->fecha != NULL) {
		delete this->fecha;
	}
	this->fecha = fecha;
}

Horario* FranjaHoraria::getHorario() {
	return this->horario;
}

void FranjaHoraria::setHorario(Horario* horario) {
	if (this->horario != NULL) {
		delete this->horario;
	}
	this->horario = horario;
}

ResultadoComparacion FranjaHoraria::comparar(Campo* otroCampo){

	FranjaHoraria* otraFranjaHoraria = dynamic_cast<FranjaHoraria*>(otroCampo);

	if (!otraFranjaHoraria) {
		return COMPARACION_NO_VALIDA;
	}

	if (this->fecha->comparar(otraFranjaHoraria->getFecha()) == MAYOR) {
		return MAYOR;
	} else if (this->fecha->comparar(otraFranjaHoraria->getFecha()) == MENOR) {
		return MENOR;
	} else if (this->horario->comparar(otraFranjaHoraria->getHorario()) == MAYOR) {
		return MAYOR;
	} else if (this->horario->comparar(otraFranjaHoraria->getHorario()) == MENOR) {
		return MENOR;
	} else {
	return IGUAL;
	}
}