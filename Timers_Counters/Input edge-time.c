//Code de Gilberto Error en diff
/* Usando el canal 0 de TPM2 para medir el período de entrada.
*Este programa utiliza la captura de tiempo de flanco de entrada de TPM2 CH1 
para medir el período de una forma de onda periódica.
*MCGFLLCLK (41,94 MHz) se utiliza como reloj contador de tiempo.
*El preescalador está configurado para dividir por 128. 
*Por lo tanto, el contador del temporizador está contando a 41,94 MHz / 128 = 327,656 Hz.
*El canal 0 del temporizador 2 está configurado como modo de captura de tiempo 
de flanco de entrada y la entrada usa PTA1.

*Cuando ocurre un flanco ascendente en PTA1, el valor del contador del temporizador 
se copia a TPM2_C0V y se establece el CHF.
*El programa espera a que se establezca el indicador CHF y luego 
calcula la diferencia entre el valor actual y el valor registrado anteriormente.
*Los bits 11-9 se utilizan para controlar los LED de tres colores.
*El LED debe cambiar de color cuando cambia la frecuencia de entrada por debajo de 642 Hz. 
*Por encima de 642 Hz, el número de ciclos de reloj entre flancos ascendentes es demasiado pequeño para alcanzar el bit 9.
*/
#include <MKL25Z4.H>
int main (void) {
unsigned short then = 0;
unsigned short now = 0;
unsigned short diff;
	
/* Initialize GPIO pins for tri-color LEDs */
SIM->SCGC5 |= 0x400; /* enable clock to Port B */
SIM->SCGC5 |= 0x1000; /* enable clock to Port D */
PORTB->PCR[18] = 0x100; /* make PTB18 pin as GPIO */
PTB->PDDR |= 0x40000; /* make PTB18 as output pin */
PORTB->PCR[19] = 0x100; /* make PTB19 pin as GPIO */
PTB->PDDR |= 0x80000; /* make PTB19 as output pin */
PORTD->PCR[1] = 0x100; /* make PTD1 pin as GPIO */
PTD->PDDR |= 0x02; /* make PTD1 as output pin */
/* end GPIO pin initialization for LEDs */
	
/* Start of Timer code */
SIM->SCGC5 |= 0x0200; /* enable clock to Port A */
PORTA->PCR[1] = 0x0300; /* set PTA1 pin for TPM2CH0 */
SIM->SCGC6 |= 0x04000000; /* enable clock to TPM2 */
/* use MCGFLLCLK as timer counter clock */
SIM->SOPT2 |= 0x01000000;
TPM2->SC = 0; /* disable timer while configuring */
TPM2->SC = 0x07; /* prescaler /128 */
TPM2->MOD = 0xFFFF; /* max modulo value */
TPM2->CONTROLS[0].CnSC = 0x04; /* IC rising edge */
TPM2->SC |= 0x08; /* enable timer */

while (1) {
while(!(TPM2->CONTROLS[0].CnSC & 0x80)) { }
/* wait until the CHF is set */
TPM2->CONTROLS[0].CnSC |= 0x80; /* clear CHF */
now = TPM2->CONTROLS[0].CnV;
diff = now - then;
then = now;
/* save the current counter value for next calculation */
}}

