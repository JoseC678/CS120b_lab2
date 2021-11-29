/*	Author: Jose Cervantes
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Project
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
 *
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "../header/timer.h"
#include "../header/ADC.h"
#include "../header/JoyStick.h"
#endif


typedef struct _task{
    signed char state;
    unsigned long int period;
    unsigned long int elapsedTime;
    int(*TickFct)(int);
}task;

enum JoyStickState{JoyStick_Init, JoyStick_Wait, Joystick_Update, LED_select};   
int JoyStickTick(int state){
    unsigned short x,y;
    unsigned short temp;
    x=ADCvalue(0);      //Read ADC 0 from PA0
    y=ADCvalue(1);      //Read ADC 1 from PA1
    output = XY_Position(x,y); //get the correct LED binary number corresponding to the correct joystick movement

    switch(state){
        case JoyStick_Init:state = JoyStick_Wait; break;
        case JoyStick_Wait:
            if(currPosition == output){
                //If The current position is the same as the output than no movenment is detected
                state = JoyStick_Wait;
            }else{
                state = Joystick_Update;
            }
            if((~PIND & 0x01)==0x01){
                state = LED_select;
            }
            break;
        case Joystick_Update: break;
        case LED_select: break;
        default: break;

    }

    switch(state){
        case JoyStick_Init:break;
        case JoyStick_Wait:break;
        case Joystick_Update: 
            PORTC = 0x00;
            for(int l = 0; l < 8; l++){
                PORTC = 0x08;
                PORTC |= ((output>>l) & 0x01);
                PORTC |= 0x02;
            } 
            PORTC |= 0x04;
            currPosition= output;//Update current position
            state = JoyStick_Wait;
            break;
        case LED_select: 
            temp =0b10010110;
            PORTC = 0x00;
            for(int l = 0; l < 8; l++){
                PORTC = 0x08;
                PORTC |= ((temp>>l) & 0x01);
                PORTC |= 0x02;
            } 
            PORTC |= 0x04;
            state = JoyStick_Wait;
            break;
        default: break;
    }



    


    return state;


   // return state;
}



int main(void){
    int i;
    DDRA = 0x00; PORTA = 0xFF; // A pins are used as inputs for the Joystick
    DDRC = 0x0F; PORTC = 0xF0; // C pins first 4 pins are used as outputs
    DDRD = 0x00; PORTD = 0xFF; // C pins first 4 pins are used as outputs

    static task task1;
    task *tasks[] = {&task1}; 
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    task1.state=JoyStick_Init;
    task1.period=150;
    task1.elapsedTime = task1.period;
    task1.TickFct = &JoyStickTick;


    TimerSet(50);
    TimerOn();


    
    while(1)
    {       
        for (i = 0; i < numTasks; ++i) {
            if (tasks[i]->elapsedTime >= tasks[i]->period) {
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 0;
            }
        tasks[i]->elapsedTime += 50;

            while(!TimerFlag){}
            TimerFlag = 0;
        }
    }
    return 1;
}




