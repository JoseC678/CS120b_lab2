/*	Author: Jose Cervantes
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Project
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Link: https://www.youtube.com/results?search_query=UCR+EECS+120B
 *
 *
 * Or if top dosent work on youtube
 *
 *  Demo Link channel: https://www.youtube.com/channel/UCQNx-GgmXaHu-ebYzAjvanA/videos
 *
 */

#define F_CPU 8000000UL
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
unsigned char gameOn = 0; //used to notify the game state that the "start game" option was selected
unsigned char outputMenu = 0;
unsigned char menu_on_off = 1; //Used for the Nokia state to know when the menu is on or off
unsigned char display_menuOnce =0;
 int level = 1; //Starting level counter to keep track of the levels
void set_startingMenu(); 
void set_PlayGame();
void restArray();
void win_Screen();
void lose_Screen();
void set_ShowScore(int lvl);
void printLED(unsigned short valueToLED);
void lightShowFunc();


unsigned char tickLight=0;


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
                    state = Joystick_Update; //update the position
                }
                if((~PIND & 0x08)==0x08){
                    state = pause_Hold;
                }
            }else{
                //printLED(0b00001111);
            }
            break;
        case Joystick_Update: break;
        case pause_Hold:
            state = ((~PIND & 0x08) == 0x08) ? pause_Hold:pause_Release; //wait until release
            break;
        case pause_Release:break;

        default: break;

    }

    switch(state){
        case JoyStick_Init:break;
        case JoyStick_Wait:break;
        case Joystick_Update: 
            printLED(output);

            currPosition= output;//Update current position
            state = JoyStick_Wait;
            break;
        case pause_Hold:break;
        case pause_Release: //The reset button was pressed so return to the starting menu
            set_startingMenu();  //Print menu
            state = JoyStick_Wait; 
            menu_on_off =1; //Turn menu on
            printLED(0b00001111);
            break;
        default: break;
    }


    return state;

}

//Array containing the light show sequence
unsigned char ArrLightShow[]={0b10000000,0b01000000,0b00100000,0b00010000,//all Top to botom
                              0b11110111,0b11111011,0b11111101,0b11111110,//all Left to right

                              0b10000111,0b10001011,0b10001101,0b10001110,//one by one left to right
                              0b01001110,0b01001101,0b01001011,0b01000111,//one by one left to right
                              0b00100111,0b00101011,0b00101101,0b00101110,//one by one left to right
                              0b00011110,0b00011101,0b00011011,0b00010111,//one by one left to right
                                         0b00100111,0b01000111,0b10000111,//one by one up down
                              0b10001011,0b01001011,0b00101011,0b00011011,//one by one up down
                              0b00011101,0b00101101,0b01001101,0b10001101,//one by one up down
                              0b10001110,0b01001110,0b00101110,0b00011110,//one by one up down
                              0b11110000,0b11110000,0b11110000,0b11110000,
                              0b11110000,0b11110000,0b11110000,0b11110000};//all on

                          //    0b00011110,0b00101110,0b01001110,0b10001110,//one by one up down
                        ///      0b10001101,0b01001101,0b00101101,0b00011101,//one by one up down
                         //     0b00011011,0b00101011,0b01001011,0b10001011,//one by one up down
                          //    0b10000111,0b01000111,0b00100111,0b00010111};//one by one up down

unsigned char indexLight=0;

unsigned char option1 =1;
unsigned char option2 =0;
enum NokiaState{NokiaInit, Nokia_Wait, up_Hold, up_Release, down_Hold,down_Release, start_Hold, start_Release, LightShow};
int NokiaTick(int state){
    if((~PIND & 0X08)==0X08){
        set_startingMenu(); //Print menu if button is pressed
    }

    switch(state){
        case NokiaInit: 
            
            state =  Nokia_Wait;
            
            break;
        case Nokia_Wait:
            if(menu_on_off == 1){
                if((~PIND & 0x01) == 0x01){ //Scroll up buttom
                    state = up_Hold;
                }else if((~PIND & 0x02) == 0x02){//Scroll down button
                    state = down_Hold;
                }else if(((~PIND & 0x04) == 0x04)&&(option1 == 1)){ //1st option
                    state = start_Hold;
                }else if(((~PIND & 0x04) == 0x04)&&(option2 == 1)){//2nd option
                    state = LightShow;
                }else{
                    state = Nokia_Wait;
                }
            }else{

            }
            
            break;
        case up_Hold:
            state = ((~PIND & 0x01) == 0x01) ? up_Hold:up_Release;
            option1 = 1;
            option2 = 0;
            break;
        case up_Release:break;
        case down_Hold:
            state = ((~PIND & 0x02) == 0x02) ? down_Hold:down_Release;
            option1 = 0;
            option2 = 1;
            break;
        case down_Release: break;
        case start_Hold: 
            state = ((~PIND & 0x04) == 0x04) ? start_Hold:start_Release;
            break;
        case start_Release: break;
        case LightShow: break;
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
            
            set_ShowScore(level);
            state = Nokia_Wait;
            break;
        case LightShow: 
            //50ms light is on so print the first element in the array and than go to the next element
            //until all elements in the array are displayed
            printLED(ArrLightShow[indexLight]);
            if(tickLight >(sizeof ArrLightShow / sizeof ArrLightShow[0])-1){
                state = Nokia_Wait; //exit the state
                indexLight =0;
                tickLight=0;
                printLED(0b00000000); //clear LED matrix
            }
            indexLight++; //
            tickLight++;
            break;
        default: break;
    }

    return state;
    
}

//I couldve added more levels but keep it relatively short so my demo video does not 
//exceed the time limit.
 int arraySelect[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}; //3 levels
 int arrayRecord[3][2]= {{0,0},{0,0},{0,0}};//3 input
 unsigned char pause_btwn_lvls =0; //counter for the pause of the start to each level
 int timeTick=0; //counter for the amount of time the LED is on
 int tempLVL = 0; //Temp to hold the current level
 int increment=0; //
 int xtemp=0; //x position of the random numbers selected array
 int ytemp=0; //y position of the random numbers selected array
enum GameState{gameInit,game_wait, generate_seq,display_seq, check_Responce,check_hold,check_release, nxt_Lvl, lose_game, win_Game};

int GameTick(int state){
    switch(state){
        case gameInit:
            restArray();
            level = 1;
            state = game_wait;
            break;
        case game_wait:
            if(menu_on_off == 0){//if menu is off than that means the game started so generate sequence
                state = generate_seq;
            }else{
                state = game_wait;
            }
            break;
        case generate_seq:  break;
        case display_seq: break;
        case check_Responce:
            printLED(currPosition);
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
                    printLED(0b00010000);
                    tempLVL--;
                    state = check_Responce;
        
                }else{
                    printLED(0b00100000);
                    state = lose_game;
                }
                if(tempLVL ==0){
                    printLED(0b00010000);
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
            for (int q=0; q<level; q++){//1st lvl = 1 number, 2nd =2 numbers and so on
                xtemp = rand() % 5;//generat a random position for x
                ytemp = rand() % 5;//also for y
                if(arraySelect[xtemp][ytemp]==1){//if there is a an index [][] that exist search again so no dublicates
                    q--;//Search again
                }else{
                    arrayRecord[q][0]=xtemp; //record the random index and store it to display it agin for the player
                    arrayRecord[q][1]=ytemp; //record the random index and store it to display it agin for the player
                    arraySelect[xtemp][ytemp] = 1; //Set that index to 1 to show that it is already selected
                }
            }
            state = display_seq;
            tempLVL = level;
            break;
        case display_seq:
            if(pause_btwn_lvls>=20){
                if(timeTick > 10){
                    //pause_btwn_lvls=0;
                    timeTick=0;
                    increment++;
                    tempLVL--;
                }else{
                    timeTick++;
                    //Print each random sequence for 1 sec
                    printLED((arrMatrix[arrayRecord[tempLVL-1][0]][arrayRecord[tempLVL-1][1]]));
                }
            }else{
                pause_btwn_lvls++;
                printLED(0b00010000);//green row means to get ready
            }

            if(tempLVL == 0){ //keep looping unil we output all the numbers that are in the level
                pause_btwn_lvls =0;
                state = check_Responce; //wait for the user response to make sure they are right
                gameOn = 1;
                printLED(0b00010000); //flash the green row to show its ready
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
            if((~PIND & 0X08)==0X08){//Wait for red button to be pressed
                set_startingMenu(); //reset arrays for next game
                state = gameInit;
                menu_on_off =1;
            }
            break;
        case lose_game: 
            lose_Screen();
            display_menuOnce =1;
            if((~PIND & 0X08)==0X08){//Wait for red button to be pressed
                set_startingMenu(); //reset arrays for next game
                state = gameInit;
                menu_on_off =1;
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



//Function for outputing the corrct values to the shift register one bit at a time.
void printLED(unsigned short valueToLED){
    PORTC = 0x00;
    for(int l = 0; l < 8; l++){
        PORTC = 0x08;
        PORTC |= ((valueToLED>>l) & 0x01);
        PORTC |= 0x02;
    } 
    PORTC |= 0x04;

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