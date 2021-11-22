#ifndef ADC_H
#define ADC_H

void InitADC(){
    ADMUX=(1<<REFS0);//Set REFS0 on for the ADMUX to select the AVCC with external 
                     //capaitor at AREF pin

    //
    ADCSRA=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); 	
    //ADEN = on than it enables ADC  to begin the conversion
    //Set ADPS0/1/2 to 1 so that we get the full 10 bit rsolution
    //of CK/128 inbetween 50kHz and 200kHz to get maximum resolution
}

unsigned short ADCvalue(unsigned char channel){	
    InitADC(); //set the correct pins to begin the 10 bit value
    channel &=0x01;//Since we are only using 2 ADC channels and select 1 of them       
    ADMUX = (ADMUX & 0xFF)|channel; //clear ADMUX to set the corect ADC 
    ADCSRA|=(1<<ADSC); //Enable ADC 
    while((ADCSRA)&(1<<ADSC));  //Wait unit ADSC is set in ADCSRA
    return(ADC);   //Return        
}

#endif //ADC_H