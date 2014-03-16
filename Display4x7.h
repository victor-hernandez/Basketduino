/*
  Display4x7.h - Biblioteca para una pantalla de leds de 4x7 segmentos serie
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.2
*/
#ifndef Display4x7_h
#define Display4x7_h

#include "Arduino.h"

class Display4x7 {
  public:
	Display4x7 (void);
	void resetear (void);
	void ajustarBrillo (int valor);
	void mostrar (String texto);
	void borrar (void);
	void deslizarCaracterIzqDer (char caracter, int duracion);
	void deslizarCaracterDerIzq (char caracter, int duracion);
	void deslizarPalabraDentroIzqDer (String palabra, int duracion);
	void deslizarPalabraDentroDerIzq (String palabra, int duracion);
	void deslizarPalabraFueraIzqDer (String palabra, int duracion);
	void deslizarPalabraFueraDerIzq (String palabra, int duracion);
	void formarPalabraIzqDer (String palabra);
	void formarPalabraDerIzq (String palabra);
};

#endif

