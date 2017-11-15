/*
 * ex07.c
 *
 * Created: 23.10.2017 16:19:31
 *  Author: hermansu
 */ 

/*
 * ex05.c
 *
 * Created: 02.10.2017 11:55:04
 *  Author: hermansu
 */ 

#include <stdio.h>
#include "settings.h"
#include <util/delay.h>
#include <math.h>

#include "../drivers/mcp2515.h"
#include "../drivers/spi.h"
#include "../drivers/CAN.h"
#include "../drivers/sram.h"
#include "../multiboard/oled.h"
#include "../multiboard/joystick.h"
#include "../multiboard/slider.h"
#include "../multiboard/button.h"
#include "../drivers/menu.h"


#include <avr/interrupt.h>
#include "ex07.h"


struct can_message joystick_message =
{
	.id = 0x10,
	.length = 2,
};

struct can_message slider_message =
{
	.id = 0x11,
	.length = 2
};

struct can_message button_message =
{
	.id = 0x12,
	.length = 4,
	.data.u32[0] = 0
};


void circle(int x,int y,int radius) {
    int i = 0, j = radius ;
	menu_clearScreen();
    while (i<=j) {
        menu_placePixel(x+i,y-j) ;
        menu_placePixel(x+j,y-i) ;
        menu_placePixel(x+i,y+j) ;
        menu_placePixel(x+j,y+i) ;
        menu_placePixel(x-i,y-j) ;
        menu_placePixel(x-j,y-i) ;
        menu_placePixel(x-i,y+j) ;
        menu_placePixel(x-j,y+i) ;
        i++ ;
        j = (int)(sqrt(radius*radius - i*i) + 0.5) ;
		
    }
}



void ex07()
{
	can_init();
	joystick_calib();
	oled_init();
	oled_clear();	
//	oled_print("Hallo", 8, 0);		
	//oled_setContrast(255);
	menu_clearScreen();
	int r = 30; // radius
	int ox = 64, oy = 32; // origin

	while(1)
	{		
		_delay_ms(500);
		
		can_message_send(&button_message);
	//	button_message.data.u32[0] = 0;
		
	//	can_message_send(&button_message);
		button_message.data.u32[0] = 0xFFFF;
		
		//button_message.data.u32[0];
		
// 		for(uint8_t i = 0; i < 64; i++)
// 		{
// 			for(uint8_t j = 0; j < 128; j++)
// 			{
// 				menu_placePixel(j, i);
// 			}
// 		}
		circle(64, 32, (r++ % 30));
// 		for (int x = -r; x < r ; x++)
// 		{
// 			int height = (int)sqrt(r * r - x * x);
// 
// 			for (int y = -height; y < height; y++)
// 			{
// 				menu_placePixel(x + ox, y + oy);
// 				menu_updateScreen();
// 			}
// 		}
		
		

		

//		menu_placePixel(1, 1);
//		menu_putPixel(x, y);
		menu_updateScreen();
// 		if(col < 128)
// 			row++;
// 		oled_putPixelColumn(/*sram_read(128 * i + j)*/0xFF, 0, row);
// 		_delay_ms(100);
		
		
		
		
		
		//oled_pixel(x, y);
		//menu_putPixel(x, y);
		//menu_updateScreen();
		
		
		//_delay_ms(500);
	}	
}
