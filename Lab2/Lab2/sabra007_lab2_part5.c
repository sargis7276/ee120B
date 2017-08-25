/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 2 Exercise 5
 *
 * I acknowledge all content contained herein, excluding temlpate or example
 * code, is my own original work.
 *
 */
#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

int main(void)
{
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFE; PORTB = 0x01;

	unsigned char tmpB = 0x00;
	unsigned short weight = 0x0000;

    while(1)
    {
		tmpB = PINB & 0x01;
		weight = PIND & 0xFF;
		weight = weight << 1;

		weight = weight | tmpB;

       if(weight > 70)
	   {
		  PORTB = SetBit(PORTB, 1, 1);
	   }
	   else if (weight > 5 && weight <= 70 )
	   {
		    PORTB = SetBit(PORTB, 2, 1);
			PORTB = SetBit(PORTB, 1, 0);
	   }
    }
	return 0;
}