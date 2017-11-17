/*
 * can_wrapper.c
 *
 * Created: 11/17/2017 6:36:37 PM
 *  Author: dinos
 */ 


#include "../drivers/can.h"
#include "can_definitions.h"
#include "can_wrapper.h"


void can_wrapper_recieveMessages()
{
	struct can_message_t message;
	
	if(/*can_recieveMessage() == 1*/1)
	{
		switch(message.id)
		{
			case CAN3_PS3_JOYSTICK_ID:
					
			break;
			
			case CAN3_PS3_BUTTONS_ID:
			
			break;
			
			case CAN3_PS3_DPAD_ID:
			
			break;
			
		}
	}
}

void can_wapper_sendMessages()
{
	
}
