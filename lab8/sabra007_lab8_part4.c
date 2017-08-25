/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 8 Exercise 4
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 */

#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}


int main(void)
{
	

	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0x03; PORTD = 0xFC;
	DDRA = 0xFE; PORTA = 0x01;


	ADC_init();

	unsigned short x = 0;
	unsigned char tmpB = 0x00;
	unsigned char tmpD = 0x00;

	

	while (1)
	{
		x = ADC;

		
		if (x < 44)
			tmpB = 0x01;
		else if (x < 53)
			tmpB = 0x03;
		else if (x < 63)
			tmpB = 0x07;
		else if (x < 72)
			tmpB = 0x0F;
		else if (x < 82)
			tmpB = 0x1F;
		else if (x < 91)
			tmpB = 0x3F;
		else if (x < 101)
			tmpB = 0x7F;
		else
			tmpB = 0xFF;

		PORTB = tmpB;
		PORTD = tmpD;

	}
}

