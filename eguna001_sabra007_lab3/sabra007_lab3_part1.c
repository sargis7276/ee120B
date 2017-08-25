/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 3 Exercise 1
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 */

#include <avr/io.h>

enum LT_States {ST_SMStart, ST_PB0, ST_PB1} ST_State;

void buttonPressed(unsigned char tmpA)
{
	switch(ST_State){ //Transitions
		
		case ST_SMStart: // // Initial transition
			ST_State = ST_PB0;
			break;
		
		case ST_PB0: 
			if (tmpA == 0x01)
			{
				ST_State = ST_PB0;
			}
			else if (tmpA == 0x00)
			{
				ST_State = ST_PB1;
			}
			break;
			
		case ST_PB1:
			if (tmpA == 0x01)
			{
				ST_State = ST_PB1;
			}
			else if (tmpA == 0x00)
			{
				ST_State = ST_PB0;
			}
			break;
			
		default:
			 ST_State = ST_SMStart;
			break;
		
	}//Transitions
	
	switch(ST_State){ // State Actions
		case ST_PB0:
			PORTB = 0x01;
		break;

		case ST_PB1:
			PORTB = 0x02;
		break;

		default:
		break;
		
		
	}//State Actions
	
}

int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x01;
	
	unsigned char tmpA = 0x00;
	
    while(1)
    {
		tmpA = PINA & 0xFF;
	   buttonPressed(tmpA);
    }
	
	return 0;
}