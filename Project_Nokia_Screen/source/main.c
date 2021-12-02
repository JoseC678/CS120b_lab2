/*	Author: Jose Cervantes
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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
#include <util/delay.h>
#include <string.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "../header/font.h"
#include "../header/timer.h"
#include "../header/nokia.h"
#endif


typedef struct _task{
    signed char state;
    unsigned long int period;
    unsigned long int elapsedTime;
    int(*TickFct)(int);
}task;

unsigned char currPositionMenu = 0;
unsigned char outputMenu = 0;
unsigned char menu_on_off = 1;
void set_startingMenu();
void set_PlayGame();

enum NokiaState{NokiaInit, Nokia_Wait, up_Hold, up_Release, down_Hold,down_Release};
int NokiaTick(int state){
    switch(state){
        case NokiaInit: 
            state =  Nokia_Wait;
            
            break;
        case Nokia_Wait:

            if((~PIND & 0x01) == 0x01){
                state = up_Hold;
            }else if((~PIND & 0x02) == 0x02){
                state = down_Hold;
            }else{
                state = Nokia_Wait;
            }
            
            break;
        case up_Hold:
            state = ((~PIND & 0x01) == 0x01) ? up_Hold:up_Release;
            break;
        case up_Release:break;
        case down_Hold:
            state = ((~PIND & 0x02) == 0x02) ? down_Hold:down_Release;
            break;
        case down_Release: break;
        default: break;
    }

    switch(state){
        case NokiaInit:break;
        case Nokia_Wait:break;
        case up_Hold:break;
        case up_Release:
            //clear_Screen();
            //Initialize x&y
            Snd_Nokia_Instructions(0x40);
            Snd_Nokia_Instructions(0x80);
                
            //Send Text, second Parameter is if to highlight the row
            Snd_Nokia_Data("1. Start Game ",1);
            Snd_Nokia_Data("1. Light Show ",0);
            state = Nokia_Wait;
            break;
        case down_Hold:break;
        case down_Release: 
            //clear_Screen();
            //Initialize x&y
            Snd_Nokia_Instructions(0x40);
            Snd_Nokia_Instructions(0x80);
                
            //Send Text, second Parameter is if to highlight the row
            Snd_Nokia_Data("1. Start Game ",0);
            Snd_Nokia_Data("1. Light Show ",1);
            state = Nokia_Wait;
            break;
        default: break;
    }

    return state;
    
}




int main(void) {
    int i;
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00; 
    DDRD = 0x00; PORTD = 0xFF; // C pins first 4 pins are used as outputs
    /* Insert your solution below */




    static task task1;
    task *tasks[] = {&task1}; 
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    task1.state=NokiaInit;
    task1.period=50;
    task1.elapsedTime = task1.period;
    task1.TickFct = &NokiaTick;
    SPI_Init();
    init_Screen();
    set_startingMenu();

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

void set_startingMenu(){

    clear_Screen();

    //Initialize x&y
    Snd_Nokia_Instructions(0x40);
    Snd_Nokia_Instructions(0x80);
    
    //Send Text, second Parameter is if to highlight the row
    Snd_Nokia_Data("1. Start Game ",1);
    Snd_Nokia_Data("1. Light Show  ",0);

}

void set_PlayGame(){

    clear_Screen();

    //Initialize x&y
    Snd_Nokia_Instructions(0x40);
    Snd_Nokia_Instructions(0x80);
    
    //Send Text, second Parameter is if to highlight the row
    Snd_Nokia_Data("1. LVL1 ",0);
    Snd_Nokia_Data("1. Score: 1",0);
    

}