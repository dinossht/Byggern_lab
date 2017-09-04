/*
 * UART_driver.h
 *
 * Created: 04.09.2017 09:19:21
 *  Author: dinossht
 */ 


#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <asf.h>

void UART0_Init(void);
void UART0_Transmit(unsigned char data);
unsigned char UART0_Receive(void);

#endif /* UART_DRIVER_H_ */