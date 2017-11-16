/*
 * CAN_messages.h
 *
 * Created: 11/15/2017 5:02:11 PM
 *  Author: dinos
 */ 


#ifndef CAN_MESSAGES_H_
#define CAN_MESSAGES_H_

#include "CAN_definitions.h"
#include "../drivers/CAN.h"


//Multiboard
struct can_message multiboard_joystick_message;
struct can_message multiboard_slider_message;
struct can_message multiboard_button_message;

//States
struct can_message FSM_setNode2State_message;

//Data
struct can_message game_parameterTuning_message;

struct can_message game_setLives_message;

struct can_message game_setController_message;


#endif /* CAN_MESSAGES_H_ */