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
    DDRB = 0x00; PORTB = 0xFF; //Configure port A's pins as inputs
    DDRC = 0xFF; PORTC = 0x00; //Configure port A's pins as inputs
    //DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 


    unsigned char tempA = 0x00;
    unsigned char tempB = 0x00;
    //unsigned char significant_bit = 0x00;
    unsigned char total = 0x00;
    unsigned char i = 0x00;




    while(1) {
        tempA= PINA & 0xFF;
        tempB= PINB & 0xFF;

        total =0x00; //reset the count
        
        //Cycle through each of the seven bits
        for(i = 0; i<=7; i++){
            
            //if the MSB is a 1 one than increment the count and than shift that bit to the left
            if( tempA & 0x80 ){ 
                total++;
            }

            //if the MSB is a 1 one than increment the count and than shift that bit to the left
            if( tempB & 0x80 ){
                total++;
            }
            tempA = tempA<<1; //shift to the left one
            tempB = tempB<<1; //shift to the left one
        }

        PORTC = total;
    } 

    
	return 0;
}

