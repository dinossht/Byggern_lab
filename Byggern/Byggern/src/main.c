 
#include "settings.h"
 
#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>
#include "drivers/uart.h"


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

