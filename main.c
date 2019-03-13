#include "msp430.h"

void main(void) {
	WDTCTL = WDTPW + WDTHOLD;         // Stop WDT
	P1DIR |= BIT2;                    // P1.2 to output
	P1SEL |= BIT2;                    // P1.2 to TA0.1
	// ADC10CTL0 = ADC10SHT_2 + ADC10ON; // ADC10ON
	// ADC10CTL1 = INCH_1;               // input A1
	// ADC10AE0 |= 0x02;                 // PA.1 ADC option select
	P1DIR |= 0x02 ;                   // Set P1.2 as output
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
	while (1) {
		for (int i = 6000; i >= 0; i-= 30) {
			CCR1 = i;
			for (int j = 0; j < 10000; j++);
			
		}
		// for (int k = 1; k < 5000; k++) {
		// 	CCR1 = k;
		// 	for (int l = 0; l < 10000; l++);
		// }
		// for (int i = 0; i < 1024; i++) {
		// 		CCR1 = i;
		// 		for (int j = 0; j < 1000; j++);
		// 	}
		// CCR1 = 0;
		// for (int j = 0; j < 100; j++);
		// CCR1 = 90;
		// for (int j = 0; j < 100; j++);
	}
	_BIS_SR(LPM0_bits);                // Enter Low Power Mode 0
}