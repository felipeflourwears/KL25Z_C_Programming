/*Alternar LED azul usando retardo TPM0 (preescalador)
Este programa usa TPM0 para generar un retardo máximo para alternar el LED azul.
MCGFLLCLK (41,94 MHz) se utiliza como reloj contador de tiempo.
El preescaler se establece en dividido por 128 y el registro de módulo se establece en 65.535. El contador del temporizador se desborda a 41,94 MHz / 128 / 65,536 = 5,0 Hz.
El LED azul está conectado a PTD1.
*/

#include <MKL25Z4.H>
int main (void) {
SIM->SCGC5 |= 0x1000; /* enable clock to Port D */
PORTD->PCR[1] = 0x100; /* make PTD1 pin as GPIO */
PTD->PDDR |= 0x02; /* make PTD1 as output pin */
SIM->SCGC6 |= 0x01000000; /* enable clock to TPM0 D24*/
SIM->SOPT2 |= 0x01000000; /* use MCGFLLCLK=41.94Mhz as timer counter clock */
TPM0->SC = 0; /* disable timer while configuring */
TPM0->SC = 0x07; /* prescaler /128 max 2^7 */
TPM0->MOD = 0xFFFF; /* max modulo value */
TPM0->SC |= 0x80; /* clear TOF D7*/
TPM0->SC |= 0x08; /* enable timer free-running mode */
	while (1) {
while((TPM0->SC & 0x80) == 0) { }
/* wait until the TOF is set */
TPM0->SC |= 0x80; /* clear TOF */
PTD->PTOR = 0x02; /* toggle blue LED */
}
}
