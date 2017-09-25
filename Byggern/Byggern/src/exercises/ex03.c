/*
 * ex03.c
 *
 * Created: 20.09.2017 10:59:43
 *  Author: hermansu
 */ 

#include <stdio.h>
#include "../drivers/joystick.h"
#include "ex03.h"

void ex03()
{
	joystick_calib();
	while(1)
	{
		int16_t x = joystick_getPos(POS_X);
		int16_t y = joystick_getPos(POS_Y);
		printf("X read from ADC is %8d \n", x);
		printf("Y read from ADC is %8d \n", y);
	}
}