/*
 * CAN_messages.c
 *
 * Created: 11/15/2017 5:17:22 PM
 *  Author: dinos
*/ 
#include "CAN_messages.h"


//Multiboard
struct can_message joystick_message =
{
	 .id = CAN_MULTIBOARD_JOYSTICK_ID,
	 .length = 3,
};

struct can_message slider_message =
{
	 .id = CAN_MULTIBOARD_SLIDER_ID,
	 .length = 2,
};

struct can_message button_message =
{
	 .id = CAN_MULTIBOARD_BUTTON_ID,
	 .length = 2,
};

//States
struct can_message FSM_setNode2State_message =
{
	 .id = CAN_STATE_FROMNODE1_ID,
	 .length = 1,
};

//Data
struct can_message game_parameterTuning =
{
	 .id = CAN_PID_TUNING_ID,
	 .length = 3,
};
