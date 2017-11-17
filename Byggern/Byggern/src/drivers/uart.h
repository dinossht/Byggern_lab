/*
 * uart.h
 *
 * Created: 04.09.2017 09:19:21
 *  Author: dinossht
 */ 


#ifndef UART_H_
#define UART_H_

void uart_init(void);
void uart0_putchar(unsigned char data);
unsigned char uart0_getchar(void);

#endif /* UART_H_ */