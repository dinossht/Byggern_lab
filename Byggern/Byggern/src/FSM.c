/*
 * game.c
 *
 * Created: 11/15/2017 2:43:42 PM
 *  Author: dinos
 */ 

#ifndef FSM_H_
#define FSM_H_

#include "FSM.h"
#include "drivers/CAN.h"
#include "CAN/CAN_messages.h"



static FSM_stateMachine_t node1_stateMachine;


static void FSM_setNode1State(FSM_states new_state){
	node1_stateMachine.FSM_current_state = new_state;
}

static void FSM_setNode2State(FSM_states new_state){
	FSM_setNode2State_message.data.u8[0] = new_state;
	can_message_send(&FSM_setNode2State_message);
}


FSM_states FSM_getGlobalState(){
	return node1_stateMachine.FSM_current_state;
}


void FSM_setGlobalState(FSM_states new_state){
	FSM_setNode1State(new_state);
	FSM_setNode2State(new_state);
}

#endif /* FSM_H_ */