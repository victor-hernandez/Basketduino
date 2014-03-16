/*
  LedAnalogico.h - Biblioteca para controlar la luminosidad de un led conectado a un
  puerto con salida analogica
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.1
*/
#ifndef LedAnalogico_h
#define LedAnalogico_h

#include "Arduino.h"

class LedAnalogico {
	public:
		LedAnalogico (int pin);
                LedAnalogico (int pin, boolean positivo);
                void encender (int intensidad);
                void encender ();
                void apagar ();

	private:
		int _pin;
                boolean _positivo;
};

#endif
