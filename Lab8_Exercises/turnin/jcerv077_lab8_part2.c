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
    unsigned short tempB = x;
    unsigned short tempD = x;
   
    /* Insert your solution below */
    while (1) {
    x = ADC;
    tempB = x;
    tempD = x;
    PORTB = (char)(tempB & 0xFF); //PORTB = 0xFF
    PORTD = (char)((tempD >> 8) & 0x03);//PORTD == 0x03 shift over 8 right ;

    }
    return 1;
}
