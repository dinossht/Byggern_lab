/*
 * hardware_init.c
 *
 * Created: 04.09.2017 14:04:56
 *  Author: Lars
 */ 

#include "hardware_init.h"

#include <asf.h>

#include "drivers/led.h"
#include "drivers/uart.h"

void hardware_init()
{
	board_init();
	uart0_init();
	led_init();
}