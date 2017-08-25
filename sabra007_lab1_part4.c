/*
 * sabra007_lab_part3.c
 *
 * Created: 7/31/2017 1:52:45 PM
 *  Author: Enrico Gunawan and Sargis Abrahamyan
 */


#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRD = 0x00; PORTD = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char tmpSum = 0x00;
	unsigned char tmpAminusC = 0x00;
	unsigned char tmpApprox = 0x00;

    while(1)
    {
		PORTC = 0x00;
		tmpSum = 0x00;
		tmpAminusC = 0x00;
		tmpApprox = 0x00;

	    tmpA = PINA & 0xFF;
	    tmpB = PINB & 0xFF;
	    tmpC = PIND & 0xFF;

		tmpAminusC = tmpA - tmpC;
		tmpSum = tmpA + tmpB + tmpC;

		if (tmpSum > 140) {
			PORTD=C = 0x01;
		}

		if (tmpAminusC > 80) {
			PORTC = 0x02;
		}

		tmpApprox = (tmpSum & 0xFC) | PORTC;
		PORTC = tmpApprox;
	}

	return 0;
}

