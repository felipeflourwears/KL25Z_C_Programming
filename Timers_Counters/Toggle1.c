#include <MKL25Z4.H>

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

void delay1ms(void) {
SysTick->LOAD = 41939;
SysTick->CTRL = 0x5; /* Enable the timer and choose sysclk
as the clock source */
while((SysTick->CTRL & 0x10000) == 0) /* wait until the
COUNT flag is set */ { }
SysTick->CTRL = 0; /* Stop the timer (Enable = 0) */ }
