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
#include <stdbool.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
int main(void) {
	//Set the proper inputs and outputs
    DDRA = 0x00; PORTA = 0xFF; //Configure port A's pins as inputs
    DDRB = 0x00; PORTB = 0xFF; //Configure port A's pins as inputs
    DDRC = 0xFF; PORTC = 0x00; //Configure port A's pins as inputs
    //DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 


    unsigned char A_upperNibble = 0x00;
    unsigned char A_lowerNibble = 0x00;
    //unsigned char C_upperNibble = 0x00;
    //unsigned char B_lowerNibble = 0x00;


    while(1) {
        A_upperNibble = PINA & 0xF0; //Take the upper Nibble
        A_lowerNibble = PINA & 0x0F; //Take the Lower Nibble


        PORTC = (A_lowerNibble << 4); // Shift it to the upper nibble of PORTC
        PORTB = (A_upperNibble >> 4); // Shift it to the lower nibble of PORTB


    } 

    
	return 0;
}

