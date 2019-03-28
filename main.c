#include "msp430.h"

void main(void) {

	int position[5] = {139, 171, 202, 233, 264}; // THIS IS INPUT! 
    int acc[768];
	for (int a = 0; a < 768; a++ ) {
	   acc[a] = 0;
       for (int i = 0; i < sizeof(position) / sizeof(position[0]); i++) {
           if (position[i] == a) {
               acc[a] = 250;
               break;
           }
           else if (a + 1 == position[i] || a - 1 == position[i]) {
               acc[a] = 220;
               break;
           }
           else if (a + 2 == position[i] || a - 2 == position[i]) {
               acc[a] = 190;
               break;
           }
           else if (a + 3 == position[i] || a - 3 == position[i]) {
               acc[a] = 140;
               break;
           }
       }
       
    }

	WDTCTL = WDTPW + WDTHOLD;         // Stop WDT
	P1DIR |= BIT2;                    // P1.2 to output
	P1SEL |= BIT2;                    // P1.2 to TA0.1
	// ADC10CTL0 = ADC10SHT_2 + ADC10ON; // ADC10ON
	// ADC10CTL1 = INCH_1;               // input A1
	// ADC10AE0 |= 0x02;                 // PA.1 ADC option select
	P1DIR |= 0xC2 ;                   // Set P1.2, P1.6, P1.7 as output
	CCTL1 = OUTMOD_7;                 // CCR1 reset/set
	CCR0 = 12000;                     // PWM Period
	TACTL = TASSEL_2 + MC_1;          // SMCLK, up mode

	// for (;;) {
	// 	 ADC10CTL0 |= ENC + ADC10SC;      // Sampling and conversion start
	// 	 while (ADC10CTL1 &ADC10BUSY);    // ADC10BUSY?
	// 	 CCR1 = ADC10MEM;                 // Set duty cycle to equal input voltage
	// 	 unsigned i;
	// 	 for (i = 0xFFFF; i > 0; i--);    // Delay
	// }
	// P1OUT = 0x40;
	// while (1) {
	// 	for (int i = 6000; i >= 0; i-= 30) {
	// 		CCR1 = i;
	// 		// read_array();
	// 		P1OUT ^= 0xC0; // blinks when in loop
	// 		for (int j = 0; j < 20000; j++);
			
	// 	}
	// }

	_BIS_SR(LPM0_bits);                // Enter Low Power Mode 0
}

