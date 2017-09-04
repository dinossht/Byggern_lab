/*
 * ex02.c
 *
 * Created: 04.09.2017 14:14:22
 *  Author: Lars
 */ 

#include "ex02.h"

#include "settings.h"
#include "drivers/led.h"
#include "drivers/latch.h"

#include <asf.h>
#include <stdio.h>
#include <util/delay.h>

void ex02(void)
{
	latch_init();
	
	while(1)
	{
		latch_write(0b00000000);
		_delay_ms(100);
		latch_write(0b00000001);
		_delay_ms(100);
		led_toggle();
	}
}