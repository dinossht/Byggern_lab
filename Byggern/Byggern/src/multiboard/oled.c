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
#include "../drivers/fonts.h"
#include "../drivers/sram.h"

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

static void oled_goToRow(uint8_t lineNr);
static void oled_goToColumn(uint8_t colNr);
static void oled_setPixelCoordinate(uint8_t lineNr, uint8_t colNr);
static void oled_putChar(char charr, uint8_t row, uint8_t col);

void oled_setOnState(oled_state_t state)
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

#define OLED_LINE_CMD_MASK 0x03
/* row nr [0:7] */
static void oled_goToRow(uint8_t row)
{
	volatile char *ext_ram = (char *) 0x0000;
	
	ext_ram[OLED_CMD_ADDR] = (0xB0) + row;		 
}

/* col nr [0:127] */
static void oled_goToColumn(uint8_t col)
{
	volatile char *ext_ram = (char *) 0x0000;	

	ext_ram[OLED_CMD_ADDR] = (0x00) | (col & LOWER_BITS_MASK); // set lower bits
	ext_ram[OLED_CMD_ADDR] = (0x10) | ((col & HIGHER_BITS_MASK) >> 4); // set higher bits	
}

/* row nr [0:7], col nr [0:127] */
static void oled_setPixelCoordinate(uint8_t row, uint8_t col)
{	
	oled_goToRow(row);
	oled_goToColumn(col);
}

void oled_updateScreen()
{
	volatile char *ext_ram = (char *) 0x0000;
	oled_setPixelCoordinate(0,0);
	
	for(uint8_t row = 0; row < OLED_NR_OF_PAGES; row++)
	{
		oled_goToRow(row);
		
		for(uint8_t col = 0; col < OLED_PIXEL_WIDTH; col++)
		{
			uint8_t byte = sram_read(OLED_PIXEL_WIDTH * row + col);
			
			ext_ram[OLED_DATA_ADDR] = byte;
		}
	}
}

void oled_clearScreen()
{
	volatile char *ext_ram = (char *) 0x0000;
	
	for(uint8_t row = 0; row < OLED_NR_OF_PAGES; row++)
	{
		oled_goToRow(row);
		
		for(uint8_t col = 0; col < OLED_PIXEL_WIDTH; col++)
		{	
			sram_write(0x00, OLED_PIXEL_WIDTH * row + col);
		}
	}
	
}

/* val [0:255] */
void oled_setContrast(uint8_t contrastVal)
{
	volatile char *ext_ram = (char *) 0x0000;	
	
	ext_ram[OLED_CMD_ADDR] = (0x81);
	ext_ram[OLED_CMD_ADDR] = contrastVal;
}

void oled_drawPixel(uint8_t x, uint8_t y)
{
	uint8_t previousByte = sram_read(128 * (y / 8) + x);
	
	uint8_t updatedByte = ((1 << (y % 8)) | previousByte);
	
	sram_write(updatedByte, 128 * (y / 8) + x);
}

#define FONT_WIDTH 8
#define ASCHII_OFFSET -32
static void oled_putChar(char charr, uint8_t row, uint8_t col)
{
	for (int i = 0; i < FONT_WIDTH; i++)
	{		
		uint8_t previousByte = sram_read(OLED_PIXEL_WIDTH * row + col + i);
				
		uint8_t updatedByte = pgm_read_word(&font8[charr + ASCHII_OFFSET][i]) | previousByte;
				
		sram_write(updatedByte, OLED_PIXEL_WIDTH * row + col + i);
	}		
}

void oled_print(char* string, uint8_t row, uint8_t col)
{
	uint8_t index = 0;
	char currentChar = string[index];
	
	while(currentChar != '\0')
	{
		oled_putChar(currentChar, row, col + index * FONT_WIDTH);
			
		index++;
		
		currentChar = string[index];
	}
}




uint8_t loadingWheel[] =
{
	0x80,0xF0,0xB8,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x70,0x38,0x3C,0x04,0x07,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x20,0x00,0x08,0x00,0x04,0x07,0x07,0x07,0x02,0x07,0x07,0x06,0x00,0x00,0x00,
	0x00,0x40,0x00,0x00,0x02,0x00,0x00,0x01,0x00,0x02,0x07,0x07,0x06,0x38,0x38,0x78,
	0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x38,0xB8,0xF8,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x88,0xC0,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x40,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,

	0x01,0x0F,0x0D,0x1C,0x20,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,
	0x00,0x05,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x03,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x38,0x38,0x3F,0x03,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0xE0,0xE0,0xE0,0x38,0x38,0x3C,0x00,
	0x00,0x18,0x3C,0x38,0xE0,0xE0,0xE0,0x40,0xE0,0xE0,0xE0,0x20,0x00,0x08,0x00,0x00
};

void oled_displayLoading(uint8_t imgIndex, uint8_t x, uint8_t y)
{
	oled_print("Loading..", y / 8 + 6, x - 20);	
	for(uint8_t row = 0; row < 2; row++)
	{
		for (uint8_t col = /*(imgIndex) * 8*/0; col < 16/* * imgIndex*//*imgIndex * 8*//*128*/; col++)
		{
			sram_write(loadingWheel[128 * row + col + (imgIndex - 1) * 16], 128 * (row + y) + col + x /*+ imgIndex * 8*/);				
		}
		//oled_print("Loading...", y / 8 + 6, x - 20);
	}
	_delay_ms(80);
}








