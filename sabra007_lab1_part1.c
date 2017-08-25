/*
 * sabra007_lab1_part1.c
 *
 * Created: 7/31/2017 1:52:45 PM
 *  Author: Enrico Gunawan and Sargis Abrahamyan
 */ 


#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char tmpB = 0x00;
	unsigned char tmpA = 0x00;
    while(1)
    {
		tmpA = PINA & 0x03;
		if (tmpA == 0x01) {
			tmpB = 0x01;
		}
		else {
			tmpB = 0x00;
		}
		PORTB = tmpB;
	}
	
	return 0;
}