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

enum MoveScreen{ScreenInit, ScreenWait,ScreenRelease, ScreenStart,ScreenStartRelease};
unsigned char obsticals[] = {"      #                    #    "};
unsigned char dispString[32]={};
unsigned char index = 0;
unsigned char y = 0;
unsigned char Cursor = 2;
unsigned char ErrorMess = 0;

int MoveScreenTick(int state){
    switch (state){
        case ScreenInit: state = ScreenWait; break;

        case ScreenWait: 
            state = ((~PINB & 0x01)==1) ? ScreenRelease : ScreenWait;
            break;

        case ScreenRelease:
            state = ((~PINB & 0x01)==1) ? ScreenRelease : ScreenStart;
            break;

        case ScreenStart:
            state = ((~PINB & 0x01)==1) ? ScreenStartRelease : ScreenStart;
            break;

        case ScreenStartRelease:
            state = ((~PINB & 0x01)==1) ? ScreenStartRelease : ScreenWait;
            break;
            
        default:
            break;
    }

    switch(state){
        case ScreenInit:break;
        case ScreenWait:break;
        case ScreenRelease: break;
        case ScreenStart:
            if(ErrorMess == 0){
                for (int y = 0; y < 31; y++) {
                    dispString[y] = obsticals[(y+index) % 32];
                    LCD_Cursor(y+1);
                    LCD_WriteData(obsticals[(y+index) % 32] );

                    
                }
                LCD_Cursor(Cursor);
                index = ((index + 1) % 32);
            }else if(ErrorMess == 1){

                
            }else{

            }
            break;
        default: break;                   
    }
    return state;
}

enum buttons{buttoninit, buttonWait, buttonUp, buttonDown};

int buttonTick(int state){
    switch(state){
        case buttoninit: state = buttonWait; break;
        case buttonWait:
            if(((~PINB & 0x02)==2)){
                //Cursor = 2; 
                state = buttonUp;
            }else if(((~PINB & 0x04)==4)){
                //LCD_Cursor(15);
                state = buttonDown;
            }else{
                state = buttonWait;
            }
            break;
        case buttonUp: state = buttonWait; break;
        case buttonDown: state = buttonWait; break;
        default: break;
    }

    switch(state){
        case buttoninit: break;
        case buttonWait: break;
        case buttonUp:
            Cursor = 2; 
            break;
        case buttonDown: 
            Cursor = 18; 
            break;
        default: break;
        
    }

    //LCD_Cursor(Cursor);
    
}

enum Lose{Loseinit, Lose};   
int LoseTick(int state){
    switch(state){
        case Loseinit: state = Lose; break;
        
        case Lose:
            if( Cursor == 2 && ((dispString[1]) == '#')) {
                ErrorMess = 1;
                LCD_DisplayString(1, "You Lose                        ");

            }else if( Cursor == 18 && ((dispString[17]) == '#')) {
                ErrorMess = 1;
                LCD_DisplayString(1, "You Lose                        ");

            
            }else{
                //Do nothing
            }

            if(((~PINB & 0x01) == 0x01) && ErrorMess == 1){
                ErrorMess =0;
                LCD_init();
                dispString[1] = "";
                dispString[17] = "";

            }


            break;

        default: break;
    }
    return state;
}


int main(void) {
    unsigned short i = 0;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRA = 0xFF; PORTA = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    
    static task task1, task2, task3;
    task *tasks[] = {&task1, &task2, &task3}; 
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    task1.state=ScreenInit;
    task1.period=60;
    task1.elapsedTime = task1.period;
    task1.TickFct = &MoveScreenTick;

    task2.state=buttoninit;
    task2.period=20;
    task2.elapsedTime = task2.period;
    task2.TickFct = &buttonTick;

    task3.state=Loseinit;
    task3.period=20;
    task3.elapsedTime = task3.period;
    task3.TickFct = &LoseTick;

    

    TimerSet(20);
    TimerOn();
    LCD_init();

    while (1) {
        for (i = 0; i < numTasks; ++i) {
            if (tasks[i]->elapsedTime >= tasks[i]->period) {
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 0;
            }
        tasks[i]->elapsedTime += 20;
            while(!TimerFlag){}
            TimerFlag = 0;
        }
    }
    return 1;
}
