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
#endif


typedef struct _task{
    signed char state;
    unsigned long int period;
    unsigned long int elapsedTime;
    int(*TickFct)(int);
}task;

//Function for determining which direction the joystick is moving
//For a 4x4 matrix using a shift register.
unsigned short XY_Position(unsigned short x,unsigned short y);
int arrMatrix[4][4] = {{0b10000111,0b10001011,0b10001101,0b10001110},
                       {0b01000111,0b01001011,0b01001101,0b01001110},
                       {0b00100111,0b00101011,0b00101101,0b00101110},
                       {0b00010111,0b00011011,0b00011101,0b00011110}};
unsigned char i = 0;
unsigned char j = 0;
unsigned short output=0;
unsigned short x,y;
unsigned short currPosition = 0b10000111; 

//Corresponding binnary sequence for each position in the 2 dimensional array
//The values are fliped sinced ouputing it to a shift register the first value ouputed
//is the last value
/*
arrMatrix[0][0] = 0b10000111;// 0b11100001; //11
arrMatrix[0][1] = 0b10001011;// 0b11010001; //12
arrMatrix[0][2] = 0b10001101;// 0b10110001; //13
arrMatrix[0][3] = 0b10001110;// 0b01110001; //14
        
arrMatrix[1][0] = 0b01000111;// 0b11100010; //21
arrMatrix[1][1] = 0b01001011;// 0b11010010; //22
arrMatrix[1][2] = 0b01001101;// 0b10110010; //23
arrMatrix[1][3] = 0b01001110;// 0b01110010; //22

arrMatrix[2][0] = 0b00100111;// 0b11100100; //31
arrMatrix[2][1] = 0b00101011;// 0b11010100; //32
arrMatrix[2][2] = 0b00101101;// 0b10110100; //33
arrMatrix[2][3] = 0b00101110;// 0b01110100; //33

arrMatrix[3][0] = 0b00010111;// 0b11101000; //41
arrMatrix[3][1] = 0b00011011;// 0b11011000; //42
arrMatrix[3][2] = 0b00011101;// 0b10111000; //43
arrMatrix[3][3] = 0b00011110;// 0b01111000; //43
*/

int main(void){
    DDRA = 0x00; PORTA = 0xFF; // A pins are used as inputs for the Joystick
    DDRC = 0x0F; PORTC = 0xF0; // C pins first 4 pins are used as outputs
    
    TimerSet(150);
    TimerOn();

    PORTC = 0x00; //Inilialize the starting position of the first LED position
    for(int l = 0; l < 8; l++){ //cycle 8 times for the 4 rows and 4 columns
        PORTC = 0x08; //Set SRCLR to 1 to write new bit
        PORTC |= ((currPosition>>l) & 0x01);//Shifting each bit 1 by one 
                                            //the [1][1] led is turned on for the SER pin 8 times for each bit
        PORTC |= 0x02; //set SRCLK to 1
    }

    PORTC |= 0x04; //Set RCLK to 1
    
    while(1)
    {       
        x=ADCvalue(0);      //Read ADC 0 from PA0
        y=ADCvalue(1);      //Read ADC 1 from PA1

        output = XY_Position(x,y); //get the correct LED binary number corresponding to the correct joystick movement

        if(currPosition == output){
            //If The current position is the same as the output than no movenment is detected
        }else{
            PORTC = 0x00;
            for(int l = 0; l < 8; l++){
                PORTC = 0x08;
                PORTC |= ((output>>l) & 0x01);
                PORTC |= 0x02;
            } 
            PORTC |= 0x04;
            currPosition= output;//Update current position
        }
        while (!TimerFlag);
        TimerFlag = 0;
        
    }
    return 0;
}





unsigned short XY_Position(unsigned short x,unsigned short y){
    //-------------------------------
    //------------Range--------------
    // ------------------------------
    //
    //Right: x = 2.5V && y = 5V  Voltage
    //Right: x = 512 && y = 1023     ADC Value
    //
    //Down Right: x = 5V  && y = 5V      Voltage 
    //Down Right: x = 1023  && y =1 023   ADC Value
    //
    //Down: x = 5V && y = 2.5V    Voltage
    //Down: x = 1023 && y = 512    ADC Value
    //
    //Down left: x = 5V  && y = 0V      Voltage 
    //Down left: x = 1023  && y = 0   ADC Value
    //
    //Left: x = 2.5V && y = 0V     Voltage
    //Left: x = 512 && y = 0       ADC Value
    //
    //Left Up: x = 0V  && y = 0V      Voltage 
    //Left Up: x = 0  && y = 0   ADC Value
    //
    //Up: x = 0 && y = 2.5V       Voltage
    //Up: x = 0 && y = 512       ADC Value
    //
    //Up Right: x = 0V  && y = 5V      Voltage 
    //Up Right: x = 0  && y = 1023   ADC Value
    if((x>300 && x<600) && y>800){////////////////////////////Right
        if(j==3){
            //do nothing
            return(arrMatrix[i][j]);
        }else{
            j++;
            return(arrMatrix[i][j]);
        }
        
    }
    //*
    else if(x>604 && y>700){////////////////////////Right Down Diagonal 
        if(i==3 || j==3){
            //do nothing
            return(arrMatrix[i][j]);
        }else{
            i++;
            j++;
            return(arrMatrix[i][j]);
        }
    }
    else if(x>800 && (y>300 && y<600)){//////////////////////////Down
        if(i==3){
            //do nothing
            return(arrMatrix[i][j]);
        }else{
            i++;
            return(arrMatrix[i][j]);
        }
    }
    else if(x>800 && y<200){////////////////////////Down Left Diagonal 
        if(i==3 || j==0){
            //do nothing
            return(arrMatrix[i][j]);
        }else{
            i++;
            j--;
            return(arrMatrix[i][j]);
        }
    }

    else if((x>300 && x<600) && y<200){/////////////////////////Left
        if(j==0){
            //do nothing
            return(arrMatrix[i][j]);
        }else{
            j--;
            return(arrMatrix[i][j]);
        }
    }else if(x<200 && y<200){////////////////////////Left Up Diagonal 
        if(i==0 || j==0){
            //do nothing
            return(arrMatrix[i][j]);
        }else{
            i--;
            j--;
            return(arrMatrix[i][j]);
        }
    }

    else if(x<200 && (y>300 && y<600)){////////////////////////Up
        if(i==0){
            //do nothing
            return(arrMatrix[i][j]);
        }else{
            i--;
            return(arrMatrix[i][j]);
        }
    }else if(x<200 && y>800){////////////////////////Right Up Diagonal 
        if(i==0 || j==3){
            //do nothing
            return(arrMatrix[i][j]);
        }else{
            i--;
            j++;
            return(arrMatrix[i][j]);
        }
    }
    //*/
    else{
        return(arrMatrix[i][j]);
    }
    
} 