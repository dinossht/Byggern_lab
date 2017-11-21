/*
 * can_wrapper.c
 *
 * Created: 11/17/2017 6:36:37 PM
 *  Author: dinos
 */ 

#include "../multiboard_data.h"
#include "../ps3_data.h"
#include "../pong_data.h"
#include "../drivers/menu.h"
#include "../drivers/can.h"
#include "../game.h"
#include "can_definitions.h"
#include "CAN_messages.h"
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
			
			case CAN2_DATA_SENSOR_ID:
				pong_data.encoderPosition = message.data.i16[0];
				pong_data.irTriggered = message.data.u8[2];
			break;			
		}
	}
}

#define NUM_OF_CAN_MSGS 5
static uint8_t i = 0;
void can_wapper_sendMessages()
{
		
	i++;
	i = i % NUM_OF_CAN_MSGS;
	switch(i)
	{
		case 0:
			joystick_message.data.i8[0] = multiboard_data.joystickPositionX;
			joystick_message.data.i8[1] = multiboard_data.joystickPositionY;
			can_sendMessage(&joystick_message);
		break;
		
		case 1:
			slider_message.data.u8[0] = multiboard_data.sliderLeftPosition;
			slider_message.data.u8[1] = multiboard_data.sliderRightPosition;
			can_sendMessage(&slider_message);
		break;
		
		case 2:
			button_message.data.u8[0] = multiboard_data.buttonLeftPressed;
			button_message.data.u8[1] = multiboard_data.buttonRightPressed;
			button_message.data.u8[2] = multiboard_data.joystickPressed;
			can_sendMessage(&button_message);
		break;
		
		case 3:
			pid_message.data.u8[0] = tunePidM.entries[0].value;
			pid_message.data.u8[1] = tunePidM.entries[1].value;
			pid_message.data.u8[2] = tunePidM.entries[2].value;
			can_sendMessage(&pid_message);
		break;
		
		case 4:
			gamesData_message.data.u8[0] = game_state == GAMEPLAYING; // game state
			gamesData_message.data.u8[1] = gameM.entries[1].value; // input
			can_sendMessage(&gamesData_message);
		break;
	}
}
