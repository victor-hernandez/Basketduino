/*
  Piezoelectrico.cpp - Biblioteca para tocar la melodia "Charge" con un piezoelectrico
  
  @author: Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
  @version: 1.0
*/
#include "Arduino.h"
#include "Piezoelectrico.h"
#include "Metro.h"

// Frecuencia en hercios de las notas musicales 
#define DO  261.626
#define RE  293.665 
#define MI  329.628 
#define FA  349.228 
#define FA_ 370
#define SOL 391.995
#define SOL_ 415
#define LA   440.000 
#define LA_  466
#define SI   493.883 
#define DO2  523.251
#define RE2  587.33
#define MI2  659.255
#define FA2  698
#define SOL2 784
#define LA2  880

#define SILENCIO 0

float cancionCharge[]={LA_, FA_, SOL_, LA_, SI,
                 FA_, SOL_, LA_, DO2, SOL, LA, SI, DO2, SOL, LA, SI, DO2, SILENCIO,
                 SOL, DO2, MI2, SOL2, MI2, SOL2, SILENCIO}; // Cancion
float duracionCharge[]={2.0, 1.80, 1.80, 1.75, 1.75,
                1.70, 1.70, 1.65, 1.65, 1.60, 1.60, 1.55, 1.55, 1.50, 1.50, 1.45, 2.5, 2.0,
                1.0, 1.0, 1.0, 2.0, 1.0, 4.0, 0};
float cancionChargeCompleta[]={LA_, FA, SOL, LA, LA_, FA, SOL, LA, SI, FA_, SOL_, LA_, SI,
                 FA_, SOL_, LA_, DO2, SOL, LA, SI, DO2, SOL, LA, SI, DO2, SILENCIO,
                 SOL, DO2, MI2, SOL2, MI2, SOL2, SILENCIO}; // Cancion*/
float duracionChargeCompleta[]={2.0, 2.0, 2.0, 1.95, 1.95, 1.90, 1.90, 1.85, 1.85, 1.80, 1.80, 1.75, 1.75,
                1.70, 1.70, 1.65, 1.65, 1.60, 1.60, 1.55, 1.55, 1.50, 1.50, 1.45, 2.5, 2.0,
                1.0, 1.0, 1.0, 2.0, 1.0, 4.0, 0};
                
String cuentaAtras[]={	"5xxx", "x5xx", "xx5x", "xxx5", "xxxx", "4xxx", "x4xx", "xx4x", "xxx4", "xxxx",
						"3xxx", "x3xx", "xx3x", "xxx3", "xxxx", "2xxx", "x2xx", "xx2x", "xxx2", "xxxx",
					  	"1xxx", "x1xx", "xx1x", "xxx1", "xxxx", "xGOx"};

/*
	Constructor para un objeto de la clase Piezoelectrico
*/
Piezoelectrico::Piezoelectrico (int pin) {
	_pin = pin;
	pinMode(_pin, OUTPUT);
}

/*
	Toca la melodia "Charge" en el piezoelectrico
	@author		Victor Hernandez Bermejo, Gabriel Rodriguez Polaina, Diego Sepulveda Blanco
	@version	1.0
	@since		1.0
*/
void Piezoelectrico::charge() {
    boolean continuar = true;
    int i = 0;
    int j = 0;
    Metro metronomoCancion(duracionCharge[i]*150);
    Metro metronomoPantalla(200);
    Serial.print(cuentaAtras[i]);
        
	while (continuar) {
		if (metronomoCancion.check()) {
			if (cancionCharge[i] == 0)
				noTone(_pin);
			else
				tone(_pin, round(cancionCharge[i]));
			
			metronomoCancion.interval(duracionCharge[i]*150);
			i++;
		}
          
		if (i >= sizeof(cancionCharge)/sizeof(float))
			continuar = false;
            
        if (metronomoPantalla.check()) {
                if (++j < 26)
                Serial.print(cuentaAtras[j]);
        }
    }
}
