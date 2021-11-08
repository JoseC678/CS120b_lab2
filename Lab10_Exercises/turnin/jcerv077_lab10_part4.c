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

 ///////////////////////////////////
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum ThreeLEDsm{init, blink} ThreeLEDstate;
unsigned char threeArray[] = {0x01,0x02,0x04};
unsigned char threeLEDs = 0;
unsigned char i = 0;


enum BlinkingLEDsm{init_oneLED, ON_OFF} BlinkingLEDstate;
unsigned char LEDarray[]={0x01,0x00};
unsigned char BlinkingLED = 0;
unsigned char j = 0;


enum SpeakerSM{init_Speaker, SpeakerOn, SpeakerOff} SpeakerState;
static unsigned char speakerValue = 0;
unsigned char speakerCount = 0;


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
            if(j==0){BlinkingLED = LEDarray[0];}
            if(j==1){BlinkingLED = LEDarray[1];}

            
            if(j<1){j++;}
            else{j=0;}

            break;

    }
}
//////////
void SpeakerTick(){
    switch(SpeakerState){
        case init_Speaker:
            SpeakerState = SpeakerOff;
            speakerValue = 0;
            break;
        case SpeakerOff:
            if((~PINA & 0x04) == 0x04){
                SpeakerState = SpeakerOn;
            }
            else{
                SpeakerState = SpeakerOff;
            }
            break;
        case SpeakerOn:
            if((~PINA & 0x04) == 0x04){
                speakerValue = ~speakerValue;
                SpeakerState = SpeakerOn;
            }
            else{
                SpeakerState = SpeakerOff;
                }
            break;
        default:
            break;
    }

    switch(SpeakerState){
        case SpeakerOn://
            break;
        case SpeakerOff:
            speakerValue = 0;
            break;
        default:
            break;
    }



}


enum FrequencySM{init_Freq, wait, up,down}FrequencyState;
unsigned short Speaker_Combine = 0;
short Speaker_CombineTick = 1;

void FreqTick(){

    switch(FrequencyState){
        case init_Freq:
            FrequencyState = wait;
            break;
        case wait:
            if((~PINA & 0x07)==0x01){
                FrequencyState = up;
                Speaker_CombineTick+=2;
                
            }else if((~PINA & 0x07) == 0x02){
                if(Speaker_CombineTick == 0){
                    //do nothing
                }
                else{
                    FrequencyState = down;
                    Speaker_CombineTick-=2;
                    if(Speaker_CombineTick<0){Speaker_CombineTick =0;}
                }
            }
            else{
                FrequencyState = wait;
            }
            break;
        case up:
            if((~PINA & 0x07) == 0x01){
                FrequencyState = up;
            }else{
                FrequencyState = wait;
            }
            break;
        case down:
            if((~PINA & 0x07) == 0x02){
                FrequencyState = down;
            }
            else{
                FrequencyState = wait;
            }
            break;

    }
}




void CombineTick(){
    switch(CombineState){
        case output:
            PORTB = ((speakerValue<<4)|(BlinkingLED << 3)|threeLEDs);
            //PORTB = ((speakerValue<<4));
            //PORTB = speakerValue<<4;
            break;
        
        default:
            break;
    }
}


int main(void) {
    	//Set the proper inputs and outputs
    DDRA = 0x00; PORTA = 0xFF; //Configure port A's pins as inputs
    DDRB = 0xFF; PORTB = 0x00; //Configure port A's pins as inputs
   // DDRC = 0xFF; PORTC = 0x00; //Configure port C's pins as outputs
    // DDRB = 0xFF; PORTB = 0x00; //Configure port C's pins as outputs
    //DDRD = 0xFF; PORTD = 0x00; //Configure port A's pins as outputs 
    
    //Initialize the starting point
    unsigned short ThreeLEDcount = 0;
    unsigned short SingleLEDcount = 0;
    unsigned short Speaker_Combine = 0;
    unsigned short Period = 2;

    TimerSet(2);
    TimerOn();

    ThreeLEDstate = init;
    CombineState = output;
    SpeakerState = init_Speaker;

    

    
    /* Insert your solution below */
    while (1) {

        FreqTick();
        if(ThreeLEDcount>=300){
            threeLEDTick();
            ThreeLEDcount = 0;
        }

        if(SingleLEDcount>=1000){
            SingleLedTick();
            SingleLEDcount = 0;
        }
        if(Speaker_Combine>=Speaker_CombineTick){
            
            SpeakerTick();
            CombineTick();
        Speaker_Combine = 0;
        }

        while (!TimerFlag){};
        TimerFlag = 0;

        ThreeLEDcount += Period;
        SingleLEDcount += Period;
        Speaker_Combine += Period;



    }
    return 1;
}
