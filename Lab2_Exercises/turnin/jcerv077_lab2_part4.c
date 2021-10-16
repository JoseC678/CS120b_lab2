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
    DDRC = 0x00; PORTC = 0xFF; //Configure port A's pins as inputs
    DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 

    unsigned char tempA = 0x00;
    unsigned char tempB = 0x00;
    unsigned char tempC = 0x00;
    unsigned char PD_0 = 0x00;
    unsigned char PD_1 = 0x00;
    unsigned char totalW = 0x00;
    //unsigned char placeHolder = 0x00;



    while(1) {
        tempA = PINA;
        tempB = PINB;
        tempC = PINC;
        
        totalW = tempA + tempB + tempC;
        PD_0 = 0x00;
        PD_1 = 0x00;

        if(totalW > 140){
            //totalW = 10;
            PD_0 = 0x01;
        }else{
            PD_0 = 0x00;
        }
        
        if(tempA > tempC){
            if((tempA - tempC) > 80 ){
                PD_1 = 0x02;
            }
        
        }else{
            if((tempC - tempA) > 80 ){
                PD_1 = 0x02;
            }
        }

        //placeHolder = 0x00;

        PORTD = (totalW>>2) | (PD_1) | PD_0;
	if(tempB==56){PORTD =PORTD -1;}
        //PORTD = (PD_0);
    }
    

    
	return 0;
}

