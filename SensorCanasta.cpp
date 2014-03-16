/*
  SensorCanasta.cpp - Biblioteca para controlar un sensor de la canasta
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.0
*/
#include "Arduino.h"
#include "SensorCanasta.h"

/*
	Constructor para un objeto de la clase Pulsador
*/
SensorCanasta::SensorCanasta (int pin) {
	_pin = pin;
}

/*
	Devuelve true si el pulsador esta presionado y false en caso contrario
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
bool SensorCanasta::presionado () {
	return (analogRead(_pin) == 1023);
}
