/*#######################################################################################
Erzeugen eines RC Summen Signals 

Copyright (C) 2006 Ulrich Radig

#######################################################################################*/

#include "rc.h"


unsigned char rc_channel_counter = 0;
unsigned int rc_channel_sum;
volatile int rc_ch[RC_MAX_CHANNEL];

//############################################################################
//Timer Interrupt Service Routine
ISR (TIMER1_OVF_vect)
//############################################################################
{
  unsigned int tmp;
  PORTD ^= (1<<PIND2);
  
  if (!(PORTD & (1<<PIND2)))
  {
    TCNT1 = TIMER_VALUE_MAX - (MS0_5);
  }
  else
  {
    if (rc_channel_counter == RC_MAX_CHANNEL)
    {
      TCNT1 = TIMER_VALUE_MAX - rc_channel_sum;
      rc_channel_sum = RC_REPETITION_TIME - ((RC_MAX_CHANNEL+1) * MS0_5);
      rc_channel_counter = 0;
    }
    else
    {
      if (rc_ch[rc_channel_counter] > RC_MAX_VALUE)
      {
        rc_ch[rc_channel_counter] = RC_MAX_VALUE;
      }
      if (rc_ch[rc_channel_counter] < RC_MIN_VALUE)
      {
        rc_ch[rc_channel_counter] = RC_MIN_VALUE;
      }
      TCNT1 = TIMER_VALUE_MAX - (RC_OFFSET_TIME + (5 * rc_ch[rc_channel_counter]));
      tmp = (RC_OFFSET_TIME + (5 * rc_ch[rc_channel_counter]));
      rc_channel_sum -= tmp;
      rc_channel_counter ++;
    }
  }
}

//############################################################################
//Diese Routine startet und inizialisiert den Timer
void rc_sum_init (void)
//############################################################################
{
    //Interrupt for the Clock enable  
    TIMSK |= (1<<TOIE1);
    //Setzen des Prescaler auf 8
    TCCR1B |= (1<<CS11); 
    TCNT1 = TIMER_VALUE_MAX - RC_REPETITION_TIME;
    return;
}

 


