/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 2 Exercise 1
 *
 * I acknowledge all content contained herein, excluding temlpate or example
 * code, is my own original work.
 *
 */

#include <avr/io.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char count = 0x00;
	unsigned char i;

    while(1)
    {
		tmpA = PINA & 0xFF;
		tmpB = PINB & 0xFF;
		count = 0x00;
		for(i=0; i<8; i++) {
			if (GetBit(tmpA, i)) {
				count++;
			}
			if(GetBit(tmpB, i)){
				count++;
			}
		}
		PORTC = count;
	}

	return 0;
}
