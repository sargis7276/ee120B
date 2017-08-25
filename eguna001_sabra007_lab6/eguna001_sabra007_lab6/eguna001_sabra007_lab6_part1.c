/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 6 Exercise 1
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 */

#include <avr/io.h>
#include "io.c"
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks
void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}
void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}
void TimerISR() {
	TimerFlag = 1;
}
// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}


unsigned char tmpB;
unsigned char tmpA;

enum SM1_States { SM1_start, SM1_initial, SM1_idle, SM1_inc, SM1_dec, SM1_reset } SM1_State;

void Tick(unsigned char column) {
	switch(SM1_State) { // Transitions
		case SM1_start:
			SM1_State = SM1_initial;
		break;
		case SM1_initial:
				SM1_State = SM1_idle;
		break;
		case SM1_idle:
			if (tmpA == 0x03) {
				SM1_State = SM1_reset;
			}
			else if (tmpA == 0x01) {
				SM1_State = SM1_inc;
			}
			else if (tmpA == 0x02) {
				SM1_State = SM1_dec;
			}
			break;
		case SM1_inc:
			if (tmpA == 0x03) {
				SM1_State = SM1_reset;
			}
			else if (1) {
				SM1_State = SM1_idle;
			}
			break;
		case SM1_dec:
			if (tmpA == 0x03) {
				SM1_State = SM1_reset;
			}
			else if (1) {
				SM1_State = SM1_idle;
			}
			break;
		case SM1_reset:
			if (1) {
				SM1_State = SM1_idle;
			}
			break;
		default:
		SM1_State = SM1_start;
	} // Transitions

	switch(SM1_State) { // State actions
		case SM1_start:
		break;
		case SM1_initial:
			tmpB=0x00;
		break;
		case SM1_idle:
		LCD_Cursor(column);
		 LCD_WriteData(tmpB +'0');
		 LCD_Cursor(++column);
		break;
		case SM1_inc:
			if(tmpB<9)
			{
				tmpB++;
			}
		break;
		case SM1_dec:
			if(tmpB)
			{
				tmpB--;
			}
		
		break;
		case SM1_reset:
			tmpB=0x00;
		break;
		default: // ADD default behaviour below
		break;
	} // State actions

}
int main(void)
{
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	DDRA = 0x00; PORTA = 0xFF;

	TimerSet(500);
	TimerOn();

	SM1_State = SM1_start;
	// Initializes the LCD display
	LCD_init();
	
	// Starting at position 1 on the LCD screen, writes Hello World
	
	
	while(1) {
		tmpA = ~PINA & 0x03;
		Tick(1);
				
				//LCD_ClearScreen();

		while (!TimerFlag);
		TimerFlag = 0;

	
		
	}
	
}
