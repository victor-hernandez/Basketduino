/*
  PushButtonRedRing.h - Biblioteca para controlar un boton del tipo push button con
  un anillo iluminado de color rojo
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.0
*/
#ifndef PushButtonRedRing_h
#define PushButtonRedRing_h

#include "Arduino.h"

class PushButtonRedRing {
	public:
		PushButtonRedRing (int salida);
		PushButtonRedRing (int led, int salida);
		void encender ();
		void apagar ();
		bool presionado ();

	private:
		int _led;
		int _salida;
		boolean _tieneLed;
};

#endif
