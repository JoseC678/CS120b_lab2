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

enum States{start_point, PB0_press, PB1_press,PB0_release,PB1_release} state;

void tick(){
    unsigned char button = 0x00;
    button = 0x00;

    //PORTB = 0x00;
    button = PINA & 0x01;
    
    switch(state){
        case start_point:
            state = PB0_release;
            PORTB = 0x01;
            break;
        
        case PB0_release:
            if(button == 0x00){
                state = PB0_release;
                PORTB = 0x01;
                
            }else{
                state = PB1_press;
                PORTB = 0x02;
            }
            
            break;

        case PB0_press:
            if(button){
                state = PB0_press;
                PORTB = 0x01;
            }else{
                state = PB0_release;
            }
            break;

        case PB1_press:
            if(button){
                state = PB1_press;
                PORTB = 0x02;
            }else{
                state = PB1_release;
                PORTB = 0x02;
                
            }
            break;

        case PB1_release:
            if(!button){
                state = PB1_release;
                PORTB = 0x02;
            }else{
                state = PB0_press;
                PORTB = 0x01;
            }
            break;

        default:
            state = start_point;
            break; 


    } 

}

int main(void) {
    	//Set the proper inputs and outputs
    DDRA = 0x00; PORTA = 0xFF; //Configure port A's pins as inputs
    DDRB = 0xFF; PORTB = 0x00; //Configure port A's pins as inputs
    //DDRC = 0xFF; PORTC = 0x00; //Configure port A's pins as inputs
    //DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 
    
    //Initialize the starting point
    state = start_point;


    /* Insert your solution below */
    while (1) {
        tick();
        

    }
}
