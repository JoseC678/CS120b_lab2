/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 * Demo Link: https://www.youtube.com/watch?v=H_tDDIZYmgE
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States{start_point,wait, PA0_press, PA1_press,reset_press, reset_wait ,PA0_wait,PA1_wait} state;
unsigned char TOTAL; 
unsigned char ORDER[]= {0x00, 0x01, 0x05,0x15, 0x02, 0x0A, 0x2A, 0x3F};
unsigned char button;

void tick(){
    button = 0x00;
    button = ~PINA;

	button = button & 0x03;
    
    switch(state){
        case start_point: 
            state = wait;
            break;

        case wait:
            if(button == 0x01){
                state = PA0_press; //Go to the press PA0 state in the next switch and add 1.
            }else{
                state = wait; //if unkown value stay in wait until valid value is entered.
            }
            break;

        case PA0_press:
            if(button == 0x01){
                state = PA0_wait; //Go to PA0_wait because in order to increment again PINA has  
                                  //to be a new value
            }else{
                state = wait;
            }
            break;

        case PA0_wait:
            if(button == 0x01){
                state = PA0_wait; //Continue in this state until a new value is entered.
            }else{
                if(button == 0x01){
                    state = PA0_press; //Go to the press PA0 state in the next switch and add 1.
                }else{
                    state = wait; //if unkown value stay in wait until valid value is entered.
                }
            }
            break;


        


        
        default:
            //error
            //PORTC=0xFF;
            break; 


    } 


    switch(state){
        case PA0_press:
            if(TOTAL == 0x07){
                TOTAL = 0;

                //Do nothing
              //  state = wait;
            //    button = 0x00;
            }
            else{
                TOTAL++;
              //  state = wait;
                //button = 0x00;
            }
        break;

        
        default:
            //error
            //PORTC=0xFF;
            break;
    }

    PORTB = ORDER[TOTAL];

}

int main(void) {
    	//Set the proper inputs and outputs
    DDRA = 0x00; PORTA = 0xFF; //Configure port A's pins as inputs
   // DDRB = 0xFF; PORTB = 0x00; //Configure port A's pins as inputs
    DDRB = 0xFF; PORTB = 0x00; //Configure port C's pins as outputs
    //DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 
    
    //Initialize the starting point
    state = start_point;
    TOTAL = 0x00; //initialize to 0x07
    PORTB = 0x07; //Starting point is 7

    /* Insert your solution below */
    while (1) {
        tick();
        

    }

}