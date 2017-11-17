/*
 * can_wrapper.c
 *
 * Created: 11/17/2017 6:36:37 PM
 *  Author: dinos
 */ 

#include "../game.h"
#include "../multiboard_data.h"
#include "../ps3_data.h"
#include "../drivers/can.h"
#include "can_definitions.h"
#include "can_wrapper.h"


void can_wrapper_recieveMessages()
{
	struct can_message_t message;
	message.id = 0x0;
	#pragma message("fix so can_recieve returns boolean as in node 1")
	if(/*can_recieveMessage() == 1*/1)
	{
		switch(message.id)
		{
		#pragma message("Implement code here")
			case CAN3_PS3_JOYSTICK_ID:
				ps3_data.joystickLeftPositionX = message.data.i8[0];	
				ps3_data.joystickLeftPositionY = message.data.i8[1];	
				ps3_data.joystickRightPositionX = message.data.i8[2];	
				ps3_data.joystickRightPositionY = message.data.i8[3];				
			break;
			
			case CAN2_DATA_PONG_DATA_ID:
				
			break;
			
			case CAN2_DATA_ENCODER_ID:
							
			break;
			
		}
	}
}

void can_wapper_sendMessages()
{
	
}
