/*
 * joystick.c
 *
 * Created: 22.09.2017 19:09:59
 *  Author: dinossht
 */ 

#include "settings.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "../drivers/adc.h"
#include "joystick.h"

#define JOY_CONV_FACT 100

int16_t calib_offset_x = 0;
int16_t calib_offset_y = 0;

static void joystick_convertPos(int16_t* rawVal, int16_t rawValMax, int16_t convValMax);

void joystick_calib()
{
	printf("Don't touch! Joystick is calibrating...\n");
	
	calib_offset_x = joystick_getPos(POS_X);
	calib_offset_y = joystick_getPos(POS_Y);
	
	printf("Joystick is calibrated\n");
}

int16_t joystick_getPos(pos_t pos)
{
	int16_t adcVal = 0;
	switch(pos)
	{
		case POS_X:
			adcVal = adc_read(CH_2) - calib_offset_x;  
			break;
			
		case POS_Y:
			adcVal = adc_read(CH_1) - calib_offset_y; 
			break; 
	}
	joystick_convertPos(&adcVal, ADC_MAX, JOY_CONV_FACT);
	_delay_us(100);
	
	return adcVal;
}

#define NEUTRAL_RADIUS 5
joystick_dir_t joystick_getDir()
{
	int16_t pos_x = joystick_getPos(POS_X);	
	int16_t pos_y = joystick_getPos(POS_Y);
	
	if(abs(pos_x) < NEUTRAL_RADIUS && abs(pos_y) < NEUTRAL_RADIUS)
		return NEUTRAL;
	
	else if(abs(pos_x) > abs(pos_y))
		return pos_x > 0 ? RIGHT : LEFT;
	
	else if(abs(pos_x) < abs(pos_y))
		return pos_y > 0 ? UP : DOWN;
	
	return NEUTRAL;
}

static void joystick_convertPos(int16_t* rawVal, int16_t rawValMax, int16_t convValMax)
{
	*rawVal -= rawValMax / 2; // Move offset
	*rawVal = 2 * convValMax * (*rawVal) / rawValMax; // Convert 
}

