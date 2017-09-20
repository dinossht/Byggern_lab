/*
 * adc.c
 *
 * Created: 11.09.2017 08:30:18
 *  Author: dinossht
 */ 

#include <stdlib.h>
#include "stdio.h"
#include "uart.h"

void adc_init()
{
	// configure the ADC
	// Enable interrupt function in ADC
	// 8-bit results
	// Enable a prescaler - determined by the internal or external clock
	
	// Turn on the ADC feature
	
	// Start the first conversation
	
	
	
}

void adc_write(uint8_t data, uint16_t memory_index)
{
	volatile char *ext_ram = (char *) 0x1400; // Start address for the ADC
	ext_ram[memory_index] = data;
	
		
}

uint8_t adc_read(uint16_t memory_index)
{
	volatile char *ext_ram = (char *) 0x1400; // Start address for the ADC
	
	
	return ext_ram[memory_index];
}