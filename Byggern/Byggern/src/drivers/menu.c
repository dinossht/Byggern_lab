/*
 * menu.c
 *
 * Created: 15.11.2017 14.21.37
 *  Author: Admin
 */ 

#include "sram.h"
#include "../multiboard/oled.h"
#include "menu.h"


#define MENU_WIDTH 128
#define MENU_HEIGHT 8

// 		for(uint8_t row = 0; row < 8; row++)
// 		{
// 			for(uint8_t col = 0; col < 128; col++)
// 			{
// 				sram_write(col, 128 * row + col);
// 			}
// 		}
// 		
// 
// 
// 		for(uint8_t row = 0; row < 8; row++)
// 		{
// 			for(uint8_t col = 0; col < 128; col++)
// 			{
// 				oled_putPixelColumn(sram_read(128 * row + col), row, col);
// 			}
// 		}

	
void menu_updateScreen()
{
	for(uint8_t row = 0; row < MENU_HEIGHT; row++)
	{
		for(uint8_t col = 0; col < MENU_WIDTH; col++)
		{
			uint8_t pixelColumn = sram_read(MENU_WIDTH * row + col);
			
			oled_putPixelColumn(pixelColumn, row, col);
		} 
	}
		
}

void menu_clearScreen()
{
	for(uint8_t row = 0; row < MENU_HEIGHT; row++)
	{
		for(uint8_t col = 0; col < MENU_WIDTH; col++)
		{
			sram_write(0x00, MENU_WIDTH * row + col);
		}
	}		
}


void menu_placePixel(uint8_t x, uint8_t y)
{
	uint8_t prevPixel = sram_read(128 * (y / 8) + x);
					
	uint8_t newPixel = ((1 << (y % 8)) | prevPixel);
					
	sram_write(newPixel, 128 * (y / 8) + x);
}



void menu_putPixel(uint8_t x, uint8_t y)
{
	uint8_t row = y / 8;
	uint8_t col = x;
	
	uint8_t pixelColumn = sram_read(MENU_WIDTH * row + col);
	
//	sram_write((1 << (y % 8)) | pixelColumn , MENU_WIDTH * y + x);
	
	sram_write((1 << (row % 8)) | pixelColumn, MENU_WIDTH * row + col);
	
	
}


