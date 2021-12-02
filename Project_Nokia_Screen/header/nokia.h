#ifndef NOKIA_H
#define NOKIA_H


///Define value bits To activate SPI and MOSI
#define SS PB4
#define RST PB0
#define DC PB1


void SPI_Init();
void SPI_Transmit(char cData);
void init_Screen();
void clear_Screen();
void Snd_Nokia_Instructions(char command);
void Snd_Nokia_Data(char *data, int invert);




void SPI_Init(){
    //From the data sheet
    //Enable SPI,MASTR, set clock rate
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_Transmit(char cData){
    //From the Data Sheet
    //Start the transmission
    //Shift each byte by writing it to the SPDR
    SPDR = cData;

    //Wait for transmission to complete
    while(!(SPSR & (1<<SPIF)));
}
void Snd_Nokia_Instructions(char command){
    //Set D/C to Zero to not write to screen and pass instructions.
    PORTB &= ~(1<<DC);

    //When SS is held low than the SPI is activated, and MISO becomes an ouput
    PORTB &= ~(1<<SS);

    //Send data command to the SPDR register and shift each bit
    SPI_Transmit(command);

    //When SS id driven high. all pins are inputs, and the SPI is passive, means
    // that it will not recieve incoming data
    PORTB |= (1<<SS); 
}

void Snd_Nokia_Data(char *data, int invert){
    unsigned char temp = 0x00;
    //enable DC to high to enable screen for data write to Y and X
    PORTB |= (1<<DC);

    //When SS is held low than the SPI is activated, and MISO becomes an ouput
    PORTB &= ~(1<<SS);

    //get the length of the char character to display each character in a 
     // down up sequence starting with the first 6 column
    int length = strlen(data);

    for(int x=0; x<length; x++){//Cylce through each character
        for(int y=0; y<6; y++){
            temp = (invert) ? ~(ASCII[data[x]-32][y]) : (ASCII[data[x]-32][y]);
            //Pass each column of data that consists of 6 columns that make up The character
            //Subtract 32 since the library only has ASCII characters 32 - 125 and 
            //the 2D array starts at 0 = 32 to offset it on the right character.
            SPI_Transmit(temp);
        }
    }
    //When SS is driven high, all pins are inputs, and the SPI is passive, means
    //That it will not receive incoming dat
    PORTB |= (1<<SS);
}

void init_Screen(){
    //To activate Reset RST must be set low than back to high
    PORTB &= ~(1<<RST);
    _delay_ms(110); //Stated in the data sheet the there must be a delay
                    //after RST is set to low than high
    PORTB |= (1<<RST);

    //Function set DB5=1 and H=1 extended instruction set to preset 
    //the screen to specific parameters
    Snd_Nokia_Instructions(0x21);

    //Set Vop
    Snd_Nokia_Instructions(0xC0);

    //Set Voltage Bias to inverse video mode
    Snd_Nokia_Instructions(0x13);

    //Function Set PD = 0 and V = 0, Select Normal Mode instruction set
    Snd_Nokia_Instructions(0x20);

    //Display control set normal mode (D = 1 and E = 0)
    Snd_Nokia_Instructions(0x0C);
}

void clear_Screen(){
    //When SS is held low than the SPI is activated, and MISO becomes an ouput
    PORTB &= ~(1<<SS);
    PORTB |= (1<<DC);

    for(int t=0; t< 504; t++){
        //Clearing out each column since there are 
        SPI_Transmit(0x00); 
    }
    PORTB &= ~(1<<DC);

    //When SS is driven high, all pins are inputs, and the SPI is passive, means
    //That it will not receive incoming dat
    PORTB |= (1<<SS);
}


#endif //JoyStick_H