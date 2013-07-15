// Erzeut ein RC Summen Signal

#include <avr/interrupt.h>
#include <avr/io.h>
#include "usart.h"
#include "rc.h"
int value,a,b;
int fit_poti(value,a,b)
{
  if (value >= 0)
  {
    return (value*a/100);
  }
  else
  {
    return (value*b/100);
  }
}
  


int main (void) 
{
  //usart_init(9600); // Serielle Schnittstelle initialisieren
  
  DDRD = (1<<PD7)|(1<<PD6)|(1<<PD2);

  //usart_write("RC_Summen_Signal_gen");

  rc_sum_init (); 
  sei();
    
  ADMUX = (1<<REFS0);  
  ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
 
  //PORTD |= (1<<PD6);
  //PORTD &= ~(1<<PD7);
  
  rc_ch[4]= -100;  
  rc_ch[5]= -100;
  rc_ch[6]= -100;
  rc_ch[7]= -100;
  rc_ch[8]= -100;
  
  //uint16_t adcval;
  //ADC_Init();
  while(1)
  { 
    ADMUX = (0<<MUX2)|(1<<MUX1)|(0<<MUX0);   //AD Channel 1 (Roll)
    ADCSRA |= (1<<ADSC);
    while (ADCSRA & (1<<ADSC));    
    rc_ch[3] = fit_poti((128 - ((ADCW>>2)&0xff)),180,185);
    
    ADMUX = (0<<MUX2)|(1<<MUX1)|(1<<MUX0);   //AD Channel 2 (Gas)
    ADCSRA |= (1<<ADSC);
    while (ADCSRA & (1<<ADSC));
    rc_ch[1] =fit_poti((128 - ((ADCW>>2)&0xff)),170,195);
    
    
    ADMUX = (1<<MUX2)|(0<<MUX1)|(0<<MUX0);   //AD Channel 4 (Gieren)
    ADCSRA |= (1<<ADSC);
    while (ADCSRA & (1<<ADSC));
    rc_ch[2] = fit_poti((-128 + ((ADCW>>2)&0xff)),203,145); 
    
    ADMUX = (1<<MUX2)|(0<<MUX1)|(1<<MUX0); //AD Channel 5 (Gier)
    ADCSRA |= (1<<ADSC);
    while (ADCSRA & (1<<ADSC));
    rc_ch[0] = fit_poti((128 - ((ADCW>>2)&0xff)),(185),(155)); 
    
    //ADMUX = (1<<MUX2)|(1<<MUX1)|(1<<MUX0); //AD Channel 0 (On/Off)
    //ADCSRA |= (1<<ADSC);
    //while (ADCSRA & (1<<ADSC));
    //value = (128 - ((ADCW>>2)&0xff));
    //if (value >= 10)
    //{
      //rc_ch[4] = 100;
    //}
    //else if (value <= 10)
    //{
      //rc_ch[4] = -100;
    //}
    //else rc_ch[4] = 0;


  }
}

