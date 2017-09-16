/*
 * address_solver.c
 *
 * Created: 11.09.2017 14:07:47
 *  Author: dinossht
 */ 
#include <stdlib.h>
#include <stdint.h>
#include "stdio.h"
#include "drivers/pio.h"
#include "uart.h"
#include "sram.h"
#include <util/delay.h>

void address_solver_test()
{
	uint16_t offset = 0;
	uint16_t some_value = 0x00;
	
 	while (1)
	{
		printf("Starting address_solver test...\n");
		//Write to SRAM, mem_area=1800
		printf("Starting SRAM...\n");
	
		volatile char *ext_ram = (char *) 0x1800;
		ext_ram[offset] = some_value;
		_delay_ms(10000);
		//Write to ADC, mem_area=1400
		printf("Starting ADC...\n");
		ext_ram = 0x1400;
		ext_ram[offset] = some_value;
		_delay_ms(10000);
		//Write to OLED Data, mem_area=1200
		printf("Starting OLED Data...\n");
		ext_ram = 0x1200;
		ext_ram[offset] = some_value;
		_delay_ms(10000);
		//Write to OLED Command, mem_area=1000
		printf("OLED Command...\n");
		ext_ram = 0x1000;
		ext_ram[offset] = some_value;
		printf("Ending Address_solver test...\n");
		_delay_ms(10000);
	
	}
}

