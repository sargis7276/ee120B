/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 8 Exercise 2
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
		unsigned short x = ADC;

		tmpB = (char)x;
		tmpD = (char)(x >> 8);



		PORTB = tmpB;
		PORTD = tmpD;

    }
}

