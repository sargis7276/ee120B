/*
 *
 * Sargis Abrahamyan sabra007@ucr.edu
 * Enrico Gunawan eguna001@ucr.edu
 * Lab section: B21
 * Assignment: Lab 7 Exercise 2
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {

	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;

	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;

	SREG |= 0x80;
}
void TimerOff() {
	TCCR1B = 0x00;
}
void TimerISR() {
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect) {

	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}


//Global variables

unsigned char threeLEDs;
unsigned char blinkingLED;
unsigned char tmpB;


enum SM_1_states { s1, s2, s3} SM_1_state;

void tickFuncSM_1(){

	switch(SM_1_state){// State Transitions

		case s1:
		SM_1_state = s2;
		break;

		case s2:
		SM_1_state = s3;
		break;

		case s3:
		SM_1_state = s1;
		break;
		default:
		SM_1_state = s1;
		break;
	}// State Transitions

	switch(SM_1_state){// State Actions

		case s1:
		threeLEDs = 0x01;
		break;

		case s2:
		threeLEDs = 0x02;
		break;

		case s3:
		threeLEDs = 0x04;
		break;

		default:
		break;
	}// State Actions

}

enum SM_2_states {s4, s5} SM_2_state;

void tickFuncSM_2(){

	switch(SM_2_state){
		case s4:
		SM_2_state = s5;
		break;

		case s5:
		SM_2_state = s4;
		break;
		default:
		SM_2_state = s4;
		break;

	}
	switch(SM_2_state){
		case s4:
		blinkingLED = 0x08;
		break;

		case s5:
		blinkingLED = 0x00;
		break;
		default:
		break;

	}
}

enum SM_3_states {s6} SM_3_state;

void tickFuncSM_3(){
	switch(SM_3_state){
		case s6:
		SM_3_state = s6;
		break;

		default:
		SM_3_state = s6;
		break;
	}

	switch(SM_3_state){

		case s6:
		tmpB = threeLEDs + blinkingLED;
		break;

		default:
		break;
	}
	PORTB = tmpB;
}


int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;

	unsigned long SM1_elapsedTime = 300;
	unsigned long SM2_elapsedTime =	1000;
	const unsigned long timerPeriod = 100;


	TimerSet(timerPeriod);
	TimerOn();

	SM_1_state = s1;
	SM_2_state = s4;

	while(1)
	{
		if(SM1_elapsedTime >= 300)
		{
			tickFuncSM_1();
			SM1_elapsedTime = 0;
		}
		if (SM2_elapsedTime >= 1000)
		{
			tickFuncSM_2();
			SM2_elapsedTime = 0;
		}
		tickFuncSM_3();
		while (!TimerFlag);
		TimerFlag = 0;
		SM1_elapsedTime += timerPeriod;
		SM2_elapsedTime += timerPeriod;
	}
}

