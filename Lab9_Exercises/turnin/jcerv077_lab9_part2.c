/*	Author: Jose Cervantes jcerv077@gmail.com
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #9  Exercise #2
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

enum State_one{init_1, wait_1,  Buttton_on_off} state1;
enum State_two{init_2, wait, increase, decrease} state2;
unsigned char toogle_on_off;
unsigned char i;
unsigned short array[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};



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
    switch(state2){
        case init_2:
            state2 = wait;
            i = 0;
            break;
        case wait:
            if((~PINA & 0x07) == 0x04){ //increase button
                state2 = increase;
                if(i==7){}
                else{i++;}
            }
            else if((~PINA & 0x07) == 0x01){
                state2 = decrease;
                if(i==0){}
                else{i--;}
            }
            else{
                state2 = wait;
            }
            break;
    
        case increase:
            state2 = ((~PINA & 0x07)==0x04) ? increase: wait;
            break;

        case decrease:
            state2 = ((~PINA & 0x07)==0x01) ? decrease: wait;

            break;
        default:
            break;
    }


    switch(state1){
        case init_1:
            state1 = wait_1;
            toogle_on_off = 0;
            break;

        case wait_1:
            if(toogle_on_off == 1){set_PWM(array[i]);}
            else{set_PWM(0);}

            if((~PINA & 0x07) == 0x02){
                state1 = Buttton_on_off;
                if(toogle_on_off == 0){
                    toogle_on_off = 1;
                    set_PWM(array[i]);

                }else if(toogle_on_off == 1){
                    toogle_on_off = 0;
                    set_PWM(0);
                }

            }else{
                state1 = wait_1;
            }
            break;

        case Buttton_on_off:
            if((~PINA & 0x07) == 0x02){
                state1 = Buttton_on_off;
            }else{
                state1 = wait_1;
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
    
    TimerSet(100);
    TimerOn();
    PWM_on();
    state1 = init_1;
    state2 = init_2;
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
