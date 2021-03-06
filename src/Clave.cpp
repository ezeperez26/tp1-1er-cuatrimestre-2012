/*
 * Implementacion de la clase Clave
 *
 *  Created on: 12/05/2012
 *      Author: ezequiel
 */

#include "Clave.h"

/*
 * Constructor de la clase Clave, que inicializa todas sus dimensiones en NULL
 */
Clave::Clave() {
	this->listaCampos = new Campo*[this->cantDimensiones];
	for(int i=0; i < this->cantDimensiones; i++){
		this->listaCampos[i] = NULL;
	}
}

/*
 * Constructor de la clase Clave
 * Inicializa sus campos copiando los de la otra clave.
 */
Clave::Clave(Clave &otraClave){
	this->listaCampos = new Campo*[this->cantDimensiones];
	this->copiar(&otraClave);
}

/*
 * Constructor de la clase Clave, que inicializa los campos Linea y Formacion,
 * el resto de sus dimensiones en NULL
 */
Clave::Clave(string linea, int formacion) {
	Campo *unaLinea = new Linea(linea);
	Campo *unaFormacion = new Formacion(formacion);
	this->listaCampos = new Campo*[this->cantDimensiones];
	this->listaCampos[0] = unaLinea;
	this->listaCampos[1] = unaFormacion;
	for(int i=2; i < this->cantDimensiones; i++){
		this->listaCampos[i] = NULL;
	}
}

Clave::~Clave() {
	for(int i=0; i < this->cantDimensiones; i++){
		if (this->listaCampos[i] != NULL){
			delete this->listaCampos[i];
		}
	}
	delete this->listaCampos;
}

void Clave::setLinea(string linea){
	if (this->listaCampos[0] != NULL){
		delete this->listaCampos[0];
	}
	this->listaCampos[0] = new Linea(linea);
}

void Clave::setFormacion(int formacion){
	if (this->listaCampos[1] != NULL){
		delete this->listaCampos[1];
	}
	this->listaCampos[1] = new Formacion(formacion);
}

void Clave::setFranjaHoraria(FranjaHoraria *franja){
	this->listaCampos[2] = franja;
}

void Clave::setFalla(string falla){
	if (this->listaCampos[3] != NULL){
		delete this->listaCampos[3];
	}
	this->listaCampos[3] = new Falla(falla);
}

void Clave::setAccidente(string accidente){
	if (this->listaCampos[4] != NULL){
		delete this->listaCampos[4];
	}
	this->listaCampos[4] = new Accidente(accidente);
}

/*
 * Se obtiene el campo correspondiente a la dimension requerida, siendo:
 * 		0: Linea
 * 		1: Formacion
 * 		2: FranjaHoraria
 * 		3: Falla
 * 		4: Accidente
 * Si se pasa un valor diferente a los mencionados anteriormente, devuelve un puntero NULL
 */
Campo *Clave::getCampo(int dimension) const{
	Campo *unCampo = NULL;
	// Valido que la dimension sea mayor o igual que 0 y menor que la cantidad de dimensiones
	if ((0 <= dimension) && (dimension < this->cantDimensiones)){
		unCampo = this->listaCampos[dimension];
	}
	return unCampo;
}

/*
 * Funcion que evalúa si esta clave es igual a otra pasada por parámetro.
 * Compara todos los campos y evuelve 0 si son iguales, o un valor distinto de 0 si
 * no son iguales
 */
ResultadoComparacion Clave::comparar(const Clave *otraClave){
	// Si el puntero recibido es NULL, no se puede comparar
	if (otraClave == NULL){
		return COMPARACION_NO_VALIDA;
	}
	// Ahora se procede a comparar
	ResultadoComparacion resultado = IGUAL;
	int i = 0;
	while ((resultado == IGUAL) && (i < this->cantDimensiones)){
		Campo *unCampo = this->listaCampos[i]; // Copio el campo correspondiente a la dimension i
		Campo *otroCampo = otraClave->getCampo(i);
		// Si ambos campos son no nulos, los comparo
		if ((unCampo != NULL) && (otroCampo != NULL)){
			ResultadoComparacion tmp = unCampo->comparar(otroCampo);
			if (tmp != IGUAL){
				resultado = COMPARACION_NO_VALIDA;
			}
		} else {
			// Si ambos campos son nulos, se sigue cumpliendo la igualdad
			if ((unCampo == NULL) && (otroCampo == NULL)){
				resultado = IGUAL;
			} else {
				resultado = COMPARACION_NO_VALIDA;
			}
		}
		i++;	// Incremento el valor de i
	}
	return resultado;
}

/*
 * Funcion que evalúa solo la dimensión de esta clave con otra pasada por parámetro
 * Compara el campo correspondiente a la dimension que se quiere evaluar y
 * devuelve 0 si son iguales, -1 si el campo es menor que el pasado por parametro y
 * 1 si el campo es mayor.
 */
ResultadoComparacion Clave::comparar(Clave *otraClave, int dimension){
	ResultadoComparacion resultComparacion = this->listaCampos[dimension]->comparar(otraClave->listaCampos[dimension]);
	return resultComparacion;
}

ResultadoComparacion Clave::comparar(Campo* otroCampo) {
	ResultadoComparacion resultado = COMPARACION_NO_VALIDA;
	int i = 0;
	while ((resultado == COMPARACION_NO_VALIDA) && (i < this->cantDimensiones)){
		if (this->listaCampos[i] != NULL) {
			resultado = this->listaCampos[i]->comparar(otroCampo);
		}
		i++;
	}
	return resultado;
}

/*
 * Funcion que copia el contenido de la clave pasada por parametro a su clave.
 * Si el puntero pasado es NULL, no se copia nada.
 */
void Clave::copiar(const Clave *otraClave){
	if (otraClave != NULL){
		// Copio el campo Linea
		if (otraClave->getCampo(0) == NULL){
			this->listaCampos[0] = NULL;
		} else {
			// Verifico si es campo Linea con un casteo dinamico
			Linea* unaLinea = dynamic_cast<Linea*>(otraClave->listaCampos[0]);
			if (!unaLinea) {
				// Si el casteo fallo, establezco como null el puntero de Linea
				this->listaCampos[0] = NULL;
			} else {
				Linea* otraLinea = new Linea(unaLinea->getDescripcion());	// Creo el campo Linea
				this->listaCampos[0] = otraLinea;	// Almaceno el campo en la clave
			}
		}
		// Copio el campo Formacion
		if (otraClave->getCampo(1) == NULL){
			this->listaCampos[1] = NULL;
		} else {
			// Verifico si es campo Formacion con un casteo dinamico
			Formacion* unaFormacion = dynamic_cast<Formacion*>(otraClave->listaCampos[1]);
			if (!unaFormacion) {
				this->listaCampos[1] = NULL;
			} else {
				Formacion* otraFormacion = new Formacion(unaFormacion->getNumeroFormacion());	// Creo el campo Formacion
				this->listaCampos[1] = otraFormacion;	// Almaceno el campo de la clave
			}
		}
		// Copio el campo FranjaHoraria
		if (otraClave->getCampo(2) == NULL){
			this->listaCampos[2] = NULL;
		} else {
			// Verifico si es campo FranjaHoraria con un casteo dinamico
			FranjaHoraria* unaFranjaHoraria = dynamic_cast<FranjaHoraria*>(otraClave->listaCampos[2]);
			if (!unaFranjaHoraria) {
				this->listaCampos[2] = NULL;
			} else {
				FranjaHoraria *otraFranjaHoraria = new FranjaHoraria(unaFranjaHoraria->getFecha(), unaFranjaHoraria->getHorario());	// Creo el campo FranjaHoraria
				this->listaCampos[2] = otraFranjaHoraria;	// Almaceno el campo de la clave
			}
		}
		// Copio el campo Falla
		if (otraClave->getCampo(3) == NULL){
			this->listaCampos[3] = NULL;
		} else {
			// Verifico si es campo FranjaHoraria con un casteo dinamico
			Falla* unaFalla = dynamic_cast<Falla*>(otraClave->listaCampos[3]);
			if (!unaFalla) {
				this->listaCampos[3] = NULL;
			} else {
				Falla *otraFalla = new Falla(unaFalla->getDescripcion());	// Creo el campo Falla
				this->listaCampos[3] = otraFalla;	// Almaceno el campo de la clave
			}
		}
		// Copio el campo Accidente
		if (otraClave->getCampo(4) == NULL){
			this->listaCampos[4] = NULL;
		} else {
			// Verifico si es campo Accidente con un casteo dinamico
			Accidente* unAccidente = dynamic_cast<Accidente*>(otraClave->listaCampos[4]);
			if (!unAccidente) {
				this->listaCampos[4] = NULL;
			} else {
				Accidente *otroAccidente = new Accidente(unAccidente->getDescripcion());	// Creo el campo Accidente
				this->listaCampos[4] = otroAccidente;	// Almaceno el campo de la clave
			}
		}
	}
}

/* Funcion que genera la cadena de bytes para almacenar la clase. Debe recibir por
 * referencia un int que pueda almacenar el tamaño de la cadena, para su guardado
 * posterior en el archivo.
 */
Byte * Clave::obtenerRegistro (int *tam){
	// Inicializo el contador de bytes de la serializacion.
	int tamClave = 0;
	Byte *tmp = NULL;
	for (int i=0; i < this->cantDimensiones; i++){
		int tamCampo;
		Byte * regCampo;
		/* Analizo si el campo es nulo. si no lo es, serializo normalmente.
		 * Si el campo es nulo, genero 4 bytes con 0.
		 */
		if (this->listaCampos[i] != NULL){
			regCampo = this->listaCampos[i]->obtenerRegistro(&tamCampo);
		} else {
			// Si el campo es nulo, genero 4 bytes con 0
			tamCampo = sizeof(int);
			regCampo = new Byte[sizeof(int)];
			*regCampo = 0;
		}
		/* Si es la primer iteracion, no necesito concatenar con un campo previo,
		 * por lo que asigno los resultados a tamClave y tmp.
		 */
		if (i == 0){
			tmp = regCampo;
			tamClave = tamCampo;
		} else {
			Byte *temp;
			concatenar(&temp, tmp, tamClave, regCampo, tamCampo);
			tamClave += tamCampo;
			delete tmp; // Elimino temporal viejo
			tmp = temp; // asigno el nuevo
			// Luego de la concatenacion y antes de finalizar la iteracion, elimino regCampo.
			delete regCampo;
		}
	}
	//Luego de finalizado el for, debo serializar el tamaño de la clave
	Byte * size = new Byte[sizeof(int)];
	*size = tamClave;
	*tam = tamClave + sizeof(int); // tamaño total para devolver a la clase externa
	Byte * registro;
	concatenar(&registro, size, sizeof(int), tmp, tamClave);
	delete size;
	delete tmp;
	return registro;
}

void Clave::inicializarConRegistro(Byte * registro) {
	int inicio = 0;
	int tamReg;
	int tamRegCampo;
	Byte * regTamCampo;
	Byte * regCampo;
	int i;
	for (i=0; i<cantDimensiones; i++) {
		tamReg = sizeof(int);
		// obtengo el tamanio del registro del campo
		obtenerPorcion(registro, &regTamCampo, inicio, tamReg);
		tamRegCampo = *regTamCampo;
		inicio += tamReg;
		// el campo es nulo
		if (tamRegCampo == 0) {
			listaCampos[i] = NULL;
		}
		// el campo no es nulo lo instancio
		else {
			obtenerPorcion(registro, &regCampo, inicio, tamRegCampo);
			inicio += tamRegCampo;
			if (i==0) {
				Linea * linea = new Linea();
				linea->inicializarConRegistro(regCampo);
				listaCampos[i] = linea;
			}
			if (i==1) {
				Formacion * formacion = new Formacion();
				formacion->inicializarConRegistro(regCampo);
				listaCampos[i] = formacion;
			}
			if (i==2) {
				FranjaHoraria * franja = new FranjaHoraria();
				franja->inicializarConRegistro(regCampo);
				listaCampos[i] = franja;
			}
			if (i==3) {
				Falla * falla = new Falla();
				falla->inicializarConRegistro(regCampo);
				listaCampos[i] = falla;
			}
			if (i==4) {
				Accidente * accidente = new Accidente();
				accidente->inicializarConRegistro(regCampo);
				listaCampos[i] = accidente;
			}
		}
	}
}
