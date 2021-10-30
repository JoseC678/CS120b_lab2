/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #8  Exercise #1
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
#ifdef _SIMULATE_
#include "simAVRHeader.h"

#endif

void ADC_init(){
    ADCSRA |= (1 << ADEN | (1 << ADSC) | (1 << ADATE));
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    ADC_init();
     unsigned short x = ADC;

    unsigned short temp = ((0x2FF)/8);
    //unsigned short tempD = x;
   
    /* Insert your solution below */
    while (1) {
    x = ADC;

    if(temp >= x ){PORTB = 0x1;}
    else if((temp * 2) >= x){PORTB = 0x03;}
    else if((temp * 3) >= x){PORTB = 0x07;}
    else if((temp * 4) >= x){PORTB = 0x0F;}
    else if((temp * 5) >= x){PORTB = 0x1F;}
    else if((temp * 6) >= x){PORTB = 0x3F;}
    else if((temp * 7) >= x){PORTB = 0x7F;}
    else if((temp * 8) >= x){PORTB = 0xFF;}

    }
    return 1;
}
