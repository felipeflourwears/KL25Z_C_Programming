/* Este programa usa TPM0 para generar un retardo máximo para alternar el LED azul.
MCGFLLCLK (41,94 MHz) se utiliza como reloj contador de tiempo. 65,536-->2^16
El registro del módulo se establece en 65.535. El contador del temporizador se desborda a 41,94 MHz / 65,536 = 640 Hz
Ponemos el retardo de tiempo de espera en un bucle for y lo repetimos 320 veces antes de alternar el LED. Esto da como resultado que el LED parpadee medio segundo encendido y medio segundo apagado.
El LED azul está conectado a PTD1. */
#include <MKL25Z4.H>
int main (void) {
int i;
SIM->SCGC5 |= 0x1000; /* enable clock to Port D */
PORTD->PCR[1] = 0x100; /* make PTD1 pin as GPIO */
PTD->PDDR |= 0x02; /* make PTD1 as output pin */
SIM->SCGC6 |= 0x01000000; /* enable clock to TPM0--->D24--->2^24=16777216 Hexadecimal*/
SIM->SOPT2 |= 0x01000000;/* use MCGFLLCLK as CNT clock */
TPM0->SC = 0; /* disable timer while configuring */
TPM0->MOD = 0xFFFF; /* max modulo value */
TPM0->SC |= 0x80; /* clear TOF¨---2^7=128 se encuentra en D7 */
TPM0->SC |= 0x08; /* enable timer free-running mode */
	
	
	while (1) {
for(i = 0; i < 320; i++) {
/* repeat timeout for 320 times */
while((TPM0->SC & 0x80) == 0) {}
/* wait until the TOF is set */
TPM0->SC |= 0x80; /* clear TOF */
PTD->PTOR = 0x02; /* toggle blue LED */
}
}