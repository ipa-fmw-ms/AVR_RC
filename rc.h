/*#######################################################################################
Erzeugen eines RC Summen Signals 

Copyright (C) 2006 Ulrich Radig

#######################################################################################*/

#ifndef _RC_H
 #define _RC_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include "usart.h"

#define RC_MAX_VALUE 100
#define RC_MIN_VALUE -100
#define TIMER_VALUE_MAX 65535
#define RC_MAX_CHANNEL 9
#define RC_REPETITION_TIME 25000 //25 ms
#define MS0_5 500
#define RC_OFFSET_TIME 1000

unsigned char rc_channel_counter;
unsigned int rc_channel_sum;
extern volatile char rc_ch[RC_MAX_CHANNEL];

extern void rc_sum_init (void);

#endif //_CLOCK_H
