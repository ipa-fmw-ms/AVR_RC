// Erzeut ein RC Summen Signal

#include <avr/interrupt.h>
#include <avr/io.h>
#include "usart.h"
#include "rc.h"

int main (void) 
{
  usart_init(9600); // Serielle Schnittstelle initialisieren
  
  DDRD = (1<<PD7)|(1<<PD6)|(1<<PD2);

  usart_write("RC_Summen_Signal_gen");

  rc_sum_init (); 
  sei();
    
  ADMUX = (1<<REFS0)|(1<<MUX1)|(1<<MUX0);  
  ADCSRA = (1<<ADEN)|(1<<ADSC);
 
  PORTD |= (1<<PD6);
  PORTD &= ~(1<<PD7);
  
  rc_ch[4]= -100;  
  rc_ch[5]= -100;
  rc_ch[6]= -100;
  rc_ch[7]= -100;
  rc_ch[8]= -100;
 
  while(1)
  { 
    ADMUX = (1<<REFS0)|(1<<MUX0);   //AD Channel 1 (Roll)
    for(unsigned int b = 0; b < 6000;b++){};
    rc_ch[2] = 128 - ((ADC>>2)&0xff);
      
    ADMUX = (1<<REFS0)|(1<<MUX1);   //AD Channel 2 (Pitch)
    for(unsigned int b = 0; b < 6000;b++){};
    rc_ch[1] = - 128 + ((ADC>>2)&0xff);
   
    ADMUX = (1<<REFS0)|(1<<MUX2);   //AD Channel 4 (Gieren)
    for(unsigned int b = 0; b < 6000;b++){};
    rc_ch[3] = 128 - ((ADC>>2)&0xff); 
    
    ADMUX = (1<<REFS0)|(1<<MUX2)|(1<<MUX0); //AD Channel 5 (Gas)
    for(unsigned int b = 0; b < 6000;b++){};
    rc_ch[0] = -128 + ((ADC>>2)&0xff); 

    ADMUX = (1<<REFS0)|(1<<MUX1)|(1<<MUX0); //AD Channel 0 (ON/OFF)
    for(unsigned int b = 0; b < 6000;b++){};
    if (((ADC>>2)&0xff)<128)
    {
        if (rc_ch[5] > 0)
        {
            rc_ch[5]= -100;
        }
        else
        {
            rc_ch[5]= 100;
        }
        PORTD ^= (1<<PD7)|(1<<PD6);
        for(unsigned int b = 0; b < 6000;b++){};
        while(((ADC>>2)&0xff)<128);
    }
  }
}

