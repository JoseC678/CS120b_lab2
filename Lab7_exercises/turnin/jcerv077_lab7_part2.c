/*	Author: Jose Cervantes jcerv077@gmail.com
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Link: 
 */
#include <avr/io.h>
#include "io.h"

#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start_point, next_LED, PA0_press, PA0_press2} state;
unsigned char array[] = {0x01, 0x02, 0x04,0x02};
unsigned char i;
unsigned char TOTAL;
unsigned char current_score = 5;

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




    unsigned char tempA = 0x00;
    tempA = PINA;
    tempA = ~tempA;
    switch (state){
        case start_point:
            state = next_LED;
            i = 0;
            PORTB = 0x00;
            TOTAL = 5;
            break;

        case next_LED:

            if((tempA & 0x01) == 0x01){
                state = PA0_press;
            }else{
                state = next_LED;
            }
            break;


        case PA0_press:
            if((tempA & 0x01) ==0x01){
                state = PA0_press;
            }else{
                state = PA0_press2;
            }
            break;
        
        case PA0_press2:
            if((tempA & 0x01) ==0x01){
                if((tempA & 0x01) ==0x01 && current_score == 0x09){
                    current_score = 0x05;
                }
                state = start_point;
            }else{
                state = PA0_press2;
            }
            break;

        

        default:
            state = start_point;
            break;
    }

    switch(state){
        case start_point:
            break;
        case next_LED:
            if(i == 3){
                PORTB = array[i];

                i = 0x00;
            }
            else{
                PORTB = array[i];
                i++;
            }
            break;
        case PA0_press:

                state = PA0_press;
                PORTB = array[i];
            if(array[i] == 0x02){
                current_score++;
            }
            else{
                current_score--;
            }

                break;

        case PA0_press2:
            

                break;

         default:
            break;

    }



    if(current_score == 0x00){
        LCD_DisplayString(1, "");
        LCD_WriteData_once( current_score +'0');
    }
    else if(current_score == 0x01){
        LCD_DisplayString(1, "");
        LCD_WriteData_once( current_score +'0');

    }
    else if(current_score == 0x02){
        LCD_DisplayString(1, "");
        LCD_WriteData_once( current_score +'0');

    }
    else if(current_score == 0x03){
        LCD_DisplayString(1, "");
        LCD_WriteData_once( current_score +'0');

    }
    else if(current_score == 0x04){
        LCD_DisplayString(1, "");
        LCD_WriteData_once( current_score +'0');

    }
    else if(current_score == 0x05){
        LCD_DisplayString(1, "");
        LCD_WriteData_once( current_score +'0');

    }
    else if(current_score == 0x06){
        LCD_DisplayString(1, "");
        LCD_WriteData_once( current_score +'0');

    }
    else if(current_score == 0x07){
        LCD_DisplayString(1, "");
        LCD_WriteData_once( current_score +'0');

    }
    else if(current_score == 0x08){
        LCD_DisplayString(1, "");
       LCD_WriteData_once( current_score +'0');

    }
    else if(current_score == 0x09){
        LCD_DisplayString(1, "VICTORY");
    }

}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00; //Configure port A's pins as outputs 
    DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 
    
    TimerSet(300);
    TimerOn();
    
        //Initializes the LCD display
    LCD_init();

        LCD_WriteData_once( 0x05 +'0');

    /* Insert your solution below */
    while (1) {
        tick();
        while (!TimerFlag);
        TimerFlag = 0;
        //Note: For the above a better style would use a synchSM with TiickSM()
        //This example just illusstrates the use of  the ISR and flag

    }
    return 1;
}
