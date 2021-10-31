/*	Author: Jose Cervantes
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
    /* Insert DDR and PORT initializations */
    //DDRA = 0x00; PORTA = 0xFF;
    //DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00; //Configure port A's pins as outputs 
    //DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 
    
    /* Insert your solution below */
    while (1) {

         //PORTC = 0b110001; //11
         //PORTC = 0b101001; //12
         //PORTC = 0b011001; //13
         
         //PORTC = 0b110010; //21
         //PORTC = 0b101010; //22
         //PORTC = 0b011010; //23

          //PORTC = 0b110100; //31
         //PORTC = 0b101100; //32
           PORTC = 0b011100; //33
         

    }
    return 1;
}
