/*
 * uart.c
 *
 * Created: 04.09.2017 09:28:55
 *  Author: dinossht
 */ 

#include <asf.h>

#include "uart.h"
#include "../settings.h"
#include "stdio.h"

#define BAUD 9600

// UART0 initialization routine
void uart_init()
{
	/* Set UART baudrate */
	UBRR0L = (F_CPU / 16 / BAUD - 1);
	
	/* Enable reciever and transimitter */
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	
	/* Frame format: 8data */
	UCSR0C |= (1 << URSEL0) | (1 << UCSZ01) | (1 << UCSZ00);
	
	/* Enable STDIO */
	fdevopen((void*)uart0_putchar, (void*)uart0_getchar);
}

// UART transmission routine
void uart0_putchar(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)));
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

// UART receive routine
unsigned char uart0_getchar()
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)));
	
	/* Get and return received data from buffer */
	return UDR0;
}
