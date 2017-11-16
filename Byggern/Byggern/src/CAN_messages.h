/*
 * CAN_messages.h
 *
 * Created: 11/15/2017 5:02:11 PM
 *  Author: dinos
 */ 


#ifndef CAN_MESSAGES_H_
#define CAN_MESSAGES_H_

#include "CAN_definitions.h"
#include "drivers/CAN.h"


//Multiboard
struct can_message joystick_message;
struct can_message slider_message;
struct can_message button_message;

//States
struct can_message FSM_setNode2State_message;


#endif /* CAN_MESSAGES_H_ */