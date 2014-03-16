/*
  Piezoelectrico.h - Biblioteca para tocar la melodia "Charge" con un piezoelectrico
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.0
*/
#ifndef Piezoelectrico_h
#define Piezoelectrico_h

#include "Arduino.h"

class Piezoelectrico {
	public:
		Piezoelectrico (int pin);
		void charge ();
	
	private:
		int _pin;
};

#endif