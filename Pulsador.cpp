/*
  Pulsador.cpp - Biblioteca para controlar un pulsador
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.0
*/
#include "Arduino.h"
#include "Pulsador.h"

/*
	Constructor para un objeto de la clase Pulsador
*/
Pulsador::Pulsador (int salida) {
	_salida = salida;
}

/*
	Devuelve true si el pulsador esta presionado y false en caso contrario
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
bool Pulsador::presionado () {
	return (digitalRead(_salida) == HIGH);
}
