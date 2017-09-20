/*
 * ex03.c
 *
 * Created: 20.09.2017 10:59:43
 *  Author: hermansu
 */ 


#include <asf.h>
#include <util/delay.h>
#include <stdio.h>
#include "exercises/ex03.h"
#include "drivers/adc.h"
#include "drivers/uart.h"


void ex03()
{
	
	/* To talk with ADC
		Chip select goes low with Write:
		What address is written to determines the configuration of the ADC
		Wait for interrupt or for approx. 50 uS and then read  with CS low
	*/
	uint8_t data = 0x04; // MSB 0 for single-ended 0x04=CH1, 0x05=CH2, 0x06 = CH3, 0x07 = CH4
	uint8_t offset = 0x00; 
	while(1)
	{
	adc_write(data, offset);
	_delay_us(40);
	uint8_t adc_voltage = adc_read(offset);
	printf("Read from ADC is %8d \n", adc_voltage);
	}
	
	
	
}