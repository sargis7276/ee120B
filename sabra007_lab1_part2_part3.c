/*
 * sabra007_lab_part3.c
 *
 * Created: 7/31/2017 1:52:45 PM
 *  Author: Enrico Gunawan and Sargis Abrahamyan
 */


#include <avr/io.h>

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	//unsigned char tmpB = 0x00;
	unsigned char tmpA = 0x00;
	unsigned char cntavail = 0x00;
	unsigned char i;

    while(1)
    {
		tmpA = PINA & 0x0F;
		cntavail = 0x00;
		for(i=0; i<4; i++) {
			if (GetBit(tmpA, i)) {
				cntavail++;
			}
		}

		PORTC = cntavail;

		if (cntavail == 4) {
			PORTC += 0x80;
		}
	}

	return 0;
}

