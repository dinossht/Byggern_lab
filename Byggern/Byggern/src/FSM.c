/*
 * game.c
 *
 * Created: 11/15/2017 2:43:42 PM
 *  Author: dinos
 */ 

#include "FSM.h"
#include "drivers/CAN.h"


static FSM_stateMachine_t node1_stateMachine;



void FSM_setNode1State(FSM_states new_state){
	node1_stateMachine.FSM_current_state = new_state;
}

void FSM_setNode2State(FSM_states new_state){
	//can_message_send();
}


FSM_states FSM_getNode1State(){
	return node1_stateMachine.FSM_current_state;
}


void FSM_game_setGlobalState(FSM_states new_state){
	FSM_setNode1State(new_state);
	FSM_setNode2State(new_state);
}