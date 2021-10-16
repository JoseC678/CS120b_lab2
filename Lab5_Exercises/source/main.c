/*	Author: lab
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
    //DDRB = 0x00; PORTB = 0xFF; //Configure port A's pins as inputs
    DDRC = 0xFF; PORTC = 0x00; //Configure port A's pins as inputs
    //DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 


    unsigned char tempA = 0x00;
    //unsigned char tempB = 0x00;
    unsigned char fuel_LED = 0x00;

    while(1) {
        tempA = ~PINA;
		tempA = tempA & 0x0F;

		
        if(tempA == 0x00){
            fuel_LED = 0x40;
        }
        else if(tempA <=0x02 ){//Check if fuel below or equal to 2
            fuel_LED = 0x60;
        }
        else if(tempA <= 0x04){//Check if fuel below or equal to 4
            fuel_LED = 0x70;
        }
        else if(tempA <= 0x06){//Check if fuel below or equal to 6
            fuel_LED = 0x38;
        }
        else if(tempA <= 0x09){//Check if fuel below or equal to 9
            fuel_LED = 0x3C;
        }
        else if(tempA <= 0x0C){//Check if fuel below or equal to 12
            fuel_LED = 0x3E;
        }else{
			fuel_LED = 0x3F;
		}


        PORTC = fuel_LED;
    } 

    
	return 1;
}

