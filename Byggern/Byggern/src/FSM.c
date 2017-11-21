/*
 * fsm.c
 *
 * Created: 11/17/2017 3:25:22 PM
 *  Author: dinos
 */ 

#include "drivers/menu.h"
#include "drivers/CAN.h"
#include "CAN/CAN_messages.h"
#include "multiboard/oled.h"
#include "drivers/sram.h"
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

fsm_state_t fsm_getCurrentState()
{
	return currentState;
}

void fsm_updateStates()
{
	menu_t currentMenu = menu_returnCurrentMenu();
	
	if(gameScreenM.id == currentMenu.id)
		fsm_setCurrentState(GAME_PLAY);
		
	//else if(currentMenu)
	else
		fsm_setCurrentState(IDLE);
}




