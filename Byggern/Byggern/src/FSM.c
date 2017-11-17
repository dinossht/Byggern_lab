/*
 * fsm.c
 *
 * Created: 11/17/2017 3:25:22 PM
 *  Author: dinos
 */ 

#include "drivers/CAN.h"
#include "CAN/CAN_messages.h"
#include "fsm.h"


static fsm_state_t currentState;

void fsm_init(void)
{
	currentState = IDLE;	
}

void fsm_setCurrentState(fsm_state_t state)
{
	currentState = state;
}

fsm_state_t fsm_getCurrentState(void)
{
	return currentState;
}









static FSM_stateMachine_t node1_stateMachine;


static void FSM_setNode1State(fsm_state_t new_state){
	node1_stateMachine.FSM_current_state = new_state;
	
}

// static void FSM_setNode2State(FSM_states new_state){
// 	
// //	FSM_setNode2State_message.data.u8[0] = new_state;
// //	can_message_send(&FSM_setNode2State_message);
// }


fsm_state_t FSM_getGlobalState(){
	return node1_stateMachine.FSM_current_state;
}


void FSM_setGlobalState(fsm_state_t new_state){
	FSM_setNode1State(new_state);
	// CAN_transmit(current_state_message);
}
