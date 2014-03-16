/*
  PushButtonRedRing.cpp - Biblioteca para controlar un boton del tipo push button con
  un anillo iluminado de color rojo
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.0
*/
#include "Arduino.h"
#include "PushButtonRedRing.h"

/*
	Constructor para un objeto de la clase PushButtonRedRing para la cual no se quiere
	controlar el led no permitiendose encenderlo ni apagarlo
*/
PushButtonRedRing::PushButtonRedRing (int salida) {
	_salida = salida;
	_tieneLed = false;
}

/*
	Constructor para un objeto de la clase PushButtonRedRing para la cual se quiere
	controlar el led permitiendose encenderlo y apagarlo
*/
PushButtonRedRing::PushButtonRedRing (int led, int salida) {
	_salida = salida;
	_led = led;
	pinMode(_led, OUTPUT);
	_tieneLed = true;
}

/*
	Se encenderá el led del boton en el caso de que se permita la accion
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
void PushButtonRedRing::encender () {
	if (_tieneLed)
		digitalWrite(_led, LOW);
}

/*
	Se apagará el led del boton en el caso de que se permita la accion
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
void PushButtonRedRing::apagar () {
	if (_tieneLed)
		digitalWrite(_led, HIGH);
}

/*
	Devuelve true si el pulsador esta presionado y false en caso contrario
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
bool PushButtonRedRing::presionado () {
	return (digitalRead(_salida) == HIGH);
}
