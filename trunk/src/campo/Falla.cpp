/*
 * Implementacion de la clase Falla, que hereda de Campo y forma una de las dimensiones
 * de Clave
 *
 *  Created on: 21/05/2012
 *      Author: ezequiel
 */

#include "Falla.h"

Falla::Falla() : CampoCadena() {

}

Falla::Falla(string tipoFalla) : CampoCadena(tipoFalla) {

}

Falla::Falla(Campo* campo){
	// TODO Implementar constructor copia
}

Falla::~Falla() {

}
