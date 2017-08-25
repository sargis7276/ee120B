/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 2 Exercise 2 & 3
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

	unsigned char tmpA = 0x00;
	unsigned char tmpAa = 0x00;

    while(1)
    {
		tmpA = PINA & 0x0F;
		tmpAa = PINA & 0x7F;
		if(tmpA == 1 || tmpA == 2)
		{
			PORTC = 0x20;
		}
		else if(tmpA == 3 || tmpA == 4)
		{
			PORTC = 0x30;
		}
		else if(tmpA == 5 || tmpA == 6)
		{
			PORTC = 0x38;
		}
		else if(tmpA == 7 || tmpA == 8 || tmpA == 9)
		{
			PORTC = 0x3C;
		}
		else if(tmpA == 10 || tmpA == 11 || tmpA == 12)
		{
			PORTC = 0x3E;
		}
		else
		{
			PORTC = 0x3F;
		}
		if((GetBit(tmpAa,4) && GetBit(tmpAa,5)) && !GetBit(tmpAa,6))
		{
			PORTC = SetBit(PORTC, 7, 1);
		}

	}

	return 0;
}
