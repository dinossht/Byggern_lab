/*
 * joystick.c
 *
 * Created: 22.09.2017 19:09:59
 *  Author: dinossht
 */ 

#include "joystick.h"
#include <util/delay.h>
#define ADC_MAX 255

void joystick_getPosition(void)
{
	int16_t X_val = adc_read(CH_2);

	_delay_us(100);
	int16_t Y_val = adc_read(CH_1);
	
	
	X_val -= (ADC_MAX/2);
	Y_val -= (ADC_MAX/2);
	
	current_joystick_postion.X = X_val; //2 * 100 * X_val/ADC_MAX;
	current_joystick_postion.Y = Y_val; //2 * 100 * Y_val/ADC_MAX;
}

void joystick_getDirection(void)
{
	//TODO
}
