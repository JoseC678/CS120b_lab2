/*	Author: Jose Cervantes jcerv077@gmail.com
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"

#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif




enum States{start_point,wait, PA0_press, PA1_press,reset_press, reset_wait ,PA0_wait,PA1_wait, increment_one} state;
unsigned char TOTAL; 
unsigned char button;
unsigned char hold;

unsigned char new_value;
unsigned char current_score;

volatile unsigned char TimerFlag = 0; //TimerISR() sets this to 1. C programmer should clear to 0.
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;


void TimerOn(){
    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;
    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0x80;

}
void TimerOff(){ TCCR1B = 0x00;}
void TimerISR(){ TimerFlag = 1;}

ISR(TIMER1_COMPA_vect){
    _avr_timer_cntcurr--;  //Count down to 0 rahter than up to TOP
    if (_avr_timer_cntcurr == 0){ //results in a more efficient compare
        TimerISR();   //Call the ISR that the user uses
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

void tick(){
    button = 0x00;
    button = ~PINA;

	button = button & 0x03;
    
    switch(state){
        case start_point: 
            state = wait;
            hold =0x00;
            current_score = TOTAL;
            new_value = 0;
            break;

        case wait:
            if(button == 0x01){
                state = PA0_press; //Go to the press PA0 state in the next switch and add 1.
            }
            else if(button == 0x02){
                state = PA1_press; //Go to the press PA1 state in the next switch and add 1.
            }
            else if(button == 0x03){
                state = reset_press;//Go to the reset_press state and reset TOTAL to zero
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
                   //     hold++;
                ///if(hold == 0x0A){
                   // state = increment_one;
                 //   hold = 0x00;
               // }else{

        case PA0_wait:
            if(button == 0x01){
                
                hold++;
                if(hold >= 0x0A){
                    state = PA0_press;
                    hold = 0x00;
                }else{

                state = PA0_wait; //Continue in this state until a new value is entered.
                }
            }else{
                if(button == 0x01){
                    state = PA0_press; //Go to the press PA0 state in the next switch and add 1.
                }
                else if(button == 0x02){
                    state = PA1_press; //Go to the press PA1 state in the next switch and add 1.
                }
                else if(button == 0x03){
                    state = reset_press;//Go to the reset_press state and reset TOTAL to zero
                }else{
                    state = wait; //if unkown value stay in wait until valid value is entered.
                }
            }
            break;
        
        case PA1_press:
            if(button == 0x02){
                state = PA1_wait; //Go to PA0_wait because in order to increment again PINA has  
                                  //to be a new value
            }else{
                state = wait;
            }
            break;

        case PA1_wait:
            if(button == 0x02){
           
                
                hold++;
                if(hold >= 0x0A){
                    state = PA1_press;
                    hold = 0x00;
                }else{

                state = PA1_wait; //Continue in this state until a new value is entered.
                }

            }else{
                if(button == 0x01){
                    state = PA0_press; //Go to the press PA0 state in the next switch and add 1.
                }
                else if(button == 0x02){
                    state = PA1_press; //Go to the press PA1 state in the next switch and add 1.
                }
                else if(button == 0x03){
                    state = reset_press;//Go to the reset_press state and reset TOTAL to zero
                }else{
                    state = wait; //if unkown value stay in wait until valid value is entered.
                }
            }
            break;

        case reset_press:
            if(button == 0x03){
                state = reset_wait;
            }else{
                state = wait;
            }
            break;
        
        case reset_wait:
            if(button == 0x03){
                state = reset_wait;
            }else{
                if(button == 0x01){
                    state = PA0_press; //Go to the press PA0 state in the next switch and add 1.
                }
                else if(button == 0x02){
                    state = PA1_press; //Go to the press PA1 state in the next switch and add 1.
                }
                else if(button == 0x03){
                    state = reset_press;//Go to the reset_press state and reset TOTAL to zero
                }else{
                    state = wait; //if unkown value stay in wait until valid value is entered.
                }
            }

        
        default:
            //error
            //PORTC=0xFF;
            break; 


    } 


    switch(state){

            

        case PA0_press:
            if(TOTAL == 0x09){
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

        

        case PA1_press:
            if(TOTAL == 0x00){
                //Do nothing
             //   state = wait;
               // button = 0x00;
            }
            else{
                TOTAL--;
             //   state = wait;
               // button = 0x00;
            }
            break;
        
        case reset_press:
            TOTAL = 0x00;
           // state = wait;
            break;
        
        default:
            //error
            //PORTC=0xFF;
            break;
    }

    if(current_score == TOTAL){
        //do nothing
    }
    else{
        current_score = TOTAL;
        LCD_WriteData_once( TOTAL +'0');
    }

}




int main(void) {
       	//Set the proper inputs and outputs
    DDRA = 0x00; PORTA = 0xFF; //Configure port A's pins as inputs
   // DDRB = 0xFF; PORTB = 0x00; //Configure port A's pins as inputs
    DDRC = 0xFF; PORTC = 0x00; //Configure port C's pins as outputs
     DDRB = 0xFF; PORTB = 0x00; //Configure port C's pins as outputs
    DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 
    //Initialize the starting point
    state = start_point;

    TOTAL = 0x00; //initialize to 0x07
    PORTB = 0x00; //Starting point is 7
    
    TimerSet(100);
    TimerOn();



    //Initializes the LCD display
    LCD_init();

        LCD_WriteData_once( 0x00 +'0');



    /* Insert your solution below */
    while (1) {
                tick();
        while (!TimerFlag){};
        TimerFlag = 0;
//
    }
    return 1;
}
