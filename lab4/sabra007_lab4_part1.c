/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 4 Exercise 1
 *
 * I acknowledge all content contained herein, excluding temlpate or example
 * code, is my own original work.
 *
 */

#include <avr/io.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;
	//unsigned char tmpAa = 0x00;

    while(1)
    {
	
		tmpA = ~PINA & 0x0F;
		
		if(tmpA == 0)
		{
			tmpC = 0x00;
		}
		if(tmpA == 0x01 || tmpA == 0x02)
		{
			tmpC = 0x60;
		}
		else if(tmpA == 0x03 || tmpA == 0x04)
		{
			tmpC = 0x70;
		}
		else if(tmpA == 0x05 || tmpA == 0x06)
		{
			tmpC = 0x38;
		}
		else if(tmpA == 0x07 || tmpA == 0x08 || tmpA == 0x09)
		{
			tmpC = 0x3C;
		}
		else if(tmpA == 0x0A || tmpA == 0x0B || tmpA == 0x0C)
		{
			tmpC = 0x3E;
		}
		else if(tmpA == 0x0D || tmpA == 0x0E || tmpA == 0x0F)
		{
			tmpC = 0x3F;
		}
		PORTC = tmpC;
		
		
	}

	return 0;
}
