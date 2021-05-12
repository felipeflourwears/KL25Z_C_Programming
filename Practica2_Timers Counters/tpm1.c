/*Parte 3. Alternar el LED azul usando el retardo TPM0 (preescalador). 
Este programa tiene que hacer uso del TPM0 para generar un retardo máximo para alternar el LED azul. 
MCGFLLCLK (41,94 MHz) se utiliza como reloj contador de tiempo. 
El preescaler debe configurarse para dividir entre 128 y el registro de módulo en 65.535. 
El contador del temporizador se desborda a 41,94 MHz / 128 / 65,536 = 5,0 Hz. El LED azul está conectado a PTD1.

Recuerde que los pasos para configurar el contador son
1) habilite el reloj al módulo TPMx en SIM_SCGC6,
2) seleccione la fuente de reloj para el contador del temporizador en SIM_SOPT2,
3) deshabilitar el temporizador mientras se modifica la configuración,
4) configure el modo como modo de temporizador de contador ascendente con el registro TPMx_SC,
5) cargue el registro TPMx_MOD con el valor adecuado,
6) bandera TOF clara,
7) habilitar el temporizador,
8) espere a que la bandera TOF se ponga ALTA.
Responde las siguientes preguntas
(a) Mostrar el cálculo de la demora de tiempo para el programa
(b) calcular el tamaño de retardo más grande sin preescalador
(c) Encuentre el valor TPMx_MOD para generar un retraso de 0.1 segundos. Utilice el preescalador de 128.
---------------------------------------------------------------------------------------------------------
Alternar LED azul usando retardo TPM0 (preescalador)
Este programa usa TPM0 para generar un retardo máximo para alternar el LED azul.
MCGFLLCLK (41,94 MHz) se utiliza como reloj contador de tiempo.
El preescaler se establece en dividido por 128 y el registro de módulo se establece en 65.535. 
El contador del temporizador se desborda a 41,94 MHz / 128 / 65,536 = 5,0 Hz.
El LED azul está conectado a PTD1.

*/

// In this program, we will use the timer tmp1 to toggle the blue led of the kl25z at its maximum delay available

#include <MKL25Z4.H>
// BLUE ->  PTD1
// This function will tune the parameters for the blue led

void ledInit(void);

void ledInit(void){
	SIM->SCGC5 |= 0x1000;  // enable clock to port D
	PORTD->PCR[1] = 0x100;  // make led pin a miscellaneous pin
	PTD->PDDR |= 0x02; // make blue led pin an output gpio
}


void timerInit(void){
	SIM->SCGC6 |= 0x02000000; //enable the clock 6 to tpm1
	SIM->SOPT2 |= 0x01000000;  // Enable 41.94 hz to clock
	TPM1->SC = 0; // disbale timer
	TPM1->SC = 0x07; 
	TPM1->MOD = 0xFFFF; // SET MAX VALUE 65536
	TPM1->SC |= 0x80; // CREAL TOF
	TPM1->SC |= 0x08;   // FRERRUNNING MODE
}

int main (void) {
	ledInit();
	timerInit();

		while (1) {
			while((TPM1->SC & 0x80) == 0) { } 
				TPM1->SC |= 0x80; 
				PTD->PTOR = 0x02; 

		}

}

