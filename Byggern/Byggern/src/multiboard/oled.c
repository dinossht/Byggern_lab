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

/* OLED info: */

// * 128 X 64 pixel display 
// * Segmented into 8 horisontal pages 
// * Able to write minimum 8 pixels at a time
// * Writes to 8 pixel in a column at once
// * Uses standard 8 x 8 pixel size fonts, can be modified

// Oled data and command address
#define OLED_CMD_ADDR		0x1000
#define OLED_DATA_ADDR		0x1200

// Bit mask
#define LOWER_BITS_MASK		0x0F
#define HIGHER_BITS_MASK	0xF0

// Oled dimensions
#define OLED_PIXEL_WIDTH	128
#define OLED_PIXEL_HEIGHT	64
#define OLED_NR_OF_PAGES	8

void oled_turn(oled_state_t state)
{
	volatile char *ext_ram = (char *) 0x0000; 
	
	switch(state)
	{
		case OLED_ON:
			ext_ram[OLED_CMD_ADDR] = (0xaf); 
			break;
			
		case OLED_OFF:
			ext_ram[OLED_CMD_ADDR] = (0xae); 
			break;			
	}
}

void oled_init()
{
	volatile char *ext_ram = (char *) 0x0000; 
	
	// Fundemental commands
	ext_ram[OLED_CMD_ADDR] = (0xae); // display off
	ext_ram[OLED_CMD_ADDR] = (0xa1); // segment remap
	ext_ram[OLED_CMD_ADDR] = (0xda); // common pads hardware: alternative
	ext_ram[OLED_CMD_ADDR] = (0x12);    
	ext_ram[OLED_CMD_ADDR] = (0xc8); // common output scan direction:com63~com0
	ext_ram[OLED_CMD_ADDR] = (0xa8); // multiplex ration mode:63
	ext_ram[OLED_CMD_ADDR] = (0x3f);    
	ext_ram[OLED_CMD_ADDR] = (0xd5); // display divide ratio/osc. freq. mode
	ext_ram[OLED_CMD_ADDR] = (0x80);    
	ext_ram[OLED_CMD_ADDR] = (0x81); // contrast control
	ext_ram[OLED_CMD_ADDR] = (0x50);    
	ext_ram[OLED_CMD_ADDR] = (0xd9); // set pre-charge period
	ext_ram[OLED_CMD_ADDR] = (0x21);
	
	// Set Memory Addressing Mode
	ext_ram[OLED_CMD_ADDR] = (0x20); // Page addressing mode
	ext_ram[OLED_CMD_ADDR] = (0x02);
	
	// Set page start address
	ext_ram[OLED_CMD_ADDR] = (0xB0);							   
	
	// Set lower start column address
	ext_ram[OLED_CMD_ADDR] = (0x00);
	
	// Set higher start column address
	ext_ram[OLED_CMD_ADDR] = (0x10); 	  
	
	// Fundemental commands	
	ext_ram[OLED_CMD_ADDR] = (0xdb); // VCOM deselect level mode
	ext_ram[OLED_CMD_ADDR] = (0x30);
	ext_ram[OLED_CMD_ADDR] = (0xad); // master configuration
	ext_ram[OLED_CMD_ADDR] = (0x00);
	ext_ram[OLED_CMD_ADDR] = (0xa4); // out follows RAM content
	ext_ram[OLED_CMD_ADDR] = (0xa6); // set normal display
	ext_ram[OLED_CMD_ADDR] = (0xaf); // display on
}

#define OLED_LINE_CMD_MASK 0x3F
/* line nr [0:63] */
void oled_goToline(uint8_t lineNr)
{
	volatile char *ext_ram = (char *) 0x0000;
	
	ext_ram[OLED_CMD_ADDR] = (0x40) | (lineNr & OLED_LINE_CMD_MASK);			 
}

/* col nr [0:127] */
void oled_goToColumn(uint8t_t colNr)
{
	volatile char *ext_ram = (char *) 0x0000;	

	ext_ram[OLED_CMD_ADDR] = (0x10) | (colNr & LOWER_BITS_MASK);
	ext_ram[OLED_CMD_ADDR] = (0x00) | (colNr & HIGHER_BITS_MASK >> 4);
}

/* row nr [0:63], col nr [0:127] */
void oled_pos(uint8_t lineNr, uint8_t colNr)
{	
	oled_goToline(lineNr);
	oled_goToColumn(colNr);
}

void oled_clearLine(uint8_t lineNr)
{
	oled_pos(lineNr, 0);
	for(uint8_t i = 0; i < OLED_PIXEL_WIDTH; i++)
	{
		ext_ram[OLED_DATA_ADDR] = 0x00;		
	}		
}

void oled_clear()
{
	for(uint8_t i = 0; i < OLED_NR_OF_PAGES; i++)
	{
		oled_clearLine(i);
	}
}

/* val [0:255] */
void oled_setContrast(uint8_t contrastVal)
{
	volatile char *ext_ram = (char *) 0x0000;	
	
	ext_ram[OLED_CMD_ADDR] = (0x81);
	ext_ram[OLED_CMD_ADDR] = contrastVal;
}

#define FONT_WIDTH 8
#define ASCHII_OFFSET -32
void oled_putChar(char charr, uint8_t lineNr, uint8_t colNr)
{
	oled_pos(lineNr, colNr * 8);
	
	volatile char *ext_ram = (char *) 0x0000; 
	
	for (int i = 0; i < FONT_WIDTH; i++)
	{
		ext_ram[OLED_DATA_ADDR] = pgm_read_word(&font8[charr + ASCHII_OFFSET][i]);
	}		
}

void oled_print(char* string, uint8_t lineNr, uint8_t colNr)
{
	uint8_t index = 0;
	char* currentChar = string[index];
	
	while(currentChar != '\0')
	{
		currentChar = string[index];
		oled_putChar(currentChar, lineNr, colNr + index);
			
		index++;
	}
}




