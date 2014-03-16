/*
  LedDigital.cpp - Biblioteca para controlar un led conectado a un puerto con salida digital
  
  @author	Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version	1.0
*/
#include "Arduino.h"
#include "LedDigital.h"

/*
	Constructor para un objeto de la clase LedAnalogico, se usara HIGH para encender el
	led y LOW para apagarlo por defecto
*/
LedDigital::LedDigital (int pin) {
	_pin = pin;
    _positivo = true;
    pinMode(pin, OUTPUT);
}

/*
	Constructor para un objeto de la clase LedDigital, se usara HIGH para encender el
	led y LOW para apagarlo si "positivo" vale true, y al contrario si "positivo" vale
	false
*/
LedDigital::LedDigital (int pin, boolean positivo) {
	_pin = pin;
    _positivo = positivo;
	pinMode(pin, OUTPUT);
}

/*
	Enciende el led
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
void LedDigital::encender () {
  if (_positivo) {
    digitalWrite(_pin, HIGH);
  }
  else {
    digitalWrite(_pin, LOW);
  }
}

/*
	Apaga el led
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
void LedDigital::apagar () {
  if (_positivo) {
    digitalWrite(_pin, LOW);
  }
  else {
    digitalWrite(_pin, HIGH);
  }
}
