/*
 * oled.c
 *
 * Created: 25.09.2017 11:52:56
 *  Author: dinossht
 */ 

#include "oled.h"
#include "../settings.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "fonts.h"

#define OLED_CMD_ADDR		0x1000
#define OLED_DATA_ADDR		0x1200

void oled_init()
{
	volatile char *ext_ram = (char *) 0x0000; 
	//////////////////////////////////////////////////////////////////////////
	
	// Fundemental commands
	ext_ram[OLED_CMD_ADDR] = (0xae); // display off
	ext_ram[OLED_CMD_ADDR] = (0xa1); //segment remap
	ext_ram[OLED_CMD_ADDR] = (0xda); //common pads hardware: alternative
	ext_ram[OLED_CMD_ADDR] = (0x12);
	ext_ram[OLED_CMD_ADDR] = (0xc8); //common output scan direction:com63~com0
	ext_ram[OLED_CMD_ADDR] = (0xa8); //multiplex ration mode:63
	ext_ram[OLED_CMD_ADDR] = (0x3f);
	ext_ram[OLED_CMD_ADDR] = (0xd5); //display divide ratio/osc. freq. mode
	ext_ram[OLED_CMD_ADDR] = (0x80);
	ext_ram[OLED_CMD_ADDR] = (0x81); //contrast control
	ext_ram[OLED_CMD_ADDR] = (0x50);
	ext_ram[OLED_CMD_ADDR] = (0xd9); //set pre-charge period
	ext_ram[OLED_CMD_ADDR] = (0x21);
	//////////////////////////////////////////////////////////////////////////
	
	// Set Memory Addressing Mode
	ext_ram[OLED_CMD_ADDR] = (0x20); // Page addressing mode
	ext_ram[OLED_CMD_ADDR] = (0x02);
	
	// Set page start address
	ext_ram[OLED_CMD_ADDR] = (0xB0);
	
	// Set lower start column address
	ext_ram[OLED_CMD_ADDR] = (0x00);
	
	// Set higher start column address
	ext_ram[OLED_CMD_ADDR] = (0x10);
		
	//////////////////////////////////////////////////////////////////////////
	ext_ram[OLED_CMD_ADDR] = (0xdb); // VCOM deselect level mode
	ext_ram[OLED_CMD_ADDR] = (0x30);
	ext_ram[OLED_CMD_ADDR] = (0xad); // master configuration
	ext_ram[OLED_CMD_ADDR] = (0x00);
	ext_ram[OLED_CMD_ADDR] = (0xa4); // out follows RAM content
	ext_ram[OLED_CMD_ADDR] = (0xa6); // set normal display
	ext_ram[OLED_CMD_ADDR] = (0xaf); // display on
	//////////////////////////////////////////////////////////////////////////
}

void oled_clear(void)
{
	volatile char *ext_ram = (char *) 0x0000; // Start address for the OLED
	
	for (int y = 0; y < 8; y++)
	{
		// Update page start address
		ext_ram[OLED_CMD_ADDR] = (0xB0) + y;
		
		for (int x = 0; x < 127; x++)
		{
			ext_ram[OLED_DATA_ADDR] = 0x00;
		}
	}
}

void oled_putChar()
{
	volatile char *ext_ram = (char *) 0x0000; // Start address for the OLED	
	ext_ram[OLED_CMD_ADDR] = (0xB2);
	for (int y = 0; y < 8; y++)
	{
		ext_ram[OLED_DATA_ADDR] = pgm_read_word(&font8['H' - 32][y]);
	}
}