/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
 
#include "settings.h"
 
#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>
#include "drivers/uart.h"

void led_init(void);
void led_toggle(void);

int main (void)
{
	board_init();
	UART0_Init();
	led_init();
	
	while(1)
	{
		led_toggle();
		UART0_Transmit('1');
		//UART0_Transmit('2');
		//UART0_Transmit('3');
		UART0_Transmit('\n');	
		
		UART0_Receive();
		_delay_ms(100);
	}
		
	return 0;
}

void led_init(void)
{
	DDRC = (1 << PINC0);	
}

void led_toggle()
{
	PORTC ^= (1 << PINC0);
}
