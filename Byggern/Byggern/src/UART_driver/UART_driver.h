/*
 * UART_driver.h
 *
 * Created: 04.09.2017 09:19:21
 *  Author: dinossht
 */ 


#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

// #define F_CPU 8000000UL	// Internal clock speed
#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1 // Baud Rate Register Setting

void UART_Init(void);
void UART_Transmit(unsigned char data);
unsigned char UART_Receive(void);

// UART Initialization routine
void UART_Init()
{
	/* Set UART baudrate */
	UBRR1H = (unsigned char) (MYUBRR >> 8);
	UBRR1L = (unsigned char) MYUBRR;
	
	/* Enable reciever and transimitter */
	UCSR1B = (1 << TXEN1) | (1 << RXEN1);
	
	/* Frame format: 8data */
	UCSR1C = (1 << URSEL1) | (1 << UCSZ10) | (1 << UCSZ00);
	
	/* 2 stop bit */
	UCSR1C |= (1 << USBS1);
	
	/* Clock polarity must be set to 0 for asynchronous mode */
	UCSR1C &= ~(1 << UCPOL0);
}
?
// UART transmission routine
void UART_Transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0C & (1 << UDRE0)));
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
?
// UART recieve routine
unsigned char UART_Receive()
{
	/* Wait for data to be received */
	while (!(UCSR0C & (1 << RXC0)));
	
	/* Get and return received data from buffer */
	return UDR0;
}

#endif /* UART_DRIVER_H_ */