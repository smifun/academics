/*
 * lab2.c
 *
 * Created: 2014-11-22 13:24:46
 *  Author: Kamil Wójcik
 */ 

#include <avr/io.h> 
#include <avr/interrupt.h>

#define F_CPU 1000000UL
#include <util/delay.h>

void init(void);
void showDigit(void);

uint8_t timeCounter = 0;
uint8_t timeCounterLimit = 61;
uint8_t digit = 0;

uint8_t digitValues[10];

ISR(INT0_vect){
	timeCounter --; // decrease time counter

	if (timeCounterLimit != 0){
		digit ++; //increase second digit
		digit = digit % 10; // reset digit if it reach 10
		timeCounter = timeCounterLimit; // reset time counter
	}
}

int main(void){
	TCCR0 |= 0x03; // set prescaler value to 64
	// by default timer is reset after overflow
	TIMSK = 0x01; // set interrupts from overflow (T0IE0=1)	
	timeCounter = timeCounterLimit;
	
	sei();

	//use PORT A to control display
	DDRA = 0xFF; // configure PORT A as output
	init();
	showDigit();
	
	while(1){
	}
 
}

void init(void){
	digitValues[0] = 0x3f;
	digitValues[1] = 0x06;
	digitValues[2] = 0x5b;
	digitValues[3] = 0x4f;
	digitValues[4] = 0x66;
	digitValues[5] = 0x6d;
	digitValues[6] = 0x7d;
	digitValues[7] = 0x07;
	digitValues[8] = 0x7f;
	digitValues[9] = 0x6f;
	
}
void showDigit(void){
	uint8_t dataValue = digitValues[digit];

	PORTA = 0x80 | dataValue;
}
