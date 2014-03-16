/*
  SensorCanasta.h - Biblioteca para controlar un pulsador
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.0
*/
#ifndef SensorCanasta_h
#define SensorCanasta_h

#include "Arduino.h"

class SensorCanasta {
	public:
		SensorCanasta (int pin);
		bool presionado ();

	private:
		int _pin;
};

#endif
