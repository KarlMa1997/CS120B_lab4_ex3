/*	Author: kma023
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states {start, lock, press, release, unlock} states;

void sm() {
	unsigned char x = (PINA & 0x01);
	unsigned char y = (PINA & 0x02);
	unsigned char p = (PINA & 0x04);
	unsigned char plocked =  (PINA & 0x80);

	switch(states) {
		case start:
			states = lock;
			break;
		case lock:
			if(p && !x && !y && !plocked) {
				states = press;
			}
			else if(!p && !x && !y && plocked) {
				states = lock;
			}
			else {
				 states = lock;
			}
			break;

		case press:
			if(p && !x && !y && !plocked) {
				states = press;
			}
			else if(!p && !x && !y && plocked) {
				states = lock;
			}
			else if(!p && !x && !y && !plocked) {
				states = release;
			}
			else {
				states = press;
			}
			break;

		case release:
			if(!p && !x && !y && !plocked) {
				states = release;
			}
			else if(!p && !x && !y && plocked) {
				states = lock;
			}
			else if(!p && !x && y && !plocked) {
				states = unlock;
			}
			else {
				states = release;
			}
			break;
	
		case unlock:
			if(!p && !x && !y && plocked) {
				states = lock;
			}
			else {
				states = unlock;
			}
			break;
		default:
			states = lock;
			break;
	}

	switch(states) {
		case start:
		break;
		case lock:
			PORTB = 0x00;
			break;
		case unlock:
			PORTB = 0x01;
			break;
		case press:
			PORTB = 0x02;
			break;
		case release:
			PORTB = 0x03;
			break;
	}
	
}

int main(void) {

        DDRA = 0x00; PORTA = 0xFF;
        DDRB = 0xFF; PORTB = 0x00;
	states = start;
        while(1) {
                sm();
	}
	
	return 0;
}
