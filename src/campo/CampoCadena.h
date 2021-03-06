/*
 * CampoCadena.h
 *
 *  Created on: May 22, 2012
 *      Author: matias_2
 */

#ifndef CAMPOCADENA_H_
#define CAMPOCADENA_H_

#include "Campo.h"
#include "../Byte.h"

using namespace std;

class CampoCadena: public Campo {
private:
	string descripcion;

public:
	CampoCadena();
	CampoCadena(CampoCadena &campoCadena);
	CampoCadena(string descripcion);
	virtual ~CampoCadena();

	string getDescripcion();
	void setDescripcion(string descripcion);

	virtual ResultadoComparacion comparar(Campo* otroCampo) = 0;

	/* Funcion que genera la cadena de bytes para almacenar la Formacion.
	 * Los 4 primeros bytes almacenan la cantidad de bytes posteriores que debe
	 * deserializar posteriormente.
	 */
	virtual Byte * obtenerRegistro(int *tam);

	virtual void inicializarConRegistro(Byte *);
};

#endif /* CAMPOCADENA_H_ */
