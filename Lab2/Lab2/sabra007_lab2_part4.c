/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 2 Exercise 3
 *
 * I acknowledge all content contained herein, excluding temlpate or example
 * code, is my own original work.
 *
 */

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char tmpA = 0x00;

    while(1)
    {
		tmpA = PINA & 0xFF;

		PORTC = tmpA << 4;
		PORTB = tmpA >> 4;

    }
}