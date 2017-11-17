#include "settings.h"
#include <util/delay.h>
#include <asf.h>

#include "drivers/timer.h"
#include "drivers/uart.h"
#include "drivers/latch.h"
#include "drivers/menu.h"
#include "drivers/can.h"

#include "multiboard/oled.h"
#include "multiboard/joystick.h"
#include "multiboard/slider.h"
#include "multiboard/button.h"

#include "../can/can_wrapper.h"

#include "multiboard_data.h"
#include "ps3_data.h"
#include "pong_data.h"
#include "fsm.h"
#include "game.h"


static void navigateMenu(joystick_dir_t joystickDirection);

int main (void)
{
	/* hardware init */
	MCUCR |= (1 << SRE); /* external memory init */
	uart_init();
	latch_init();
	can_init();
	timer_init();
	oled_init();
	/*****************/
	
	ps3_data_init();
	multiboard_data_init();
	pong_data_init();
	fsm_init();
	menu_init();

	while(1)
	{
		if(timer_isAFlagSet(SIXTY_HZ_TIMER) == 1)
		{
			oled_clearScreen();
			menu_draw();
			oled_updateScreen();
			
			timer_reset(SIXTY_HZ_TIMER);
		}
		
		if(timer_isAFlagSet(SIXTEEN_KHZ_TIMER) == 1)
		{
			can_wrapper_recieveMessages();
			//send message
			timer_reset(SIXTEEN_KHZ_TIMER);
		}
		
		multiboard_data_updateInputs();
		
		fsm_state_t fsmState = fsm_getCurrentState();
		switch(fsmState)
		{
			case IDLE:
				navigateMenu(multiboard_data.joystickDirection);
			break;
			
			case GAME_PLAY:
				//playGame();
			break;
			
			case DATA_LOGGING:
				//logData();
			break;
			
			case DATA_PLAYBACK:
				//playBack();
			break;
			
			case TUNING:
				//tunePID();
			break;
		}
	}
}

static void navigateMenu(joystick_dir_t joystickDirection)
{
	switch(joystickDirection)
	{
		case JOY_UP:
			menu_scrollEntry(SCROLL_UP);
			menu_incrementEntryValue(1);
		break;
		
		case JOY_DOWN:
			menu_scrollEntry(SCROLL_DOWN);
			menu_incrementEntryValue(0);
		break;
		
		case JOY_RIGHT:
			menu_navigateToCurrentEntry();
		break;
		
		case JOY_LEFT:
			menu_navigateToPreviusMenu();
		break;
		
		case JOY_NEUTRAL:
		break;
	}
}
