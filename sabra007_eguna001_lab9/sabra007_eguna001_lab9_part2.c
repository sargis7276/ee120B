/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 9 Exercise 2
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 */



#include <avr/io.h>

void set_PWM(double frequency) {
	// Keeps track of the currently set frequency
	// Will only update the registers when the frequency
	// changes, plays music uninterrupted.
	static double current_frequency;
	if (frequency != current_frequency) {

		if (!frequency) TCCR3B &= 0x08; //stops timer/counter
		else TCCR3B |= 0x03; // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) OCR3A = 0xFFFF;
		
		// prevents OCR3A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) OCR3A = 0x0000;
		
		// set OCR3A based on desired frequency
		else OCR3A = (short)(8000000 / (128 * frequency)) - 1;

		TCNT3 = 0; // resets counter
		current_frequency = frequency;
	}
}
void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}
void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}




enum States { Init, Off, On, Inc, Inc2, Dec, Dec2 } state;
unsigned char tmpA;
unsigned char tmpB;
const double Notes[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

void Tick() {
	
	// State Transitions
	switch (state) {
		case Init:
			state = Off;
		break;
		case Off:
		if(tmpA < 4)
		{
			state = Off;
		}
		else
		{
			state = On;
		}
		break;
		case On:
			if(tmpA == 4)
			{
				state = On;
			}
			else if (tmpA == 5)
			{
				state = Inc;
			}
			else if (tmpA == 6)
			{
				state = Dec;
			}
			else
			{
				state = Off;
			}
		break;
		case Inc:
			if (tmpA == 5)
			{
				state = Inc2;
			}
			else
			{
				state = On;
			}
		break;
		case Inc2:
			if (tmpA == 5)
			{
				state = Inc2;
			}
			else
			{
				state = On;
			}
		break;
		case Dec:
			if(tmpA == 6)
			{
				state = Dec2;
			}
			else
			{
				state = On;
			}
		break;
		case Dec2:
			if (tmpA == 6)
			{
				state = Dec2;
			}
			else
			{
				state = On;
			}
			break;
		
		default:
			state = Init;
		break;
	}

	// State Actions
	switch (state) {
		case Init:
		break;
		case Off:
			set_PWM(0);
		break;

		case On:

			if (tmpA == 4)
			{
				set_PWM(Notes[tmpB]);
			}
			else
			{
				set_PWM(0);
			}
		break;

		case Inc:
			if (tmpB < 7)
			{
				++tmpB;
			}
		break;

		case Inc2:
		break;

		case Dec:
		if (tmpB > 0)
		{
			--tmpB;
		}
		break;

		case Dec2:
		break;

		default:
		break;
	}

}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	PWM_on();
	state = Init;
	tmpB = 0;

	while(1)
	{
		tmpA = ~PINA & 0x07;
		Tick();
	}
}