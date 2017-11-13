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

#include "../drivers/mcp2515.h"
#include "../drivers/spi.h"
#include "../drivers/CAN.h"
#include "../multiboard/joystick.h"
#include "../multiboard/slider.h"
#include "../multiboard/button.h"


#include <avr/interrupt.h>
#include "ex07.h"


struct can_message joystick_message =
{
	.id = 0x10,
	.length = 3,
};

struct can_message slider_message =
{
	.id = 0x11,
	.length = 2
};

struct can_message button_message =
{
	.id = 0x12,
	.length = 2
};



void ex07()
{
	can_init();
	joystick_calib();
	
	while(1)
	{
		joystick_message.data.i8[0] = joystick_getPos(POS_X);
		joystick_message.data.i8[1] = joystick_getPos(POS_Y); 
		joystick_message.data.u8[2] = button_getStat(BUTTON_JOYSTICK);
		can_message_send(&joystick_message);
		//printf("%d\n", joystick_message.data.i8[0]);
		
		_delay_ms(10);
		
		slider_message.data.u8[0] = slider_getPos(SLIDER_LEFT);
		slider_message.data.u8[1] = slider_getPos(SLIDER_RIGHT);
		can_message_send(&slider_message);
		printf("%d\n", slider_message.data.u8[1]);	
		
		_delay_ms(10);
		
		button_message.data.u8[0] = button_getStat(BUTTON_LEFT);
		button_message.data.u8[1] = button_getStat(BUTTON_RIGHT);
		can_message_send(&button_message);
//		printf("%d\n", button_message.data.u8[0]);
		
		_delay_ms(10);
	}	
}
