/*	Author: lab Jose Cervantes
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #4
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
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "../header/keypad.h"
#include "../header/timer.h"
#include "../header/io.h"
#endif



typedef struct _task{
    signed char state;
    unsigned long int period;
    unsigned long int elapsedTime;
    int(*TickFct)(int);
}task;


unsigned char keypadOutput=0;
unsigned char value=0;

enum KeypadStates{wait, start};
int keypadTick(int state){
    keypadOutput=GetKeypadKey();
    
    switch(state){
        case wait: state = start; break;
        case start: state = start; break;
        default: break;
    }

    switch(state){
        case wait: break;
        case start:
            switch (keypadOutput){
                case '\0': value = 0x1F; break;
                case '1': value = 0x01; break;
                case '2': value = 0x02; break;
                case '3': value = 0x03; break;
                case '4': value = 0x04; break;
                case '5': value = 0x05; break;
                case '6': value = 0x06; break;
                case '7': value = 0x07; break;
                case '8': value = 0x08; break;
                case '9': value = 0x09; break;
                case 'A': value = 0x0A; break;
                case 'B': value = 0x0B; break;
                case 'C': value = 0x0C; break;
                case 'D': value = 0x0D; break;
                case '#': value = 0x0E; break;
                case '0': value = 0x00; break;
                case '*': value = 0x0F; break;
                default: value = 0x1B; break;
            }

            PORTB = value;
            break;
        default: break;
    }
    return state;

}

enum LCDscreen{waitLCD, startLCD, buttonPress};
unsigned char dispString[16]={};
unsigned char sentence[] = "                 CS120B is Legend... wait for it DARY!";
unsigned char index=0x01;
int LCDTick(int state){
    switch(state){
        case waitLCD: state = start; break;
        case startLCD: state = (value == 0x1F) ? startLCD : buttonPress; break; 
        case buttonPress: state = startLCD; break;
        default: break;
    }

    switch(state){
        case waitLCD: break;
        case startLCD: break;
        case buttonPress: 
            LCD_Cursor(index);
            LCD_WriteData(keypadOutput);

            if(index>15){index = 1;}
            else{index++;}
            break;
        default: break;

    }
    return state;
}


enum output{wait2, start2};
int outputTick(int state){
    switch(state){
        case wait2: state = start2; break;
        case start2: state = start2; break;
        default: break;
    }

    switch(state){
        case wait2: break;
        case start2:// PORTB = value; break;
        default: break;
    }
    return state;
}



int main(void) {
    unsigned short i = 0;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRA = 0xFF; PORTA = 0x00;
    DDRD = 0xFF; PORTD = 0x00;


    
    static task task1, task2, task3;
    task *tasks[] = {&task1, &task2, &task3}; 
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    task1.state=wait;
    task1.period=50;
    task1.elapsedTime = task1.period;
    task1.TickFct = &keypadTick;

    i++;

    task2.state=wait2;
    task2.period=50;
    task2.elapsedTime = task2.period;
    task2.TickFct = &outputTick;

    i++;

    task3.state=waitLCD;
    task3.period=50;
    task3.elapsedTime = task3.period;
    task3.TickFct = &LCDTick; 


    
    TimerSet(50);
    TimerOn();
    
    LCD_init();
    LCD_DisplayString(1, "");
    LCD_DisplayString(1,"Congratulations!");


    while (1) {
        


        for (i = 0; i < numTasks; i++) {
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
