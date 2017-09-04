/*
 * uart.h
 *
 * Created: 04.09.2017 09:19:21
 *  Author: dinossht
 */ 


#ifndef UART_H_
#define UART_H_

#include <asf.h>

void UART0_Init(void);
void UART0_Transmit(unsigned char data);
unsigned char UART0_Receive(void);

#endif /* UART_H_ */