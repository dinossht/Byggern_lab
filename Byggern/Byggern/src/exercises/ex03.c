/*
 * ex03.c
 *
 * Created: 20.09.2017 10:59:43
 *  Author: hermansu
 */ 


#include "ex03.h"
#include "../drivers/joystick.h"

void ex03()
{
	while(1)
	{

	joystick_getPosition();
	printf("X read from ADC is %8d \n", current_joystick_postion.X);
	printf("Y read from ADC is %8d \n", current_joystick_postion.Y);
	}
}