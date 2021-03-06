/*
 * Interface de la clase FranjaHoraria, que hereda de Campo y forma una de las dimensiones
 * de Clave
 *
 *  Created on: 21/05/2012
 *      Author: ezequiel
 */

#ifndef FRANJAHORARIA_H_
#define FRANJAHORARIA_H_

#include <iostream>
#include "../Byte.h"
#include "Campo.h"
#include "Fecha.h"
#include "Horario.h"

using namespace std;

class FranjaHoraria: public Campo {
private:
	Fecha* fecha;
	Horario* horario;

public:

	/*
	 * Constructor de la clase FranjaHoraria
	 */
	FranjaHoraria();

	/*
	 * Constructor copia de la clase FranjaHoraria
	 */
	FranjaHoraria(FranjaHoraria& franja);

	FranjaHoraria(Fecha* fecha, Horario* horario);

	/*
	 * Destructor de la clase FranjaHoraria
	 */
	virtual ~FranjaHoraria();

	Fecha* getFecha();
	void setFecha(Fecha* fecha);

	Horario* getHorario();
	void setHorario(Horario* horario);

	/*
	 * Metodo virtual que compara este campo con otro pasado por parámetro.
	 * Como estándar, debe devolver 0 si son iguales y distinto de 0 si son distintos.
	 * Se puede considerar devolver -1 si el campo es menor que el pasado por parámetro
	 * y 1 si el campo es mayor que el pasado por parámetro
	 */
	ResultadoComparacion comparar(Campo* otroCampo);

	/* Funcion que genera la cadena de bytes para almacenar la FranjaHoraria. Debe recibir por
	 * referencia un int que pueda almacenar el tamaño de la cadena, para su guardado
	 * posterior en el archivo.
	 */
	virtual Byte * obtenerRegistro (int *tam);

	virtual void inicializarConRegistro(Byte *);
};

#endif /* FRANJAHORARIA_H_ */
