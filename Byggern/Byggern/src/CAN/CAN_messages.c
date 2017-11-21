/*
 * can_messages.c
 *
 * Created: 11/17/2017 6:23:01 PM
 *  Author: dinos
 */ 

#include "can_definitions.h"
#include "can_messages.h"
#include "multiboard_data.h"

struct can_message_t joystick_message =
{
	.id = CAN1_MULTIBOARD_JOYSTICK_ID,
	.length = 2, 
};

struct can_message_t slider_message =
{
	.id = CAN1_MULTIBOARD_SLIDER_ID,
	.length = 2,
};

struct can_message_t button_message =
{
	.id = CAN1_MULTIBOARD_BUTTON_ID,
	.length = 3,
};

struct can_message_t pid_message =
{
	.id = CAN1_DATA_PID_PARAM_ID,
	.length = 3,
};

struct can_message_t gamesData_message =
{
	.id = CAN1_DATA_GAME_ID,
	.length = 2,
};
