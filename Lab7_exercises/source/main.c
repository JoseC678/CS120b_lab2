/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRC = 0xFF; PORTC = 0x00; //LCD data lines
    DDRD = 0xFF; PORTD = 0x00; //LCD control lines

    //Initializes the LCD display
    LCD_init();

    //Starting at position 1 on the LCD screen, writes hello world
    LCD_DisplayString(1, "You dont got the facilities for that big man");


    /* Insert your solution below */
    while (1) {
        continue;

    }
    return 1;
}
