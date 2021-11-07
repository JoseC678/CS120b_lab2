/*	Author: Jose Cervantes
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 10  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *
 *  Demo Link: https://drive.google.com/drive/folders/1452OogB5nVNzuja2EHKyvhxzJiOLQd_Y?usp=sharing
 *
 *
 * Or if top dosent work on youtube
 *
 *  Demo Link: https://www.youtube.com/channel/UCQNx-GgmXaHu-ebYzAjvanA
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum ThreeLEDsm{init, blink} ThreeLEDstate;
unsigned char threeArray[] = {0x01,0x02,0x04};
unsigned char threeLEDs;
unsigned char i;


enum BlinkingLEDsm{init_oneLED, ON_OFF} BlinkingLEDstate;
unsigned char BlinkingLED;


enum CombineSM{output}CombineState;


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

void threeLEDTick(){
    switch(ThreeLEDstate){
        case init:
            i = 0;
            ThreeLEDstate = blink;
            break;
        case blink:
            ThreeLEDstate = blink;
            break;
        default:
            ThreeLEDstate = init;
            break;
    }

    switch(ThreeLEDstate){
        case init:
            break;
        case blink:
            if(i==0){threeLEDs = threeArray[0];}
            if(i==1){threeLEDs = threeArray[1];}
            if(i==2){threeLEDs = threeArray[2];}
            
            if(i<2){i++;}
            else{i=0;}

            break;
        default:
            break;
    }
  

}

void SingleLedTick(){
    switch(BlinkingLEDstate){
        case init_oneLED:
            BlinkingLED = 0;
            BlinkingLEDstate = ON_OFF;
            break;
        case ON_OFF:
            BlinkingLEDstate = ON_OFF;
            break;
        default:
            break;
    }

    switch(BlinkingLEDstate){
        case ON_OFF:
            BlinkingLED = ~BlinkingLED;
            break;

    }
}

void CombineTick(){
    switch(CombineState){
        case output:
            PORTB = ((BlinkingLED << 3)|threeLEDs);
            break;
        
        default:
            break;
    }
}


int main(void) {
    	//Set the proper inputs and outputs
    //DDRA = 0x00; PORTA = 0xFF; //Configure port A's pins as inputs
    DDRB = 0xFF; PORTB = 0x00; //Configure port A's pins as inputs
   // DDRC = 0xFF; PORTC = 0x00; //Configure port C's pins as outputs
    // DDRB = 0xFF; PORTB = 0x00; //Configure port C's pins as outputs
    //DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 
    
    //Initialize the starting point
    unsigned short ThreeLEDcount = 0;
    unsigned short SingleLEDcount = 0;
    unsigned short Period = 100;

    ThreeLEDstate = init;
    CombineState = output;

    
    TimerSet(100);
    TimerOn();
    
    /* Insert your solution below */
    while (1) {
        if(ThreeLEDcount>=300){
            threeLEDTick();
            ThreeLEDcount = 0;
        }

        if(SingleLEDcount>=1000){
            SingleLedTick();
            SingleLEDcount = 0;
        }

        CombineTick();

        while (!TimerFlag){};
        TimerFlag = 0;

        ThreeLEDcount += Period;
        SingleLEDcount += Period;



    }
    return 1;
}
