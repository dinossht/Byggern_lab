/*
 * CAN_wrapper.c
 *
 * Created: 11/15/2017 6:51:15 PM
 *  Author: dinos
 */ 

#include <stdint.h>
#include <asf.h>
#include <stdio.h>
#include "../drivers/CAN.h"
#include "CAN_wrapper.h"
#include "can_definitions.h"
#include "../FSM.h"
#include "../game.h"



void CAN_wrapper_updateStates()
{
	struct can_message recieveMessage;

	
	recieveMessage = can_message_recieve();
	switch(recieveMessage.id)
	{
// 	case CAN_STATE_FROMNODE2_ID:
// 		FSM_setGlobalState(recieveMessage.data.u8[0]);
// 	break;
// 	case CAN_REMAINING_LIVES_ID:
// 		game_setLives(recieveMessage.data.u8[0]);
	}
	
}