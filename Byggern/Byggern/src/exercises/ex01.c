/*
 * ex01.c
 *
 * Created: 04.09.2017 14:14:22
 *  Author: Lars
 */ 

#include <stdio.h>
#include <util/delay.h>	  
#include "../drivers/led.h"
#include "ex01.h"

void ex01()
{
	int cnt = 0;
	while(1)
	{
		led_toggle();
		printf("BYGGERNBOiZ %i\n", cnt++);
		_delay_ms(500);
	}
}