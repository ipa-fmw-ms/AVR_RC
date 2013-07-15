/*----------------------------------------------------------------------------
 Copyright:      Radig Ulrich  mailto: mail@ulrichradig.de
 Author:         Radig Ulrich
 Remarks:        
 known Problems: none
 Version:        24.10.2007
 Description:    RS232 Routinen
----------------------------------------------------------------------------*/

#ifndef _UART_H
	#define _UART_H

	#define USART_ECHO	1
	
	#define BUFFER_SIZE	50
	
	volatile unsigned char buffercounter;
	char usart_rx_buffer[BUFFER_SIZE];
	
	char *rx_buffer_pointer_in;
	char *rx_buffer_pointer_out;
	
	struct {
			volatile unsigned char usart_ready:1;
			volatile unsigned char usart_rx_ovl:1;
			volatile unsigned char usart_disable:1; //benötigt für ftp2com
			}usart_status ;
	
	//----------------------------------------------------------------------------
	
	#include <avr/interrupt.h>
	#include <avr/pgmspace.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <ctype.h>
	#include <string.h>
	#include <avr/io.h>
	
	//----------------------------------------------------------------------------
	
	//Die Quarzfrequenz auf dem Board
	#define F_CPU 800000UL
	
	//Anpassen der seriellen Schnittstellen Register wenn ein ATMega128 benutzt wird
	#if defined (__AVR_ATmega128__)
		#define USR UCSR0A
		#define UCR UCSR0B
		#define UDR UDR0
		#define UBRR UBRR0L
		#define USART_RX USART0_RX_vect 
	#endif
	
	#if defined (__AVR_ATmega644__)
		#define USR UCSR0A
		#define UCR UCSR0B
		#define UBRR UBRR0L
		#define EICR EICRB
		#define TXEN TXEN0
		#define RXEN RXEN0
		#define RXCIE RXCIE0
		#define UDR UDR0
		#define UDRE UDRE0
		#define USART_RX USART0_RX_vect   
	#endif
	
	#if defined (__AVR_ATmega32__)
		#define USR UCSRA
		#define UCR UCSRB
		#define UBRR UBRRL
		#define EICR EICRB
		#define USART_RX USART_RXC_vect  
	#endif
	
	#if defined (__AVR_ATmega8__)
		#define USR UCSRA
		#define UCR UCSRB
		#define UBRR UBRRL
        #define USART_RX USART_RXC_vect 
	#endif
	
	#if defined (__AVR_ATmega88__)
		#define USR UCSR0A
		#define UCR UCSR0B
		#define UBRR UBRR0L
		#define TXEN TXEN0
		#define UDR UDR0
		#define UDRE UDRE0
	#endif
	//----------------------------------------------------------------------------
	
	void usart_init(unsigned int baudrate); 
	void usart_write_char(char c);
	void usart_write_str(char *str);
	
	void usart_write_P (const char *Buffer,...);
	#define usart_write(format, args...)   usart_write_P(PSTR(format) , ## args)
	
	//----------------------------------------------------------------------------

#endif //_UART_H
