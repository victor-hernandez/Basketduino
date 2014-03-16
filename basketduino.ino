/************************************************************************************
						Bibliotecas de funciones y clases
************************************************************************************/
#include "FlexiTimer2.h"
#include "Metro.h"
#include "Display4x7.h"
#include "Piezoelectrico.h"
#include "Pulsador.h"
#include "PushButtonRedRing.h"
#include "LedAnalogico.h"
#include "LedDigital.h"
#include "SensorCanasta.h"


/************************************************************************************
							Pines de entrada y salida
************************************************************************************/
const int pinPiezoelectrico  = 8;

const int pinBotonAceptar    = 7;
const int pinBotonDerecho    = 2;
const int pinBotonIzquierdo  = 4;

const int pinSensorCanasta1  = A0;
const int pinSensorCanasta2  = A1;

const int pinLedRjug1  = 3;
const int pinLedAjug1  = 5;
const int pinLedVjug1  = 6;
const int pinLedBjug1  = 13;
const int pinLedRjug2  = 9;
const int pinLedAjug2  = 10;
const int pinLedVjug2  = 11;
const int pinLedBjug2  = 12;


/************************************************************************************
			Objetos para controlar los dispositivos del sistema
************************************************************************************/
Display4x7 pantalla;
	
Piezoelectrico bocina (pinPiezoelectrico);
	
Pulsador botonDerecho (pinBotonDerecho);
Pulsador botonIzquierdo (pinBotonIzquierdo);
PushButtonRedRing botonAceptar (pinBotonAceptar);
	
SensorCanasta canastaJugador1 (pinSensorCanasta1);
SensorCanasta canastaJugador2 (pinSensorCanasta2);

LedAnalogico ledRjug1 (pinLedRjug1, false);
LedAnalogico ledAjug1 (pinLedAjug1, false);
LedAnalogico ledVjug1 (pinLedVjug1, false);
LedDigital	 ledBjug1 (pinLedBjug1, false);
LedAnalogico ledRjug2 (pinLedRjug2, false);
LedAnalogico ledAjug2 (pinLedAjug2, false);
LedAnalogico ledVjug2 (pinLedVjug2, false);
LedDigital	 ledBjug2 (pinLedBjug2, false);


/************************************************************************************
			Variables globales necesarias para los juegos y menus
************************************************************************************/
int segundosRestantes;
int opcion = 1;
const int numeroDeOpciones = 4;

/************************************************************************************
										SETUP
************************************************************************************/
void setup () {
	Serial.begin(9600);		// Necesario para el Display4x7
  
	// Resetear la pantalla para poner el brillo al maximo, borrar su contenido y
	// desactivar todos los separadores
	pantalla.resetear();
  
	// Apagar todos los leds
	ledRjug1.apagar();
	ledAjug1.apagar();
	ledVjug1.apagar();
	ledBjug1.apagar();
	ledRjug2.apagar();
	ledAjug2.apagar();
	ledVjug2.apagar();
	ledBjug2.apagar();

	// Establecer el reloj para los juegos en los que sea necesario
	FlexiTimer2::set(500, tic);
	
	// Test inicial en el que se activaran los leds y la pantalla
	// para comprobar su que funcionan correctamente
	test();
}

/************************************************************************************
										LOOP
************************************************************************************/
void loop () {
  menu();
}


/************************************************************************************
									MENU PRINCIPAL
************************************************************************************/
void menu() {
  	String opcionActual = "OPC";
        opcionActual += opcion;
        pantalla.mostrar(opcionActual);
  
	// Si se pulsa el boton aceptar
	if (botonAceptar.presionado()) {
		tratarOpcion(opcion);
	}
	
	// Si se pulsa el boton derecho
	if (botonDerecho.presionado()) {
		String opcionAnterior = "OPC";
                opcionAnterior += opcion;
		
		// Incremetar variable opcion, si superamos el numero de opciones volver a 1
		opcion++;
		if (opcion > numeroDeOpciones) {
			opcion = 1;
		}
		
		String opcionActual = "OPC";
                opcionActual += opcion;
		
		// Actualizar la pantalla del dispositivo
		pantalla.deslizarPalabraFueraDerIzq(opcionAnterior, 500);
		pantalla.deslizarPalabraDentroDerIzq(opcionActual, 500);
	}
	
	// Si se pulsa el boton izquierdo
	if (botonIzquierdo.presionado()) {
		String opcionAnterior = "OPC";
                opcionAnterior += opcion;
		
		// Decrementar variable opcion, si llegamos a 0 volver a la opcion mas alta
		opcion--;
		if (opcion < 1) {
			opcion = numeroDeOpciones;
		}
		
		String opcionActual = "OPC";
                opcionActual += opcion;
		
		// Actualizar la pantalla del dispositivo
		pantalla.deslizarPalabraFueraIzqDer(opcionAnterior, 500);
		pantalla.deslizarPalabraDentroIzqDer(opcionActual, 500);
	}	
}

void tratarOpcion (int opcion) {
	switch(opcion) {
		case 1: juego1vs1();
				break;
		case 2: juego1vs1conBonus();
				break;
		case 3: juegoAsno();
				break;
		case 4: juego11();
				break;
		default:
				break;
	}
}


/************************************************************************************
									MODOS DE JUEGO
************************************************************************************/

/*
	Juego 1vs1: Partida jugador contra jugador durante 60 segundos, gana el jugador
	que haya anotado mas puntos al final de la partida
*/
void juego1vs1 () {
	// Marcadores para los jugadores
	int puntosJugador1 = 0;
	int puntosJugador2 = 0;
  
	boolean pulsadorCanasta1Pulsado = false;
	boolean pulsadorCanasta2Pulsado = false; 

	// Cuenta atras
    bocina.charge();

  	// Iniciar reloj
	segundosRestantes = 60;
	FlexiTimer2::start();

	// Jugar partida hasta llegar a cero
	while (segundosRestantes >= 0) {
		// Marcador, con los dos digitos de la izquierda para la puntuacion del jugador 1
		// y los dos digitos de la derecha para la puntuacion del jugador 2
		int marcador = puntosJugador1 * 100 + puntosJugador2;
    
		// Comprobar si ha anotado algun jugador
		if (canastaJugador1.presionado() && !pulsadorCanasta1Pulsado) {
			pulsadorCanasta1Pulsado = true;
      
			if (puntosJugador1 < 99) {
				puntosJugador1++;
			}
      
			delay(500);
		}
    
		if (canastaJugador2.presionado() && !pulsadorCanasta2Pulsado) {
			pulsadorCanasta2Pulsado = true;
      
			if (puntosJugador2 < 99) {
				puntosJugador2++;
			}
      
			delay(500);
		}
    
		if (!canastaJugador1.presionado()) {
			pulsadorCanasta1Pulsado = false;
		}
    
		if (!canastaJugador2.presionado()) {
			pulsadorCanasta2Pulsado = false;
		}

		// Mostrar el marcador o el tiempo restante
		// El tiempo restante se muestra cuando:
		//  - De 60 a 57
		//  - De 45 a 42
		//  - De 30 a 27
		//  - De 10 a 0
		// El resto del tiempo se muesta la puntuacion
		Serial.print("v");  // Restear la pantalla 4x7segmentos
		if ((segundosRestantes <= 60 && segundosRestantes >= 60) || (segundosRestantes <= 45 && segundosRestantes >= 42) || (segundosRestantes <= 30 && segundosRestantes >= 27) || (segundosRestantes <= 10)) {
			// Mostrar los segundos restantes
			// Desactivar separador
			Serial.write(byte(119));    // Descctivar seperador
			Serial.write(byte(0));      // Desactivar seperador
  
			if (segundosRestantes >= 10)
				Serial.print("x");
			else
				Serial.print("x0");

			Serial.print(segundosRestantes);
			Serial.print("x");
		}
		else {
			// Mostrar marcador
			Serial.write(byte(119));    // Activar seperador
			Serial.write(byte(16));     // Activar seperador
      
			if (marcador < 10)
				Serial.print("000");
			else if (marcador < 100)
				Serial.print("00");
			else if (marcador < 1000)
				Serial.print("0");
        
			Serial.print(marcador);
		}
	}
	FlexiTimer2::stop();
  
	// Desactivar separador
	Serial.write(byte(119));    // Desactivar seperador
	Serial.write(byte(0));      // Desactivar seperador

	// GAME OVER
	pantalla.formarPalabraDerIzq("GANE");
	delay(1000);
	pantalla.formarPalabraDerIzq("OUER");
	delay(2000);
 
	// Comprobar quien ha ganado
	mostrarGanador(puntosJugador1, puntosJugador2);
}


/*
	Juego 1vs1 con bonus: Partida jugador contra jugador durante 60 segundos, cuando un
	jugador anota varias canastas en un intervalo corto de tiempo consigue un bonus
	y sus canastas valen 2 o 3 puntos. Gana la partida el jugador que haya conseguido
	mas puntos al final de los 60 segundos
*/
void juego1vs1conBonus() {
	// Marcadores para los jugadores
	int puntosJugador1 = 0;
	int puntosJugador2 = 0;
	int bonusJugador1 = 0;
	int bonusJugador2 = 0;
	boolean pulsadorCanasta1Pulsado = false;
	boolean pulsadorCanasta2Pulsado = false; 

	// Cuenta atras
    bocina.charge();

	// Iniciar reloj
	segundosRestantes = 60;
	FlexiTimer2::start();
	Metro metronomo(100);

	// Jugar partida hasta llegar a cero
	while (segundosRestantes >= 0) {
    	// Marcador, con los dos digitos de la izquierda para la puntuacion del jugador 1
    	// y los dos digitos de la derecha para la puntuacion del jugador 2
    	int marcador = puntosJugador1 * 100 + puntosJugador2;
    
		// Comprobar si ha anotado algun jugador
    	if (canastaJugador1.presionado() && !pulsadorCanasta1Pulsado) {
			pulsadorCanasta1Pulsado = true;

			if (bonusJugador1 >= 300) {
				if (puntosJugador1 < 96)
					puntosJugador1+= 3;
				else if (puntosJugador1 >= 96)
					puntosJugador1 = 99;
			} else if (bonusJugador1 >= 200) {
				if (puntosJugador1 < 97)
					puntosJugador1 += 2;
				else if (puntosJugador1 >= 97)
          			puntosJugador1 = 99;
			} else {
				if (puntosJugador1 < 98)
					puntosJugador1 += 1;
				else if (puntosJugador1 >= 98)
					puntosJugador1 = 99;
		}
        
			bonusJugador1 += 100;
			delay(500);
		}
    
		if (canastaJugador2.presionado() && !pulsadorCanasta2Pulsado) {
			pulsadorCanasta2Pulsado = true;
      
			if (bonusJugador2 >= 300) {
				if (puntosJugador2 < 96)
					puntosJugador2+= 3;
				else if (puntosJugador2 >= 96)
					puntosJugador2 = 99;
			} else if (bonusJugador2 >= 200) {
				if (puntosJugador2 < 97)
					puntosJugador2 += 2;
				else if (puntosJugador2 >= 97)
					puntosJugador2 = 99;
			} else {
				if (puntosJugador2 < 98)
					puntosJugador2 += 1;
				else if (puntosJugador2 >= 98)
					puntosJugador2 = 99;
      		}
      
      		bonusJugador2 += 100;
			delay(500);
		}
    
		encenderLedsBonus(bonusJugador1, bonusJugador2);
    
		if (!canastaJugador1.presionado()) {
			pulsadorCanasta1Pulsado = false;
		}
    
		if (!canastaJugador2.presionado()) {
			pulsadorCanasta2Pulsado = false;
		}
    
		if (metronomo.check() == 1) {
			if (bonusJugador1 < 5)
				bonusJugador1 = 0;
			else
				bonusJugador1 -= 5;
        
			if (bonusJugador2 < 5)
				bonusJugador2 = 0;
			else  
				bonusJugador2 -= 5;
		}

		// Mostrar el marcador o el tiempo restante
		// El tiempo restante se muestra cuando:
		//  - De 60 a 57
		//  - De 45 a 42
		//  - De 30 a 27
		//  - De 10 a 0
		// El resto del tiempo se muesta la puntuacion
		Serial.print("v");  // Restear la pantalla 4x7segmentos
		if ((segundosRestantes <= 60 && segundosRestantes >= 60) || (segundosRestantes <= 45 && segundosRestantes >= 42) || (segundosRestantes <= 30 && segundosRestantes >= 27) || (segundosRestantes <= 10)) {
			// Mostrar los segundos restantes
			// Desactivar separador
			Serial.write(byte(119));    // Descctivar seperador
			Serial.write(byte(0));      // Desactivar seperador
  
			if (segundosRestantes >= 10)
				Serial.print("x");
			else
				Serial.print("x0");

			Serial.print(segundosRestantes);
			Serial.print("x");
		}
		else {
			// Mostrar marcador
			Serial.write(byte(119));    // Activar seperador
			Serial.write(byte(16));     // Activar seperador
      
			if (marcador < 10)
				Serial.print("000");
			else if (marcador < 100)
				Serial.print("00");
			else if (marcador < 1000)
				Serial.print("0");
        
		Serial.print(marcador);
		}
	}
 	FlexiTimer2::stop();
  
	// Desactivar separador
	Serial.write(byte(119));    // Desactivar seperador
	Serial.write(byte(0));      // Desactivar seperador

	// GAME OVER
	pantalla.formarPalabraDerIzq("GANE");
	delay(1000);
	pantalla.formarPalabraDerIzq("OUER");
	delay(2000);
 
	// Comprobar quien ha ganado
	mostrarGanador(puntosJugador1, puntosJugador2);
}

/*
	Juego del Asno
	Implementado como finita maquina de estados
	Estado 1 - Turno J1
		Mete canasta  -> Transitar al estado 3
		Falla canasta -> Transitar al estado 2
	Estado 2 - Turno J2
		Mete canasta  -> Transitar al estado 4
		Falla canasta -> Transitar al estado 1
	Estado 3 - Turno J2
		Mete canasta  -> Transitar al estado 1
		Falla canasta -> Transitar al estado 1 y sumar error al jugador 2
	Estado 4 - Turno J1
		Mete canasta  -> Transitar al estado 2
		Falla canasta -> Transitar al estado 2 y sumar error al jugador 1
*/
void juegoAsno() {
	int estadoActual = 1;
	int numErroresJ1 = 0;
	int numErroresJ2 = 0;
	
	// Cuenta atras
    
    bocina.charge();
    pantalla.resetear();
    mostrarLetras(numErroresJ1);
    ledBjug1.encender();
    ledBjug2.apagar();
	
	// Mientras que ningun jugador haya perdido seguir jugando
	while (numErroresJ1 < 4 && numErroresJ2 <4) {
		// Si se ha metido canasta
		if (canastaJugador1.presionado()) {
			switch (estadoActual) {
				case 1:
					estadoActual = 3;
					mostrarLetras(numErroresJ2);
					ledBjug2.encender();
					ledBjug1.apagar();
					break;
				case 2:
					estadoActual = 4;
					mostrarLetras(numErroresJ1);
					ledBjug1.encender();
					ledBjug2.apagar();
					break;
				case 3:
					estadoActual = 1;
					mostrarLetras(numErroresJ1);
					ledBjug1.encender();
					ledBjug2.apagar();
					break;
				case 4:
					estadoActual = 2;
					mostrarLetras(numErroresJ1);
					ledBjug2.encender();
					ledBjug1.apagar();
					break;
				default:
					break;
			}
                        delay(500);
		}
		// Se no se ha encestado
		if (botonAceptar.presionado()) {
			switch (estadoActual) {
				case 1:
					estadoActual = 2;
					mostrarLetras(numErroresJ2);
					ledBjug2.encender();
					ledBjug1.apagar();
					break;
				case 2:
					estadoActual = 1;
					mostrarLetras(numErroresJ1);
					ledBjug1.encender();
					ledBjug2.apagar();
					break;
				case 3:
					estadoActual = 1;
					numErroresJ2++;
					mostrarLetras(numErroresJ2);
					delay(3000);
					mostrarLetras(numErroresJ1);
					ledBjug1.encender();
					ledBjug2.apagar();
					break;
				case 4:
					estadoActual = 2;
					numErroresJ1++;
					mostrarLetras(numErroresJ1);
					delay(3000);
					mostrarLetras(numErroresJ2);
					ledBjug2.encender();
					ledBjug1.apagar();
					break;
				default:
					break;
			}
                        delay(5500);
		}
	}
  
	delay(3000);
	if (numErroresJ1 == 4){
		pantalla.mostrar("J1");
		delay(2000);
		pantalla.mostrar("LOSE");
		delay(4000);
		pantalla.mostrar("J2");
		delay(2000);
		pantalla.mostrar("GANA");
		delay(4000);
	}else if (numErroresJ2 == 4){
		pantalla.mostrar("J2");
		delay(2000);
		pantalla.mostrar("LOSE");
		delay(4000);
		pantalla.mostrar("J1");
		delay(2000);
		pantalla.mostrar("GANA");
		delay(4000);
	}
}

void mostrarLetras(int numErrores){
	switch(numErrores){
                case 0: pantalla.mostrar("xxxx");
                        break;
		case 1: pantalla.mostrar("A");
			break;
		case 2: pantalla.mostrar("AS");
                      break;
		case 3: pantalla.mostrar("ASN");
                      break;
		case 4: pantalla.mostrar("ASNO");
                      break;
		default:
            break;
	}
}

void juego11 () {
	// Marcadores para los jugadores
	int puntosJugador1 = 0;
	int puntosJugador2 = 0;
	bool turnoJ1 = true;
	
	ledBjug1.encender();
    ledBjug2.apagar();

	// Cuenta atras
	bocina.charge();
	
	// Continuar la partida hasta que uno de los jugadores llegue a 11
	while (puntosJugador1 != 11 && puntosJugador2 != 11) {
		// Marcador, con los dos digitos de la izquierda para la puntuacion del jugador 1
		// y los dos digitos de la derecha para la puntuacion del jugador 2
		int marcador = puntosJugador1 * 100 + puntosJugador2;
		
		// Mostrar marcador
		Serial.write(byte(119));    // Activar seperador
		Serial.write(byte(16));     // Activar seperador
  
		if (marcador < 10)
			Serial.print("000");
		else if (marcador < 100)
			Serial.print("00");
		else if (marcador < 1000)
			Serial.print("0");
        
		Serial.print(marcador);
		
		// Si anota canasta
		if (canastaJugador1.presionado()) {
			if (turnoJ1)
				puntosJugador1++;
			else
				puntosJugador2++;
				
			delay(500);
		}
		// Si no anota
		if (botonAceptar.presionado()) {
			// Cambio de turno
			turnoJ1 = !turnoJ1;
			
			// Encender la luz del jugador que sea el turno
			if (turnoJ1) {
				ledBjug1.encender();
			    ledBjug2.apagar();
			} else {
				ledBjug2.encender();
			        ledBjug1.apagar();
			}
			
			delay(5500);
		}
	}     

	pantalla.resetear();	// Desactivar separador
 
	if ((int)(puntosJugador1 / 100) == 11){
		pantalla.formarPalabraDerIzq("JUG1");
		delay(2000);
		pantalla.formarPalabraDerIzq("GANA");
		delay(2000);
	}
	else {
		pantalla.formarPalabraDerIzq("JUG2");
		delay(2000);
		pantalla.formarPalabraDerIzq("GANA");
		delay(2000);
	}
}


/************************************************************************************
								FUNCIONES ADICIONALES
************************************************************************************/

/*
  Muestra por el Display4x7 quien ha sido el ganador de la partida
*/
void mostrarGanador (int puntos1, int puntos2) {
	if (puntos1 > puntos2) {
		pantalla.mostrar("GANA");
		delay(1000);
		pantalla.mostrar("JUG1");
		delay(1000);
	} else if (puntos2 > puntos1) {
		pantalla.mostrar("GANA");
		delay(1000);
		pantalla.mostrar("JUG2");
		delay(1000); 
	} else {
		pantalla.mostrar("IGUA");
		delay(1000);
	}
}

/*
  Marca un tic de reloj, restando 1 a los segundos restantes en cada iteracion
 */
void tic() {
	segundosRestantes--;
}

void palabra () {
	pantalla.deslizarCaracterDerIzq('1', 500);
}

/*
	Enciende los leds de bonus de cada jugador
*/
void encenderLedsBonus (int bonusJug1, int bonusJug2) {
	if (bonusJug1 >= 300) {
		ledRjug1.encender(255);
		ledAjug1.encender(255);
		ledVjug1.encender(255);
	} else if (bonusJug1 >= 200) {
		ledRjug1.encender(255);
		ledAjug1.encender(255);
		ledVjug1.encender((int)((bonusJug1-200) * 2.55));    
	} else if (bonusJug1 >= 100) {
		ledRjug1.encender(255);
		ledAjug1.encender((int)((bonusJug1-100) * 2.55));
		ledVjug1.encender(0);    
	} else {
		ledRjug1.encender((int)(bonusJug1 * 2.55));
		ledAjug1.encender(0);
		ledVjug1.encender(0);    
	}
  
	if (bonusJug2 >= 300) {
		ledRjug2.encender(255);
		ledAjug2.encender(255);
		ledVjug2.encender(255);
	} else if (bonusJug2 >= 200) {
		ledRjug2.encender(255);
		ledAjug2.encender(255);
		ledVjug2.encender((int)((bonusJug2-200) * 2.55));    
	} else if (bonusJug2 >= 100) {
		ledRjug2.encender(255);
		ledAjug2.encender((int)((bonusJug2-100) * 2.55));
		ledVjug2.encender(0);    
	} else {
		ledRjug2.encender((int)(bonusJug2 * 2.55));
		ledAjug2.encender(0);
		ledVjug2.encender(0);    
	}
}

/*
	Enciende y apaga los leds y muestra un mensaje por pantalla para comprobar
	que todos los dispositivos funcionan correctamente
*/
void test () {
	pantalla.mostrar("HOLA");
	delay(250);
	
	ledRjug1.encender();
	ledAjug1.encender();
	ledVjug1.encender();
	ledBjug1.encender();
	ledRjug2.encender();
	ledAjug2.encender();
	ledVjug2.encender();
	ledBjug2.encender();
	delay(250);
	
	ledRjug1.apagar();
	ledAjug1.apagar();
	ledVjug1.apagar();
	ledBjug1.apagar();
	ledRjug2.apagar();
	ledAjug2.apagar();
	ledVjug2.apagar();
	ledBjug2.apagar();
	delay(50);
	
	ledRjug1.encender();
	ledAjug1.encender();
	ledVjug1.encender();
	ledBjug1.encender();
	ledRjug2.encender();
	ledAjug2.encender();
	ledVjug2.encender();
	ledBjug2.encender();
	delay(250);
	
	ledRjug1.apagar();
	ledAjug1.apagar();
	ledVjug1.apagar();
	ledBjug1.apagar();
	ledRjug2.apagar();
	ledAjug2.apagar();
	ledVjug2.apagar();
	ledBjug2.apagar();
	
	pantalla.resetear();
}

