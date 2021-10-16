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
    //DDRA = 0x00; PORTA = 0xFF; //Configure port A's pins as inputs
    DDRB = 0xFE; PORTB = 0x01; //Configure port B2 & B3 bit 's pins as outputs
                               //And configure B0 as inputs
    //DDRC = 0xFF; PORTC = 0x00; //Configure port A's pins as inputs
    DDRD = 0x00; PORTD = 0xFF; //Configure port D's pins as D7-D0 as inputs 


    unsigned char totalWeight = 0x00;
    unsigned char B_bits = 0x00;
    unsigned char D_bits = 0x00;


    while(1) {
        B_bits = PINB & 0x01;//get B0
        D_bits = PIND & 0xFF; //get bits D7 - D0

        totalWeight = ((D_bits<<1) | B_bits);
        
        if(D_bits >= 128){//overFlow of bits
            PORTB = 0x02;
        }else{
            if(totalWeight >= 70){
                PORTB = 0x02;
            }else if( totalWeight < 70 && totalWeight > 5){
                PORTB = 0x04;
            }else{
                PORTB = 0x00;
            }
        }



        //PORTB = D_bits;
    } 

    
	return 0;
}

