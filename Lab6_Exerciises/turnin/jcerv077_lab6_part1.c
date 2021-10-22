/*	Author: Jose Cervantes jcerv077@gmail.com
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Link: 
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start_point, next_LED} state;
unsigned char array[] = {0x01, 0x02, 0x04};
unsigned char i;

volatile unsigned char TimerFlag = 0; //TimerISR() sets this to 1. C programmer should clear to 0.

///Internaal vaariiabbles foorr mmapping AVR's ISR  cleaerr TimerISR model.
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;


void TimerOn(){
    //AVR timer/counter controller register TCCR1
    TCCR1B = 0x0B; //bit3 = 0; CTC mode (clear timer on compppare)
                    //bit22bit1bit0 = 011: pre-scaler / 64 
                    //00001011: 0x0B
                    // SO, 8MHz clock or 8,000,000 /64 = 125,000 ticks/s
                    //Thus,e TCNTI register wil count at 125,000 ticks/s

    //AVR output compare register OCR1A
    OCR1A = 125; // Timer interrupt will be generated when TCNT1==OCR1A
                 // We want a 1 mas tick. 0.001 s * 125,000 tick/s = 125
                 //So when TCNT1 register equals 125,
                 // 1 ms has passed. Thus, we compare to 125
    //AVR timer interrupt mask register
    TIMSK1 = 0x02; //bit1: OCIE1A -- enables compaare match interrupt

    //initialize avr counter
    TCNT1 = 0;

    _avr_timer_cntcurr = _avr_timer_M;
    //TimerISR will be called every_avr_timer_cntcurr milliseconds

    //Enable global interrupts
    SREG |= 0x80; //0x80; 1000000

}

void TimerOff(){
    TCCR1B = 0x00;
}

void TimerISR(){
    TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect){
    //CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
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
    switch (state){
        case start_point:
            state = next_LED;
            i = 0;
            PORTB = 0x00;
            break;

        case next_LED:
            state = next_LED;
            break;

        default:
            state = start_point;
            break;
    }

    switch(state){
        case start_point:
            break;
        case next_LED:
            if(i == 2){
                PORTB = array[i];
                i = 0x00;
            }
            else{
                PORTB = array[i];
                i++;
            }
    }

}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;
    TimerSet(1000);
    TimerOn();
    
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
