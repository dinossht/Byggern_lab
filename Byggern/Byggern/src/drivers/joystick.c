/*
 * joystick.c
 *
 * Created: 22.09.2017 19:09:59
 *  Author: dinossht
 */ 


#include <util/delay.h>
#include "adc.h"
#include "joystick.h"

#define ADC_MAX 255

void joystick_convertPos(int16_t* raw_val, int16_t raw_value_min, int16_t raw_value_max, int16_t conv_val_min, int16_t conv_val_max, );

void joystick_calib()
{
	
}

int8_t joystick_getPos(pos_t pos)
{
	switch(pos)
	{
		case POS_X:
			int16_t data = adc_read(CH_2);
			joystick_convertPos(-100, 100, int16_t* adc_val);
			break;
			
		case POS_Y:
			int16_t data = adc_read(CH_1);
			joystick_convertPos(-100, 100, int16_t* adc_val);
			break;
	}	
}

joystick_dir_t joystick_getDir(void)
{
	
}



void joystick_getPos()
{
	int16_t X_val = adc_read(CH_2);

	_delay_us(100);
	int16_t Y_val = adc_read(CH_1);
	
	
	X_val -= (ADC_MAX/2);
	Y_val -= (ADC_MAX/2);
	
	current_joystick_postion.X = X_val; //2 * 100 * X_val/ADC_MAX;
	current_joystick_postion.Y = Y_val; //2 * 100 * Y_val/ADC_MAX;
}

void joystick_getDir()
{
	//TODO
}
