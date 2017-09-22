/*
 * address_decoder.c
 *
 * Created: 11.09.2017 14:07:47
 *  Author: dinossht
 */ 

#include <stdlib.h>
#include "stdio.h"
#include "drivers/pio.h"
#include "uart.h"
#include "sram.h"
#include <util/delay.h>

#include "address_decoder.h"

void address_decoder_send(device_t device, uint8_t data, uint16_t memory_index)
{
	switch(device)
	{
		case DEVICE_OLED:
			//
			break;
		
		case DEVICE_ADC:
			//
			break;
			
		case DEVICE_SRAM:
			sram_write(data, memory_index);
			break;
	}
}