/*
 * address_decoder.c
 *
 * Created: 11.09.2017 14:07:47
 *  Author: dinossht
 */ 

#include "settings.h"
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "stdio.h"
#include "drivers/pio.h"
#include "uart.h"
#include "sram.h"
#include "address_decoder.h"

// Start address for devices
#define OLED_ADDR_OFFSET	0x1000
#define ADC_ADDR_OFFSET		0x1400
#define SRAM_ADDR_OFFSET	0x1800

void address_decoder_enable(device_t device)
{
	printf("Starting address_solver test...\n");
	volatile char *ext_ram = (char *) 0x0000;
	uint16_t some_value = 0x00;
	
	switch(device)
	{
		case DEVICE_OLED:
			printf("Sending to ADC...\n\n");
			ext_ram[OLED_ADDR_OFFSET] = some_value;
			break;
		
		case DEVICE_ADC:
			printf("Sending to ADC...\n\n");
			ext_ram[ADC_ADDR_OFFSET] = some_value;
			break;
			
		case DEVICE_SRAM:
			printf("Sending to SRAM...\n\n");
			ext_ram[SRAM_ADDR_OFFSET] = some_value;
			break;
	}
}