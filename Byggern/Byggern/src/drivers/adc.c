/*
 * adc.c
 *
 * Created: 11.09.2017 08:30:18
 *  Author: dinossht
 */ 

#include "adc.h"

uint8_t adc_read(channel_t ch)
{
	
	volatile char *ext_ram = (char *) 0x1400; // Start address for the ADC
	ext_ram[0] = ch;
	
	_delay_us(50);
	
	return ext_ram[0];

}