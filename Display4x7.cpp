/*
  Display4x7.cpp - Biblioteca para una pantalla de leds de 4x7 segmentos serie
  @author	Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version	1.2
*/

#include "Arduino.h"
#include "Display4x7.h"

/*
	Constructor para un objeto de la clase Display4x7
*/
Display4x7::Display4x7 (void) {
	// Resetear pantalla
	Serial.print("v");

	// Desactivar separador
	Serial.write(byte(119));    // Desactivar seperador
	Serial.write(byte(0));      // Desactivar seperador
	
	// Brillo al maximo
	Serial.write(byte(122));	// Valor para fijar el brillo
	Serial.write(byte(0));		// Fijar el nuevo brillo
	
}

/*
	Resetea el display poniendo el brillo al maximo y borrando tanto los caracteres
	mostrados como los separadores que hubiera activados
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.1
*/
void Display4x7::resetear (void) {
  Serial.print("v");    // rested led screen
  Serial.write(byte(122));    // Brillo al maximo
  Serial.write(byte(0));      // Brillo al maximo
  Serial.print("xxxx");
  
  // Desactivar separador
  Serial.write(byte(119));    // Desactivar seperador
  Serial.write(byte(0));      // Desactivar seperador
}

/*
	Ajusta el brillo del display al valor indicado como porcentaje
	0 = apagada
	100 = brillo maximo
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.1
*/
void Display4x7::ajustarBrillo (int valor) {
  	if (valor >= 0 && valor <= 100) {
		int nuevoBrillo = 254 - (int)(valor*2.54);	// Valor entre 0 y 255
		Serial.write(byte(122));					// Valor para fijar el brillo
		Serial.write(byte(nuevoBrillo));			// Fijar el nuevo brillo
	}
}

/*
	Muestra la cadena de hasta 4 caracteres en el display
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
void Display4x7::mostrar (String texto) {
	if (texto.length() <= 4) {
		if (texto.length() == 0)
			Display4x7::borrar();
		else {
			if (texto.length() == 1)
				Serial.print("xxx");
			else if (texto.length() == 2)
				Serial.print("xx");
			else if (texto.length() == 3)
				Serial.print("x");
				
			Serial.print(texto);
		}
	} else {
		Serial.print(texto[3]);
		Serial.print(texto[2]);
		Serial.print(texto[1]);
		Serial.print(texto[0]);
	}
}

/*
	Borra el contenido de la pantalla
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
void Display4x7::borrar (void) {
	Serial.print("xxxx");
}

/*
	Desliza de izquierda a derecha por el display el caracter pasado
	como argumento con la duracion total indicada como argumento
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
 */
void Display4x7::deslizarCaracterIzqDer (char caracter, int duracion) {
	// Restear el display
	Serial.print("v");

	/*
		C _ _ _
	*/
	Serial.print(caracter);
	Serial.print("xxx");
	delay((int)(duracion/5));

	/*
		_ C _ _
	*/
	Serial.print("x");
	Serial.print(caracter);
	Serial.print("xx");
	delay((int)(duracion/5));

	/*
		_ _ C _
	*/
	Serial.print("xx");
	Serial.print(caracter);
	Serial.print("x");
	delay((int)(duracion/5));

	/*
		_ _ _ C
	*/
	Serial.print("xxx");
	Serial.print(caracter);
	delay((int)(duracion/5));

	/*
		_ _ _ _
	*/
	Serial.print("xxxx");
	delay((int)(duracion/5));
}

/*
	Desliza de derecha a izquierda por el display el caracter pasado
	como argumento con la duracion total indicada como argumento
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
 */
void Display4x7::deslizarCaracterDerIzq (char caracter, int duracion) {
	// Restear el display
	Serial.print("v");

	/*
		_ _ _ C
	*/
	Serial.print("xxx");
	Serial.print(caracter);
	delay((int)(duracion/5));

	/*
		_ _ C _
	*/
	Serial.print("xx");
	Serial.print(caracter);
	Serial.print("x");
	delay((int)(duracion/5));

	/*
		_ C _ _
	*/
	Serial.print("x");
	Serial.print(caracter);
	Serial.print("xx");
	delay((int)(duracion/5));

	/*
		C _ _ _
	*/
	Serial.print(caracter);
	Serial.print("xxx");
	delay((int)(duracion/5));

	/*
		_ _ _ _
	*/
	Serial.print("xxxx");
	delay((int)(duracion/5));
}

/*
	Desliza dentro del display una palabra de cuatro caracteres
	desde el lado izquierdo al derecho
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.2
*/
void Display4x7::deslizarPalabraDentroIzqDer (String palabra, int duracion) {
	if (palabra.length() != 4)
		return;
	
	// Resetear el display
	Serial.print("v");
	
	char caracter0 = palabra[0];
	char caracter1 = palabra[1];
	char caracter2 = palabra[2];
	char caracter3 = palabra[3];
	
	/*
		3 _ _ _
	*/
	Serial.print(caracter3);
	Serial.print("xxx");
	delay((int)(duracion/4));
	
	/*
		2 3 _ _
	*/
	Serial.print(caracter2);
	Serial.print(caracter3);
	Serial.print("xx");
	delay((int)(duracion/4));
	
	/*
		1 2 3 _
	*/
	Serial.print(caracter1);
	Serial.print(caracter2);
	Serial.print(caracter3);
	Serial.print("x");
	delay((int)(duracion/4));
	
	/*
		0 1 2 3
	*/
	Serial.print(caracter0);
	Serial.print(caracter1);
	Serial.print(caracter2);
	Serial.print(caracter3);
}

/*
	Desliza dentro del display una palabra de cuatro caracteres
	desde el lado derecho al izquierdo
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.2
*/
void Display4x7::deslizarPalabraDentroDerIzq (String palabra, int duracion) {
	if (palabra.length() != 4)
		return;
	
	// Resetear el display
	Serial.print("v");
	
	char caracter0 = palabra[0];
	char caracter1 = palabra[1];
	char caracter2 = palabra[2];
	char caracter3 = palabra[3];
	
	/*
		_ _ _ 0
	*/
	Serial.print("xxx");
	Serial.print(caracter0);
	delay((int)(duracion/4));
	
	/*
		_ _ 0 1
	*/
	Serial.print("xx");
	Serial.print(caracter0);
	Serial.print(caracter1);
	delay((int)(duracion/4));
	
	/*
		_ 0 1 2
	*/
	Serial.print("x");
	Serial.print(caracter0);
	Serial.print(caracter1);
	Serial.print(caracter2);
	delay((int)(duracion/4));
	
	/*
		0 1 2 3
	*/
	Serial.print(caracter0);
	Serial.print(caracter1);
	Serial.print(caracter2);
	Serial.print(caracter3);
}

/*
	Desliza fuera del display una palabra de cuatro caracteres
	desde el lado izquierdo al derecho
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.2
*/
void Display4x7::deslizarPalabraFueraIzqDer (String palabra, int duracion) {
	if (palabra.length() != 4)
		return;
	
	// Resetear el display
	Serial.print("v");
	
	char caracter0 = palabra[0];
	char caracter1 = palabra[1];
	char caracter2 = palabra[2];
	char caracter3 = palabra[3];
	
	/*
		_ 0 1 2
	*/
	Serial.print("x");
	Serial.print(caracter0);
	Serial.print(caracter1);
	Serial.print(caracter2);
	delay((int)(duracion/4));
	
	/*
		_ _ 0 1
	*/
	Serial.print("xx");
	Serial.print(caracter0);
	Serial.print(caracter1);
	delay((int)(duracion/4));
	
	/*
		_ _ _ 0
	*/
	Serial.print("xxx");
	Serial.print(caracter0);
	delay((int)(duracion/4));
	
	/*
		_ _ _ _
	*/
	Serial.print("xxxx");
}

/*
	Desliza fuera del display una palabra de cuatro caracteres
	desde el lado derecho al izquierdo
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.2
*/
void Display4x7::deslizarPalabraFueraDerIzq (String palabra, int duracion) {
	if (palabra.length() != 4)
		return;
	
	// Resetear el display
	Serial.print("v");
	
	char caracter0 = palabra[0];
	char caracter1 = palabra[1];
	char caracter2 = palabra[2];
	char caracter3 = palabra[3];
	
	/*
		1 2 3 _
	*/
	Serial.print(caracter1);
	Serial.print(caracter2);
	Serial.print(caracter3);
	Serial.print("x");
	delay((int)(duracion/4));
	
	/*
		2 3 _ _
	*/
	Serial.print(caracter2);
	Serial.print(caracter3);
	Serial.print("xx");
	delay((int)(duracion/4));
	
	/*
		3 _ _ _
	*/
	Serial.print(caracter3);
	Serial.print("xxx");
	delay((int)(duracion/4));
	
	/*
		_ _ _ _
	*/
	Serial.print("xxxx");
}

/*
	Rellena el display con una palabra de 4 caracteres
	desplazando caracter a caracter de izquierda a derecha
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
 */
void Display4x7::formarPalabraIzqDer (String palabra) {
	if (palabra.length() != 4)
		return;
		
	// Restear el display
	Serial.print("v");

	char caracter0 = palabra[0];
	char caracter1 = palabra[1];
	char caracter2 = palabra[2];
	char caracter3 = palabra[3];

	/*
		3 _ _ _
	*/
	Serial.print(caracter3);
	Serial.print("xxx");
	delay(200);

	/*
		_ 3 _ _
	*/
	Serial.print("x");
	Serial.print(caracter3);
	Serial.print("xx");
	delay(200);

	/*
		_ _ 3 _
	*/
	Serial.print("xx");
	Serial.print(caracter3);
	Serial.print("x");
	delay(200);

	/*
		_ _ _ 3
	*/
	Serial.print("xxx");
	Serial.print(caracter3);
	delay(200);

	/*
		2 _ _ 3
	*/
	Serial.print(caracter2);
	Serial.print("xx");
	Serial.print(caracter3);
	delay(200);

	/*
		_ 2 _ 3
	*/
	Serial.print("x");
	Serial.print(caracter2);
	Serial.print("x");
	Serial.print(caracter3);
	delay(200);

	/*
		_ _ 2 3
	*/
	Serial.print("xx");
	Serial.print(caracter2);
	Serial.print(caracter3);
	delay(200);

	/*
		1 _ 2 3
	*/
	Serial.print(caracter1);
	Serial.print("x");
	Serial.print(caracter2);
	Serial.print(caracter3);
	delay(200);

	/*
		_ 1 2 3
	*/
	Serial.print("x");
	Serial.print(caracter1);
	Serial.print(caracter2);
	Serial.print(caracter3);
	delay(200);

	/*
		0 1 2 3
	*/
	Serial.print(caracter0);
	Serial.print(caracter1);
	Serial.print(caracter2);
	Serial.print(caracter3);
        delay(200);
}


/*
	Rellena el display con una palabra de 4 caracteres
	desplazando caracter a caracter de derecha a izquierda
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/

void Display4x7::formarPalabraDerIzq (String palabra) {
        //if (palabra.length() != 4)
		//return;

	// Restear el display
	Serial.print("v");

	char caracter0 = palabra[0];
	char caracter1 = palabra[1];
	char caracter2 = palabra[2];
	char caracter3 = palabra[3];

	/*
		_ _ _ 0
	*/
	Serial.print("xxx");
	Serial.print(caracter0);
	delay(200);

	/*
		_ _ 0 _
	*/
	Serial.print("xx");
	Serial.print(caracter0);
	Serial.print("x");
	delay(200);

	/*
		_ 0 _ _
	*/
	Serial.print("x");
	Serial.print(caracter0);
	Serial.print("xx");
	delay(200);

	/*
		0 _ _ _
	*/
	Serial.print(caracter0);
	Serial.print("xxx");
	delay(200);

	/*
		0 _ _ 1
	*/
	Serial.print(caracter0);
	Serial.print("xx");
	Serial.print(caracter1);
	delay(200);

	/*
		0 _ 1 _
	*/
	Serial.print(caracter0);  
	Serial.print("x");
	Serial.print(caracter1);
	Serial.print("x");
	delay(200);

	/*
		0 1 _ _
	*/
	Serial.print(caracter0);
	Serial.print(caracter1);
	Serial.print("xx");
	delay(200);

	/*
		0 1 _ 2
	*/
	Serial.print(caracter0);
	Serial.print(caracter1);
	Serial.print("x");
	Serial.print(caracter2);
	delay(200);

	/*
		0 1 2 _
	*/
	Serial.print(caracter0);
	Serial.print(caracter1);
	Serial.print(caracter2);
	Serial.print("x");
	delay(200);

	/*
		0 1 2 3
	*/
	Serial.print(palabra);
        delay(200);
}
