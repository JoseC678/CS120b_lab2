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
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "../header/font.h"
#include "../header/timer.h"
#include "../header/nokia.h"
#include "../header/ADC.h"
#include "../header/JoyStick.h"
#endif


typedef struct _task{
    signed char state;
    unsigned long int period;
    unsigned long int elapsedTime;
    int(*TickFct)(int);
}task;

unsigned char currPositionMenu = 0;
unsigned char gameOn = 0;
unsigned char outputMenu = 0;
unsigned char menu_on_off = 1;
unsigned char display_menuOnce =0;
 int level = 1;
void set_startingMenu();
void set_PlayGame();
void restArray();
void win_Screen();
void lose_Screen();
void set_ShowScore(int lvl);




enum JoyStickState{JoyStick_Init, JoyStick_Wait, Joystick_Update, pause_Hold,pause_Release};   
int JoyStickTick(int state){
    unsigned short x,y;
    unsigned short temp;
    x=ADCvalue(0);      //Read ADC 0 from PA0
    y=ADCvalue(1);      //Read ADC 1 from PA1
    output = XY_Position(x,y); //get the correct LED binary number corresponding to the correct joystick movement

    switch(state){
        case JoyStick_Init:state = JoyStick_Wait; break;
        case JoyStick_Wait:
            if(menu_on_off==0 && gameOn == 1){
                if(currPosition == output){
                    //If The current position is the same as the output than no movenment is detected
                    state = JoyStick_Wait;
                }else{
                    state = Joystick_Update;
                }
                if((~PIND & 0x08)==0x08){
                    state = pause_Hold;
                }
            }else{
               // PORTC = 0x00;
               // for(int l = 0; l < 8; l++){
              //      PORTC = 0x08;
              //      PORTC |= ((0b00001111>>l) & 0x01);
              //      PORTC |= 0x02;
              //  } 
              //  PORTC |= 0x04;
            }
            break;
        case Joystick_Update: break;
        case pause_Hold:
            state = ((~PIND & 0x08) == 0x08) ? pause_Hold:pause_Release;
            break;
        case pause_Release:break;

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
        case pause_Hold:break;
        case pause_Release:
                    Snd_Nokia_Instructions(0x40);
            Snd_Nokia_Instructions(0x80);
                
            //Send Text, second Parameter is if to highlight the row
            Snd_Nokia_Data("1. Start Game ",0);
            Snd_Nokia_Data("2. Light Show ",1);


            state = JoyStick_Wait;
            menu_on_off =1;
            PORTC = 0x00;
            for(int l = 0; l < 8; l++){
                PORTC = 0x08;
                PORTC |= ((0b00001111>>l) & 0x01);
                PORTC |= 0x02;
            } 
            PORTC |= 0x04;
            break;
        default: break;
    }


    return state;


   // return state;
}

enum NokiaState{NokiaInit, Nokia_Wait, up_Hold, up_Release, down_Hold,down_Release, start_Hold, start_Release};
int NokiaTick(int state){
            if((~PIND & 0X08)==0X08){
                set_startingMenu();
            }

    switch(state){
        case NokiaInit: 
            
            state =  Nokia_Wait;
            
            break;
        case Nokia_Wait:
            if(menu_on_off == 1){
                if((~PIND & 0x01) == 0x01){
                    state = up_Hold;
                }else if((~PIND & 0x02) == 0x02){
                    state = down_Hold;
                }else if((~PIND & 0x04) == 0x04){
                    state = start_Hold;
                }else{
                    state = Nokia_Wait;
                }
            }else{

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
        case start_Hold: 
            state = ((~PIND & 0x04) == 0x04) ? start_Hold:start_Release;
            break;
        case start_Release: break;
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
            Snd_Nokia_Data("2. Light Show ",0);
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
            Snd_Nokia_Data("2. Light Show ",1);
            state = Nokia_Wait;
            break;
        case start_Hold:break;
        case start_Release: 
            menu_on_off =0;
            clear_Screen();
            //Initialize x&y
            Snd_Nokia_Instructions(0x40);
            Snd_Nokia_Instructions(0x80);
            
            set_ShowScore(level);
            state = Nokia_Wait;
            break;
        default: break;
    }

    return state;
    
}

 int arraySelect[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
 int arrayRecord[3][2]= {{0,0},{0,0},{0,0}};
 int timeTick=0;
 int tempLVL = 0;
 int increment=0;
 int xtemp=0;
 int ytemp=0;
enum GameState{gameInit,game_wait, generate_seq,display_seq, check_Responce,check_hold,check_release, nxt_Lvl, lose_game, win_Game};

int GameTick(int state){
    switch(state){
        case gameInit:
            restArray();
            level = 1;
            state = game_wait;
            break;
        case game_wait:
            if(menu_on_off == 0){
                state = generate_seq;
            }else{
                state = game_wait;
            }
            break;
        case generate_seq:  break;
        case display_seq: break;
        case check_Responce:
            if((~PIND & 0x04) == 4){
                state = check_hold;
            }else{
                state = check_Responce;
            }
            
            break;
        case check_hold:break;
        case check_release:
            if(tempLVL >0){
                state = check_Responce;
                if(arrayRecord[tempLVL-1][0] == ii && arrayRecord[tempLVL-1][1] == jj){
                    tempLVL--;
                    state = check_Responce;
        
                }else{
                    state = lose_game;
                }
                if(tempLVL ==0){
                    level++;
                    state = game_wait;
                    restArray();
                }
                if(tempLVL==0 && level ==4){
                    state = win_Game;
                }
                set_ShowScore(level);
            }
            break;
        case win_Game: break;
        case lose_game: break;
        default: break;
    }

    switch(state){
        case gameInit:break;
        case game_wait:break;
        case generate_seq:
            for (int q=0; q<level; q++){
                xtemp = rand() % 5;
                ytemp = rand() % 5;
                if(arraySelect[xtemp][ytemp]==1){
                    q--;//Search again
                }else{
                    arrayRecord[q][0]=xtemp;
                    arrayRecord[q][1]=ytemp;
                    arraySelect[xtemp][ytemp] = 1;
                }
            }
            state = display_seq;
            tempLVL = level;
            break;
        case display_seq:
            if(timeTick > 10){
                timeTick=0;
                increment++;
                tempLVL--;
            }else{
                timeTick++;

                PORTC = 0x00;
                for(int l = 0; l < 8; l++){
                    PORTC = 0x08;
                    PORTC |= ((arrMatrix[arrayRecord[tempLVL-1][0]][arrayRecord[tempLVL-1][1]]>>l) & 0x01);
                    PORTC |= 0x02;
                } 
                PORTC |= 0x04;

            }

            if(tempLVL == 0){
                state = check_Responce;
                gameOn = 1;

                PORTC = 0x00;
                for(int l = 0; l < 8; l++){
                    PORTC = 0x08;
                    PORTC |= ((0b10000111>>l) & 0x01);
                    PORTC |= 0x02;
                } 
                PORTC |= 0x04;
                tempLVL = level;
            }
            break;
        case check_Responce:break;
        case check_hold:
            if((~PIND & 0x04) == 4){
                state = check_hold;
            }else{
                state = check_release;
            }
            break;
        case check_release:break;
        case win_Game: 
            win_Screen();
            display_menuOnce =1;
            if((~PIND & 0X08)==0X08){
                set_startingMenu();
                state = gameInit;
            }
            break;
        case lose_game: 
            lose_Screen();
            display_menuOnce =1;
            if((~PIND & 0X08)==0X08){
                set_startingMenu();
                state = gameInit;
            }
            break;
        default:break;
    }
    if(menu_on_off==1){
        state = gameInit;
        //display_menuOnce =1;
    }
    return state;
}

int main(void){
    srand(time(NULL));
    int i;
    DDRA = 0x00; PORTA = 0xFF; // A pins are used as inputs for the Joystick
    DDRC = 0x0F; PORTC = 0xF0; // C pins first 4 pins are used as outputs
    DDRB = 0xFF; PORTB = 0x00; 
    DDRD = 0x00; PORTD = 0xFF; // C pins first 4 pins are used as outputs

    static task task1, task2,task3;
    task *tasks[] = {&task1, &task2,&task3}; 
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    task1.state=JoyStick_Init;
    task1.period=100;
    task1.elapsedTime = task1.period;
    task1.TickFct = &JoyStickTick;

    task2.state=NokiaInit;
    task2.period=50;
    task2.elapsedTime = task2.period;
    task2.TickFct = &NokiaTick;

    task3.state=gameInit;
    task3.period=50;
    task3.elapsedTime = task3.period;
    task3.TickFct = &GameTick;

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

void lose_Screen(){
    clear_Screen();

    //Initialize x&y
    Snd_Nokia_Instructions(0x40);
    Snd_Nokia_Instructions(0x80);
    
    //Send Text, second Parameter is if to highlight the row
    Snd_Nokia_Data("1. You LOSE!! ",1);
    Snd_Nokia_Data("2. Press Red Button to play again  ",0);

}

void win_Screen(){
    clear_Screen();

    //Initialize x&y
    Snd_Nokia_Instructions(0x40);
    Snd_Nokia_Instructions(0x80);
    
    //Send Text, second Parameter is if to highlight the row
    Snd_Nokia_Data("1. You WIN!!! ",1);
    Snd_Nokia_Data("2. Score: 3        Press Red Button to play again  ",0);
}

void set_startingMenu(){

    clear_Screen();

    //Initialize x&y
    Snd_Nokia_Instructions(0x40);
    Snd_Nokia_Instructions(0x80);
    
    //Send Text, second Parameter is if to highlight the row
    Snd_Nokia_Data("1. Start Game ",1);
    Snd_Nokia_Data("2. Light Show  ",0);

}

void set_PlayGame(){

    clear_Screen();

    //Initialize x&y
    Snd_Nokia_Instructions(0x40);
    Snd_Nokia_Instructions(0x80);
    
    //Send Text, second Parameter is if to highlight the row
    Snd_Nokia_Data("1. LVL1       ",0);
    Snd_Nokia_Data("2. Score: 1",0);
    

}



void set_ShowScore(int lvl){

    clear_Screen();

    //Initialize x&y
    Snd_Nokia_Instructions(0x40);
    Snd_Nokia_Instructions(0x80);
    
    //Send Text, second Parameter is if to highlight the row
    if(lvl == 1){
            Snd_Nokia_Data("1. LVL1       ",0);
    Snd_Nokia_Data("2. Score: 0",0);
    }
    if(lvl == 2){
            Snd_Nokia_Data("1. LVL2       ",0);
    Snd_Nokia_Data("2. Score: 1",0);
    }
    if(lvl == 3){
            Snd_Nokia_Data("1. LVL3       ",0);
    Snd_Nokia_Data("2. Score: 2",0);
    }

    

}

void restArray(){

 arraySelect[0][0]=0;
 arraySelect[0][1]=0;
 arraySelect[0][2]=0;
 arraySelect[0][3]=0;
 arraySelect[1][0]=0;
 arraySelect[1][1]=0;
 arraySelect[1][2]=0;
 arraySelect[1][3]=0;
 arraySelect[2][0]=0;
 arraySelect[2][1]=0;
 arraySelect[2][2]=0;
 arraySelect[2][3]=0;
 arraySelect[3][0]=0;
 arraySelect[3][1]=0;
 arraySelect[3][2]=0;
 arraySelect[3][3]=0;

 arrayRecord[0][0]= 0;
 arrayRecord[0][1]= 0;
 arrayRecord[1][0]= 0;
 arrayRecord[1][1]= 0;
 arrayRecord[2][0]= 0;
 arrayRecord[2][1]= 0;
}