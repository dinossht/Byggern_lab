/*
 * ex07.c
 *
 * Created: 23.10.2017 16:19:31
 *  Author: hermansu
 */ 



#include <stdio.h>
#include "settings.h"
#include <util/delay.h>

#include "../drivers/mcp2515.h"
#include "../drivers/spi.h"
#include "../drivers/CAN.h"
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
	oled_clear();
	
	int x = 0;
	int y = 0;
	while(1)
	{
		multiboard_joystick_message.data.i8[0] = joystick_getPos(POS_X);
		multiboard_joystick_message.data.i8[1] = joystick_getPos(POS_Y); 
		multiboard_joystick_message.data.u8[2] = button_getStat(BUTTON_JOYSTICK);
		can_message_send(&multiboard_joystick_message);
		//printf("%d\n", joystick_message.data.i8[0]);
		
		_delay_ms(10);
		
		multiboard_slider_message.data.u8[0] = slider_getPos(SLIDER_LEFT);
		multiboard_slider_message.data.u8[1] = slider_getPos(SLIDER_RIGHT);
		can_message_send(&multiboard_slider_message);
		printf("%d\n", multiboard_slider_message.data.u8[1]);	
		
		_delay_ms(10);
		
		multiboard_button_message.data.u8[0] = button_getStat(BUTTON_LEFT);
		multiboard_button_message.data.u8[1] = button_getStat(BUTTON_RIGHT);
		can_message_send(&multiboard_button_message);
//		printf("%d\n", button_message.data.u8[0]);
		
		oled_print("Hei", 0, 0);
		oled_setContrast(255);
		
		
		
// 		x++;
// 
// 		if(x == 127)
// 		{
// 			x = 0;
// 			y++;
// 		}
// 		
// 		
// 		
// 		oled_pixel(x, y);
		
		
		_delay_ms(10);
	}	
}
