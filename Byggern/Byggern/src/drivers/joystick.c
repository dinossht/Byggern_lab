/*
 * joystick.c
 *
 * Created: 22.09.2017 19:09:59
 *  Author: dinossht
 */ 


#include <util/delay.h>
#include <stdio.h>
#include "adc.h"
#include "joystick.h"

#define ADC_MAX 255
#define CONV_FACT 100

int16_t offset_x = 0;
int16_t offset_y = 0;


static void joystick_convertPos(int16_t* rawVal, int16_t rawValMax, int16_t convValMax);

void joystick_calib()
{
	printf("Don't touch! Joystick is calibrating...\n");
	offset_x = joystick_getPos(POS_X);
	offset_y = joystick_getPos(POS_Y);
	printf("Joystick is calibrated\n");
}
// 
// int8_t joystick_getPos(pos_t pos)
// {
// 	switch(pos)
// 	{
// 		case POS_X:
// 			int16_t data = adc_read(CH_2);
// 			joystick_convertPos(-100, 100, int16_t* adc_val);
// 			break;
// 			
// 		case POS_Y:
// 			int16_t data = adc_read(CH_1);
// 			joystick_convertPos(-100, 100, int16_t* adc_val);
// 			break;
// 	}	
// }
// 
// joystick_dir_t joystick_getDir(void)
// {
// 	
// }



int16_t joystick_getPos(pos_t pos)
{
	int16_t adcVal = 0;
	switch(pos)
	{
		case POS_X:
			adcVal = adc_read(CH_2);
			adcVal -=  offset_x; 
			break;
			
		case POS_Y:
			adcVal = adc_read(CH_1);
			adcVal -=  offset_y; 
			break; 
	}
	joystick_convertPos(&adcVal, ADC_MAX, CONV_FACT);
	_delay_us(100);
	return adcVal;
}

// 
// void joystick_getDir()
// {
// 	//TODO
// }

static void joystick_convertPos(int16_t* rawVal, int16_t rawValMax, int16_t convValMax)
{
  	*rawVal -= rawValMax / 2; // Move offset 	 
  	*rawVal = 2 * convValMax * (*rawVal) / rawValMax; // Convert 	
}
