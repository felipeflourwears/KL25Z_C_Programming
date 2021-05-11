/* Alternar LED azul usando retardo TPM0
Este programa usa TPM0 para generar un retraso largo para alternar el LED azul.
MCGIRCLK (32,768 kHz) se utiliza como reloj contador de tiempo.
El preescaler está configurado para dividir por 4 y el módulo
registro se establece en 40,959. El contador del temporizador se desborda a 32,768 Hz / 40,960 / 4 = 0.2 Hz
El LED azul está conectado a PTD1.
*/

#include <MKL25Z4.H>
int main (void) {
SIM->SCGC5 |= 0x1000; /* enable clock to Port D */
PORTD->PCR[1] = 0x100; /* make PTD1 pin as GPIO */
PTD->PDDR |= 0x02; /* make PTD1 as output pin */
SIM->SCGC6 |= 0x01000000; /* enable clock to TPM0 */
SIM->SOPT2 |= 0x03000000;
/* use MCGIRCLK as timer counter clock */
	
TPM0->SC = 0; /* disable timer while configuring */
TPM0->SC = 0x02; /* prescaler /4--->Datos sacados del prescaler */
TPM0->MOD = 40960 - 1; /* modulo value */
TPM0->SC |= 0x80; /* clear TOF */
TPM0->SC |= 0x08; /* enable timer free-running mode*/
while (1)
{
while((TPM0->SC & 0x80) == 0) { }
/* wait until the TOF is set */
TPM0->SC |= 0x80; /* clear TOF */
PTD->PTOR = 0x02; /* toggle blue LED */
}
}
