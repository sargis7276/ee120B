/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 3 Exercise 2
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 */

#include <avr/io.h>


enum LT_States {ST_SMStart, ST_Inital, ST_PressOff, ST_Idle, ST_Inc, ST_Dec,ST_Reset} ST_State;

unsigned char buttonPressed(unsigned char tmpA, unsigned char tmpC)
{
	switch(ST_State){ //Transitions
		
		case ST_SMStart: // // Initial transition
		ST_State = ST_Inital;
		break;
		
		case ST_Inital:
		ST_State = ST_PressOff;
		break;
		
		case ST_PressOff:
			if(tmpA == 0x01)
			{
				ST_State = ST_Inc;
			}
			else if(tmpA == 0x02)
			{
				ST_State = ST_Dec;
			}
			else if(tmpA == 0x03)
			{
				ST_State = ST_Reset;
			}
			break;
		
		case ST_Idle:
			if(tmpA == 0x00)
			{
				ST_State = ST_PressOff;
			}
			else if(tmpA == 0x03)
			{
				ST_State = ST_Reset;
			}
			else
			{
				ST_State = ST_Idle;
			}
			break;
		
		case ST_Inc:
			if(tmpA == 0x01)
			{
				ST_State = ST_Idle;
			}
			else if(tmpA == 0x02)
			{
				ST_State = ST_Dec;
			}
			else if (tmpA == 0x03)
			{
				ST_State = ST_Reset;
			}
			break;
		
		case ST_Dec:
			if(tmpA == 0x01)
			{
				ST_State = ST_Inc;
			}
			else if(tmpA == 0x02)
			{
				ST_State = ST_Idle;
			}
			else if (tmpA == 0x03)
			{
				ST_State = ST_Reset;
			}
			break;
		
		
		case ST_Reset:
		ST_State = ST_PressOff;
		break;
		
		default:
		ST_State = ST_Inital;
		break;
		
	}//Transitions
	
	switch(ST_State){ // State Actions
		case ST_Inital:
			tmpC = 0x07;
			break;

		case ST_PressOff:
		break;
		
		case ST_Idle:
			break;
			
		case ST_Inc:
			if(PORTC < 9)
			{tmpC++;}
			break;
			
		case ST_Dec:
			if(PORTC>0)
			{tmpC--;}
			break;

		case ST_Reset:
			tmpC = 0x00;
			break;
			
		default:
		break;
		
		
	}//State Actions
	return tmpC;
}

int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;
	
	while(1)
	{
		tmpA = PINA & 0xFF;
		tmpC = buttonPressed(tmpA, tmpC);
		PORTC = tmpC;
	}
	
	return 0;
}