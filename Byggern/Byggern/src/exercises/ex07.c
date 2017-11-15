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
#include "../drivers/menu.h"
#include "../multiboard/oled.h"
#include "../multiboard/joystick.h"
#include "../multiboard/slider.h"
#include "../multiboard/button.h"


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
	.data.u8[0] = 1
};




void ex07()
{
	can_init();
	joystick_calib();
	oled_init();
	menu_init();
	//menu_initEntries(%gameM, gameEntries);
	while(1)
	{	
		oled_clearScreen();
		joystick_dir_t direction = joystick_getDir();
		
		
		
		switch(direction)
		{
			case UP:
				menu_scrollEntry(SCROLL_UP);
			break;
			
			case DOWN:
				menu_scrollEntry(SCROLL_DOWN);
			break;
			
			case RIGHT:
				menu_navigateToCurrentEntry();
			break;
			
			case LEFT:
				menu_navigateToPreviusMenu();
			break;
		}
		
		
		//oled_print("Hei", x / 12, 0);
		//menu_draw(&mainM);
		//mainM.currentEntryIndex = x;
		
		//menu_navigateToPreviusMenu(&tunePidM);
		
		menu_draw();
		
		oled_updateScreen();
		_delay_ms(100);
		//while(1);
	}	
}
