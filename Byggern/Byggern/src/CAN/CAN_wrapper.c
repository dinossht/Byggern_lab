/*
 * can_wrapper.c
 *
 * Created: 11/17/2017 6:36:37 PM
 *  Author: dinos
 */ 

#include "../multiboard_data.h"
#include "../ps3_data.h"
#include "../pong_data.h"
#include "../drivers/can.h"
#include "can_definitions.h"
#include "can_wrapper.h"


void can_wrapper_recieveMessages()
{
	struct can_message_t message;
	message.id = 0x0;

	if(can_recieveMessage(&message) == 1)
	{
		switch(message.id)
		{
			case CAN3_PS3_JOYSTICK_ID:
				ps3_data.joystickLeftPositionX = message.data.i8[0];	
				ps3_data.joystickLeftPositionY = message.data.i8[1];	
				ps3_data.joystickRightPositionX = message.data.i8[2];	
				ps3_data.joystickRightPositionY = message.data.i8[3];				
			break;
			
			case CAN2_DATA_PONG_DATA_ID:
				pong_data.irTriggered = message.data.u8[0];			
			break;
			
			case CAN2_DATA_ENCODER_ID:
				pong_data.encoderPosition = message.data.i16[0];			
			break;
			
		}
	}
}

void can_wapper_sendMessages()
{
	
}
