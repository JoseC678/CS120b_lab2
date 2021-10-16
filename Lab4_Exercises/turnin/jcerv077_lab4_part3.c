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

//# = 0x43
//X = 0x58
//Y = 0x59

enum States{start_point, init , press_PA2, release_PA2,  press_PA1, press_PA1hold, PINA7_press} state;
unsigned char TOTAL; 
unsigned char button;
//bool hashtag_Set;


void tick(){
    button = PINA & 0x87;
    
    //PORTC = button;

    switch(state){
        case start_point:
            state = init;
            //hashtag_Set = false;
            break;
        
        case init:
        //PORTC = button;
            if(button == 0x04){
                state = press_PA2;
                //PORTC = 0x07;
                
            }else if(button == 0x08){
                state = PINA7_press;
            }
            else
            {
                state = init;
                
            }
            break;

        case press_PA2:
            if(button == 0x04){
                state = press_PA2;
                //PORTC = 0x07;
            }
            else if(button == 0x00){
                state = release_PA2;
            }else{
                state = init;
            }
            break;

        case release_PA2:
            if(button == 0x02)
            {
                state = press_PA1;
               // PORTB = 0x01;
                 
            }else if(button == 0x00)
            {
                //PORTB = 0x01;
                state = release_PA2;
                //PORTC = 0x07;
                

            }else{
                state = init;
            }
            break;

        case press_PA1:
            if(button == 0x02 || button ==0x00)
            {
                state = press_PA1hold;
                //PORTC = 0x07;
                
            }
            else{
                state = init;
            }
            //PORTC = button;

            break;

        case press_PA1hold:
            if(button == 0x02 || button == 0x00)
            {
                state = press_PA1hold;
                // PORTC = 0x07;

            }else
            {
                state = init;
            }
            break;

        case PINA7_press:
            if(button == 0x80)
            {
                state = PINA7_press;
            }else
            {
                state = init;
            }

        default:
            break; 


    } 


    switch(state){
        case press_PA1hold:
            PORTB = 0x01;
            break;
        case init:
            PORTB = 0x00;
            break;
        case PINA7_press:
            PORTB = 0x00;
            break;
        
        default:
            break;
    }


}

int main(void) {
    	//Set the proper inputs and outputs
    DDRA = 0x00; PORTA = 0xFF; //Configure port A's pins as inputs
    DDRB = 0xFF; PORTB = 0x00; //Configure port A's pins as inputs
    //DDRC = 0xFF; PORTC = 0x00; //Configure port C's pins as outputs
    //DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 
    
    //Initialize the starting point
    state = init;

    /* Insert your solution below */
    while (1) {
        tick();
        

    }
}