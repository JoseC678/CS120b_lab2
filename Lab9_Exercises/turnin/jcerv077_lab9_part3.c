/*	Author: Jose Cervantes jcerv077@gmail.com
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #9  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Link: https://drive.google.com/drive/folders/1452OogB5nVNzuja2EHKyvhxzJiOLQd_Y?usp=sharing
 *
 *
 * Or if top dosent work on youtube
 *
 *  Demo Link: https://www.youtube.com/channel/UCQNx-GgmXaHu-ebYzAjvanA
 */
#include <avr/io.h>
#include "io.h"

#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum state{init, wait, Play_Melody, check} state;
unsigned short i;
unsigned short note_number;
unsigned short time_number;


unsigned short array_time[]  ={49,49,49,49,49,49,49,49,49,59};
unsigned short array_notes[] = {293.66, 349.23, 349.23,293.66,349.23,349.23,
                                293.66, 349.23, 300.66,349.23};



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

void set_PWM(double frequency){
    static double current_frequency;
    if(frequency != current_frequency){
        if(!frequency){TCCR3B &= 0x08;}
        else{TCCR3B |= 0x03;}

        if(frequency < 0.954){OCR3A = 0xFFFF;}
        else if (frequency > 31250){OCR3A = 0x0000;}
        else{ OCR3A = (short)(8000000 / (128 * frequency))-1;}

        TCNT3 = 0;
        current_frequency = frequency;
    }
}

void PWM_on(){
    TCCR3A = (1 << COM3A0);
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 <<CS30);
    set_PWM(0);

}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

void tick(){
    switch (state){
        case init:
            state = wait;
            i = 0x00;
            note_number = 0x00;
            time_number = 0x00;
            break;
        case wait:
            state = ((~PINA & 0x01)==0x01) ? Play_Melody : wait;
        case Play_Melody:
            break;
        case check:
            state = ((~PINA & 0x01)==0x01) ? check : wait;
            break;
        
    }

    switch(state){
        case wait:
            break;
        case Play_Melody:
            if(i<=500){
                set_PWM(array_notes[note_number]);

                if(time_number==array_time[note_number]){
                    note_number++;
                    time_number = 0x00;
                }
                time_number++;
                i++;

            }
            else{
                state = check;
                i=0x00;
                note_number = 0x00;
                set_PWM(0);
            }
            break;
        default:
            break;

    }
   
}



int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00; //Configure port A's pins as outputs 
    DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 
    
    TimerSet(10);
    TimerOn();
    PWM_on();
    state = init;
    //Initializes the LCD display


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
