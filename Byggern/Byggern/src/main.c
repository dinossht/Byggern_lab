#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>
#include "drivers/uart.h"


int main (void)
{
	board_init();
	UART0_Init();
	led_init();
	
		
	return 0;
}

