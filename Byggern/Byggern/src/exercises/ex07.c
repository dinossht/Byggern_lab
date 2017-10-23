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


#include <avr/interrupt.h>
#include "ex07.h"





void ex07()
{
	can_init();
	joystick_calib();
	struct can_message joystick_message = 
	{
		.id = 42,
		.length = 1,
		.data.i8[0] = 0,
	};
	
	while(1)
	{
		joystick_message.data.i8[0] = joystick_getPos(POS_X)/* * 0.05 + joystick_message.data.i8[0] * 0.95*/;
		can_message_send(&joystick_message);
	}	
}
