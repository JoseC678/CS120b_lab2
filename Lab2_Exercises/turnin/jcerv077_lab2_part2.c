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
    DDRC = 0xFF; PORTC = 0x00; //Configure port A's pins as outputs 
    unsigned char cntvail = 0x00;
    unsigned char temp = 0x00;


    while(1) {
        temp = PINA & 0x0F;
        cntvail = 0x00;

        //Check for 4 spots full
        if(temp == 0x0F){ 
            cntvail = 0x00;

        //Check for 3 spots full
        }else if(temp == 0x07 || temp == 0x0B || temp == 0x0D || temp == 0x0E){
            cntvail = 0x01;

        //Check for 2 spots full
        }else if(temp == 0x03 || temp == 0x05 || temp == 0x06 || temp == 0x09|| temp == 0x0A|| temp == 0x0C){
            cntvail = 0x02;

        //Check for 1 spots full
        }else if(temp == 0x01|| temp == 0x02|| temp == 0x04|| temp == 0x08){
            cntvail = 0x03;

        //Check for 0 spots full
        }else{
            cntvail = 0x04;
        }

        //Assign to PORTC
        PORTC = cntvail;
    }
    

		
	return 0;
}

