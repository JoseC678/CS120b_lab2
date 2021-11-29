#ifndef JoyStick_H
#define JoyStick_H

#endif //JoyStick_H



//Function for determining which direction the joystick is moving
//For a 4x4 matrix using a shift register.
unsigned short XY_Position(unsigned short x,unsigned short y);
int arrMatrix[4][4] = {{0b10000111,0b10001011,0b10001101,0b10001110},
                       {0b01000111,0b01001011,0b01001101,0b01001110},
                       {0b00100111,0b00101011,0b00101101,0b00101110},
                       {0b00010111,0b00011011,0b00011101,0b00011110}};


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
unsigned char ii = 0;
unsigned char jj = 0;
unsigned short output=0;
unsigned short currPosition = 0b10010110; 


unsigned short XY_Position(unsigned short x,unsigned short y);




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
        if(jj==3){
            //do nothing
            return(arrMatrix[ii][jj]);
        }else{
            jj++;
            return(arrMatrix[ii][jj]);
        }
        
    }
    //*
    else if(x>604 && y>700){////////////////////////Right Down Diagonal 
        if(ii==3 || jj==3){
            //do nothing
            return(arrMatrix[ii][jj]);
        }else{
            ii++;
            jj++;
            return(arrMatrix[ii][jj]);
        }
    }
    else if(x>800 && (y>300 && y<600)){//////////////////////////Down
        if(ii==3){
            //do nothing
            return(arrMatrix[ii][jj]);
        }else{
            ii++;
            return(arrMatrix[ii][jj]);
        }
    }
    else if(x>800 && y<200){////////////////////////Down Left Diagonal 
        if(ii==3 || jj==0){
            //do nothing
            return(arrMatrix[ii][jj]);
        }else{
            ii++;
            jj--;
            return(arrMatrix[ii][jj]);
        }
    }

    else if((x>300 && x<600) && y<200){/////////////////////////Left
        if(jj==0){
            //do nothing
            return(arrMatrix[ii][jj]);
        }else{
            jj--;
            return(arrMatrix[ii][jj]);
        }
    }else if(x<200 && y<200){////////////////////////Left Up Diagonal 
        if(ii==0 || jj==0){
            //do nothing
            return(arrMatrix[ii][jj]);
        }else{
            ii--;
            jj--;
            return(arrMatrix[ii][jj]);
        }
    }

    else if(x<200 && (y>300 && y<600)){////////////////////////Up
        if(ii==0){
            //do nothing
            return(arrMatrix[ii][jj]);
        }else{
            ii--;
            return(arrMatrix[ii][jj]);
        }
    }else if(x<200 && y>800){////////////////////////Right Up Diagonal 
        if(ii==0 || jj==3){
            //do nothing
            return(arrMatrix[ii][jj]);
        }else{
            ii--;
            jj++;
            return(arrMatrix[ii][jj]);
        }
    }
    //*/
    else{
        return(arrMatrix[ii][jj]);
    }
    
} 