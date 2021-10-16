/*	Author: jcerv077
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

int main(void) {
	//Set the proper inputs and outputs
    DDRA = 0x00; PORTA = 0xFF; //Configure port A's pins as inputs
    DDRB = 0xFF; PORTB = 0x00; //Configure port A's pins as outputs 

    unsigned char tempA = 0x00;
    unsigned char tempB = 0x00;

while(1) {
    tempA = PINA & 0x01;
    tempB = PINA & 0x02;
    if(tempA ==  0x01 && tempB == 0x00){
        PORTB = 0x01;
    }else{
        PORTB = 0x00;
    }
}

		
	return 0;
}

