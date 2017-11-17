/*
 * CAN_messages.h
 *
 * Created: 11/15/2017 5:02:11 PM
 *  Author: dinos
 */ 


#ifndef CAN_MESSAGES_H_
#define CAN_MESSAGES_H_

#include "../drivers/can.h"


struct can_message_t joystick_message;
struct can_message_t slider_message;
struct can_message_t button_message;
struct can_message_t gamesData_message;
struct can_message_t pid_message;

#endif /* CAN_MESSAGES_H_ */