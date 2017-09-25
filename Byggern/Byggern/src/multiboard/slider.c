/*
 * slider.c
 *
 * Created: 25.09.2017 10:25:41
 *  Author: dinossht
 */ 

#include "settings.h"
#include <util/delay.h>
#include "../drivers/adc.h"
#include "slider.h"

#define SLIDER_CONV_FACT 100

static void slider_convertPos(int16_t* rawVal, int16_t rawValMax, int16_t convValMax);

int16_t slider_getPos(slider_t slider)
{
	int16_t adcVal = 0;
	
	switch(slider)
	{
		case SLIDER_LEFT:
			adcVal = adc_read(CH_3);
			break;
			
		case SLIDER_RIGHT:
			adcVal = adc_read(CH_4);
			break;	
	}
 	slider_convertPos(&adcVal, ADC_MAX, SLIDER_CONV_FACT);	_delay_us(100);
	return adcVal;
}

static void slider_convertPos(int16_t* rawVal, int16_t rawValMax, int16_t convValMax)
{
	*rawVal = (*rawVal) * convValMax / rawValMax; 
}
