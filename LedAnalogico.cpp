/*
  LedAnalogico.cpp - Biblioteca para controlar la luminosidad de un led conectado a un
  puerto con salida analogica
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.0
*/
#include "Arduino.h"
#include "LedAnalogico.h"

/*
	Constructor para un objeto de la clase LedAnalogico, se usara HIGH para encender el
	led y LOW para apagarlo por defecto
*/
LedAnalogico::LedAnalogico (int pin) {
	_pin = pin;
        _positivo = true;
        pinMode(pin, OUTPUT);
}

/*
	Constructor para un objeto de la clase LedAnalogico, se usara HIGH para encender el
	led y LOW para apagarlo si "positivo" vale true, y al contrario si "positivo" vale
	false
*/
LedAnalogico::LedAnalogico (int pin, boolean positivo) {
	_pin = pin;
        _positivo = positivo;
        pinMode(pin, OUTPUT);
}

/*
	Enciende el led con la intensidad indicada como parametro, siendo 255 el valor para
	la maxima luminosidad y 0 para la minima. Si el valor pasado como parametro esta
	fuera del rango se usara 255 si el valor del parametro es es mayor que este 255 y 0 si
	el valor del parametro es menor que 0
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
void LedAnalogico::encender (int intensidad) {
  if (_positivo) {
    if (intensidad >= 255) {
      analogWrite(_pin, 255);
    }
    else if (intensidad <= 0) {
      analogWrite(_pin, 0);
    }
    else {
      analogWrite(_pin, intensidad);
    }
  }
  else {
    if (intensidad >= 255) {
      analogWrite(_pin, 0);
    }
    else if (intensidad <= 0) {
      analogWrite(_pin, 255);
    }
    else {
      analogWrite(_pin, 255 - intensidad);
    }
  }
}

/*
	Enciende el led con intensidad maxima
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.1
*/
void LedAnalogico::encender () {
	LedAnalogico::encender(255);
}

/*
	Apaga el led poniendole luminosidad 0
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
void LedAnalogico::apagar () {
  LedAnalogico::encender(0);
}
