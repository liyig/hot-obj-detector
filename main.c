#include "msp430.h"
#include <stdlib.h>

// Function declaration
static int sum_array(int acc[], int start, int size);
static int contains(int hot_object[], int position);

int contains(int hot_object[], int position) {
    for (int i = 0; i < 4; i++) { // INPUT: Size of hot object
        if (hot_object[i] == position) {
            return 1;
        }
    }
    return 0;
}

int sum_array(int acc[], int start, int size) {
    int res = 0;
    for (int i = start; i < start + size; i++) {
        res += acc[i];
    }
    return res;
}

void main(void) {
    // =================== MOCKING INFRARED CAMERA ===================
    register int start, end;
	// Mocking a hot object on the LEFT of the screen
	// int hot_object[4] = {325, 326, 357, 358};
	// start = 2290;
	// end = 2250;

	// Mocking a hot object SLIGHT on the LEFT of the screen
	// int hot_object[4] = {330, 331, 362, 363};
	// start = 1915;
	// end = 1875;

	// Mocking a hot object in the MIDDLE of the screen
	int hot_object[4] = {335, 336, 367, 368};
	start = 1540;
	end = 1500;

	// Mocking a hot object SLIGHT on the RIGHT of the screen
	// int hot_object[4] = {340, 341, 372, 373};
	// start = 1165;
	// end = 1125;

	// Mocking a hot object on the RIGHT of the screen
	// int hot_object[4] = {345, 346, 377, 378};
	// start = 790;
	// end = 750;

    int acc[768];

	for (int a = 0; a < 768; a++ ) {
      	if (contains(hot_object, a)) {
          	acc[a] = 250;
      	}
		else if (contains(hot_object, a+1) || contains(hot_object, a-1)
		   		|| (a > 32 && contains(hot_object, a-32)) || (a < 32*23 && contains(hot_object, a+32))) {
		acc[a] = 220;
		}
		else if (contains(hot_object, a+2) || contains(hot_object, a-2)
		   		|| (a > 32 && contains(hot_object, a-31)) || (a < 32*23 && contains(hot_object, a+31))
		   		|| (a > 32 && contains(hot_object, a-33)) || (a < 32*23 && contains(hot_object, a+33))
			    || (a > 64 && contains(hot_object, a-64)) || (a < 32*22 && contains(hot_object, a+64))) {
		acc[a] = 190;
		}
		else if (contains(hot_object, a+3) || contains(hot_object, a-3) 
		   		|| (a > 32 && contains(hot_object, a-30)) || (a < 32*23 && contains(hot_object, a+30))
		   		|| (a > 32 && contains(hot_object, a-34)) || (a < 32*23 && contains(hot_object, a+34))) {
		acc[a] = 140;
		}
		else if (contains(hot_object, a+4) || contains(hot_object, a-4)) {
		acc[a] = 120;
		}
		else if (contains(hot_object, a+5) || contains(hot_object, a-5)) {
		acc[a] = 50;
		}
		else {
		acc[a] = 0;
		}
    }

    // =================== ANALYZING OUTPUT OF INFRARED CAMERA ===================
    int num_row = sizeof(acc)/sizeof(acc[0])/32; // Each row has 32 ele
    int row_counter = 0; // For tracking row in iteration
    
    int right = 0;
    int left = 0;
    int mid = 0;
    
    for (int k = 0; k < num_row; k ++) {
       int start_left = 0 + 32*row_counter;
       int start_mid = 11 + 32*row_counter;
       int start_right = 21 + 32*row_counter;
       int end_right = 32 + 32*row_counter;
       
       left += sum_array(acc, start_left, 11);
       mid += sum_array(acc, start_mid, 10);
       right += sum_array(acc, start_right, 11);
       
       row_counter++;
    }  

	// ========== INITIALIZING MICROPROCESSOR ==========
	WDTCTL = WDTPW + WDTHOLD;         // Stop WDT
	P1DIR |= BIT2;                    // P1.2 to output
	P1SEL |= BIT2;                    // P1.2 to TA0.1
	P1DIR |= 0x79 ;                   // Set P1.0, P1.3, P1.4, P1.5, P1.6 as output
									  //P2.3, P2.4, P2.5 are input
	CCTL1 = OUTMOD_7;                 // CCR1 reset/set
	CCR0 = 12000;                     // PWM Period
	TACTL = TASSEL_2 + MC_1;          // SMCLK, up mode


	// if (left > mid && left > right) {
	// 	start = 2290;
	// 	end = 2250;
	// } else if (left == mid && left > right) {
	// 	start = 1915;
	// 	end = 1875;
	// } else if (mid > left && mid > right) {
	// 	start = 1540;
	// 	end = 1500;
	// } else if (right == mid && right > left) {
	// 	start = 1165;
	// 	end = 1125;
	// } else if (right > mid && right > left) {
	// 	start = 790;
	// 	end = 750;
	// } else {
	// 	start = 6000;
	// 	end = 0;
	// }



	P1OUT = 0x48;
	while (1) {
		for (int i = start; i >= end; i-= 20) {
			CCR1 = i;
			P1OUT ^= 0xC0; // blinks when in loop
			for (int j = 0; j < 10000; j++);	
		}
	P1OUT ^= 0x1;
	}
	// _BIS_SR(LPM0_bits);                // Enter Low Power Mode 0
}

