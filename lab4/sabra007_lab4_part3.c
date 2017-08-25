/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 4 Exercise 3
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 */
#include <avr/io.h>


 unsigned char tmpB = 0x00;
 unsigned char tmpD = 0x00;

/*Define user variables and functions for this state machine here.*/
enum SM1_States { SM1_Init, SM1_s2, SM1_s3, SM1_s4, SM1_s5, SM1_s6 } SM1_State;

unsigned char TickFct_State_machine_1() {
	switch(SM1_State) { // Transitions
		case SM1_Init:
		if (tmpB) {
			SM1_State = SM1_s2;
		}
		else
		{
		 SM1_State = SM1_Init;
		}
		break;
		case SM1_s2:
		if (tmpB) {
			SM1_State = SM1_s3;
		}
		else
		{
			SM1_State = SM1_s2;
		}
		break;
		case SM1_s3:
		if (tmpB) {
			SM1_State = SM1_s4;
	}
	else
	{
		SM1_State = SM1_s3;
	}
		break;
		case SM1_s4:
		if (tmpB) {
			SM1_State = SM1_s5;
		}
		else
		{
			SM1_State = SM1_s4;
		}
		break;
		case SM1_s5:
		if (tmpB) {
			SM1_State = SM1_s6;
		}
		else
		{
			SM1_State = SM1_s5;
		}
		break;
		case SM1_s6:
		if (tmpB) {
			SM1_State = SM1_Init;
		}
		else
		{
			SM1_State = SM1_s6;
		}
		break;
		default:
		SM1_State = SM1_Init;
	} // Transitions

	switch(SM1_State) { // State actions
		case SM1_Init:
		tmpD=0x00;
		break;
		case SM1_s2:
		tmpD=0x09;
		break;
		case SM1_s3:
		tmpD=0x12;
		break;
		case SM1_s4:
		tmpD=0x24;
		break;
		case SM1_s5:
		tmpD=0x15;
		break;
		case SM1_s6:
		tmpD=0x2A;
		break;
		default: // ADD default behaviour below
		break;
	} // State actions
	return tmpD;
}

int main() {

	DDRB = 0x00; PORTB = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;


	SM1_State = 0; // Initial state



	while(1) {
	tmpB = ~PINB & 0x01;
	tmpD =  TickFct_State_machine_1();
	PORTD = tmpD;
	} // while (1)
} // Main
