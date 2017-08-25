/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 3 Exercise 3
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 */


/*
A household has a digital combination deadbolt lock system on the doorway.
The system has buttons on a keypad.

Button 'X' connects to PA0, 'Y' to PA1, and '#' to PA2.

Pressing and releasing '#', then pressing 'Y', should unlock the door by setting PB0 to 1.

Any other sequence fails to unlock.
Pressing a button from inside the house (PA7) locks the door (PB0=0).

For debugging purposes, give each state a number, and always write the current state to PORTC (consider using the enum state variable).
Also, be sure to check that only one button is pressed at a time.
 */

#include <avr/io.h>

enum LT_States {ST_SMStart, ST_Inital, ST_Wait, ST_S1, ST_Unlock} ST_State;

unsigned char buttonPressed(unsigned char tmpA, unsigned char tmpB)
{
	switch(ST_State){ //Transitions

		case ST_SMStart: // // Initial transition
		ST_State = ST_Inital;
		break;

		case ST_Inital:
		ST_State = ST_Wait;
		break;


		case ST_Wait:
		if(tmpA == 0x04)
		{
			ST_State = ST_S1;
		}
		else
		{
			ST_State = ST_Inital;
		}
		break;

		case ST_S1:
		if(tmpA == 0x04)
		{
			ST_State = ST_S1;
		}
		else if(tmpA == 0x02)
		{
			ST_State = ST_Unlock;
		}
		else
		{
			ST_State = ST_Wait;
		}
		break;

		case ST_Unlock:
		if(tmpA == 0x80)
		{
			ST_State = ST_Inital;
		}
		break;

		default:
		ST_State = ST_Inital;
		break;

	}//Transitions

	switch(ST_State){ // State Actions
		case ST_Inital:
		tmpB = 0x00;
		break;

		case ST_Wait:
		break;

		case ST_S1:
		break;

		case ST_Unlock:
		tmpB = 0x01;
		break;

		default:
		break;


	}//State Actions
	return tmpB;
}

int main(void)
{

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;

	while(1)
	{
		tmpA = PINA & 0xFF;
		tmpB = buttonPressed(tmpA, tmpB);
		PORTB = tmpB;
	}

	return 0;
}