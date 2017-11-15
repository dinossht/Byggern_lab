/*
 * ex07.c
 *
 * Created: 23.10.2017 16:19:31
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
#include "../drivers/timer.h"

#include "../multiboard/oled.h"
#include "../multiboard/joystick.h"
#include "../multiboard/slider.h"
#include "../multiboard/button.h"
#include "../CAN/CAN_messages.h"


#include <avr/interrupt.h>
#include "ex07.h"



void ex07()
{
	can_init();
	joystick_calib();
	oled_init();
	menu_init();
	timer_init();
	
	sei();
	
	while(1)
	{	
		oled_clearScreen();

		while(1)
		{
			static int i = 0;
				
			if(timer_isAFlagSet(EIGHT_KHZ_TIMER))
			{	
				if(i > 100)
				{
					oled_print("ks", 0, i / 100);
				}

				i++;
				oled_updateScreen();
				timer_reset(EIGHT_KHZ_TIMER);
			}	
		}

	
		
		
		
		oled_clearScreen();
		joyPos = joystick_getPos(POS_X);
		
		joystick_dir_t direction = joystick_getDir();
		button_t button = button_getStat(BUTTON_JOYSTICK);
		shoot = button_getStat(BUTTON_RIGHT);	
		if(button == 1)
		{
			menu_selectCurrentEntry();
		}	
		
		switch(direction)
		{
			case UP:
				menu_scrollEntry(SCROLL_UP);
				menu_incrementEntryValue(1);
			break;
			
			case DOWN:
				menu_scrollEntry(SCROLL_DOWN);
				menu_incrementEntryValue(0);
			break;
			
			case RIGHT:
				menu_navigateToCurrentEntry();
			break;
			
			case LEFT:
				menu_navigateToPreviusMenu();
			break;
		}		

		menu_draw();
		
		oled_updateScreen();
		_delay_ms(100);
	}	
}
