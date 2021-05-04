#include <MKL25Z4.H>
/*
The next program uses the SysTick to toggle the PTB18
every 200 milliseconds.
We need the RELOAD value of 8,387,999 since 0.200 sec *
41.94 MHz = 8,388,000.
We assume the system clock is 41.94 MHz. Notice, every
8,388,000 clocks the down counter reaches 0, and COUNT
flag is raised.
Then the RELOAD register is loaded with 8,388,000
automatically. The COUNT flag is clear when the STCTRL
(SysTick->CTRL) register is read.
*/



int main (void) {
SIM->SCGC5 |= 0x0400; /* enable clock to Port B */
PORTB->PCR[18] = 0x100; /* make PTB18 pin as GPIO */
PTB->PDDR |= 0x040000; /* make PTB18 as output pin */
/* Configure SysTick */
SysTick->LOAD = 8388000 - 1; /* reload with number of
clocks per 200 ms */
SysTick->CTRL = 5; /* enable it, no interrupt, use
system clock */
while (1)
{
if (SysTick->CTRL & 0x10000) /* if COUNT flag is set */
PTB->PTOR = 0x040000; /* toggle red LED */
} }


