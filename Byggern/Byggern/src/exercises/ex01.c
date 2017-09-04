/*
 * ex01.c
 *
 * Created: 04.09.2017 14:14:22
 *  Author: Lars
 */ 

#include "ex01.h"

#include "settings.h"
#include "drivers/led.h"

#include <asf.h>
#include <stdio.h>
#include <util/delay.h>

void ex01(void)
{
	int cnt = 0;
	while(1)
	{
		led_toggle();
		printf("BYGGERNBOiZ %i\n", cnt++);
		_delay_ms(500);
	}
}