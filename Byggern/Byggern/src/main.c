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

#include "multiboard.h"
#include "ps3.h"
#include "fsm.h"
#include "game.h"


static void navigateMenu(joystick_dir_t joystickDirection);
static void updateMultiboard(void);

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
	
	ps3_init();
	//multiboard_init();
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
			//can_message_send();
		}
		
		updateMultiboard();
		
		fsm_state_t fsmState = fsm_getCurrentState();
		switch(fsmState)
		{
			case IDLE:
				navigateMenu(multiboardInputs.joystickDirection);
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
	}
}

static void updateMultiboard()
{
	multiboardInputs.joystickDirection = joystick_getDir();
	multiboardInputs.joystickPositionX = joystick_getPos(POS_X);
	multiboardInputs.joystickPositionY = joystick_getPos(POS_Y);
	multiboardInputs.buttonLeftPressed = button_getStat(BUTTON_LEFT);
	multiboardInputs.buttonRightPressed = button_getStat(BUTTON_RIGHT);
	multiboardInputs.joystickPressed = button_getStat(BUTTON_JOYSTICK);
	multiboardInputs.sliderLeftPosition = slider_getPos(SLIDER_LEFT);
	multiboardInputs.sliderRightPosition = slider_getPos(SLIDER_RIGHT);
}