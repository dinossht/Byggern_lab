/*
 * can_wrapper.c
 *
 * Created: 11/17/2017 6:36:37 PM
 *  Author: dinos
 */ 

#include "../multiboard.h"
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
				//multiboardInputs.				
			break;
			
			case CAN3_PS3_BUTTONS_ID:
			
			break;
			
			case CAN3_PS3_DPAD_ID:
			
			break;
			
			case CAN2_DATA_ENCODER_ID:
				
			break;
			
		}
	}
}

void can_wapper_sendMessages()
{
	
}
