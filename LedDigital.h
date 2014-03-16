/*
  LedDigital.h - Biblioteca para controlar un led conectado a un puerto con salida digital
  
  @author	Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version	1.0
*/
#ifndef LedDigital_h
#define LedDigital_h

#include "Arduino.h"

class LedDigital {
	public:
		LedDigital (int pin);
    	LedDigital (int pin, boolean positivo);
        void encender ();
        void apagar ();

	private:
		int _pin;
        boolean _positivo;
};

#endif
