/*
 * UART_driver.c
 *
 * Created: 04.09.2017 09:28:55
 *  Author: dinossht
 */ 


#include "settings.h"
#include "UART_driver.h"

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1 // Baud Rate Register Setting

// UART0 Initialization routine
void UART0_Init()
{
	/* Set UART baudrate */
	UBRR0H = (unsigned char)(MYUBRR >> 8);
	UBRR0L = (unsigned char)MYUBRR;
	
	/* Enable reciever and transimitter */
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	
	/* Frame format: 8data */
	UCSR0C = (1 << URSEL0) | (1 << UCSZ01) | (1 << UCSZ00);
	
	/* 2 stop bit */
	UCSR0C |= (1 << USBS0);
	
	/* Clock polarity must be set to 0 for asynchronous mode */
	UCSR0C &= ~(1 << UCPOL0);
}

// UART transmission routine
void UART0_Transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)));
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

// UART recieve routine
unsigned char UART0_Receive()
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)));
	
	/* Get and return received data from buffer */
	return UDR0;
}

