/*
  Pulsador.h - Biblioteca para controlar un pulsador
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.0
*/
#ifndef Pulsador_h
#define Pulsador_h

#include "Arduino.h"

class Pulsador {
	public:
		Pulsador (int salida);
		bool presionado ();

	private:
		int _salida;
};

#endif