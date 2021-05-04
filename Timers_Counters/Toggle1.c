#include <MKL25Z4.H>

/* Toggling LEDs using SysTick counter
This program let the SysTick counter run freely and
dumps the counter values to the tri-color LEDs
continuously.
The counter value is shifted 4 places to the right
so that the changes of LEDs will be slow enough to
be visible.
SysTick counter has 24 bits.
The red LED is connected to PTB18.
The green LED is connected to PTB19.
*/

void delay1ms(void);

int main (void) {
int c;
SIM->SCGC5 |= 0x400; /* enable clock to Port B */
PORTB->PCR[18] = 0x100; /* make PTB18 pin as GPIO */
PORTB->PCR[19] = 0x100; /* make PTB19 pin as GPIO */
PTB->PDDR |= 0xC0000; /* make PTB18, 19 as output pin */
/* Configure SysTick */
SysTick->LOAD = 0xFFFFFF; /* reload reg. with max val */
SysTick->CTRL = 5; /* enable it, no interrupt, use
system clock */
while (1) {
c = SysTick->VAL; /* read current val of down counter */
PTB->PDOR = c >> 4; /* line up counter MSB with LED */
}
}


/*
Using the System Tick timer, write a function that makes a
delay of 1 ms. Assume sysclk = 41.94 MHz.
Solution: From the equation delay = (N + 1) / sysclk
(N + 1) = delay × sysclk = 0.001 sec × 41.94 MHz = 41,940
==>
 N = 41,940 – 1 = 41939
 
*/
void delay1ms(void) {
SysTick->LOAD = 41939;
SysTick->CTRL = 0x5; /* Enable the timer and choose sysclk
as the clock source */
while((SysTick->CTRL & 0x10000) == 0) /* wait until the
COUNT flag is set */ { }
SysTick->CTRL = 0; /* Stop the timer (Enable = 0) */ }
