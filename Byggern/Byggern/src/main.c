#include "settings.h"
#include <asf.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "hardware_init.h"
#include "FSM.h"
#include "game.h"

#include "drivers/mcp2515.h"
#include "drivers/spi.h"
#include "drivers/CAN.h"
#include "drivers/menu.h"

#include "multiboard/oled.h"
#include "multiboard/joystick.h"
#include "multiboard/slider.h"
#include "multiboard/button.h"

#include "CAN/CAN_wrapper.h"

#include "exercises/ex07.h"


int main (void)
{
	hardware_init();
	can_init();
	joystick_calib();
	oled_init();
	menu_init();
	
	FSM_setGlobalState(MENU); 
	#warning Only for debugging purposes

	
	while(1)
	{
		oled_clearScreen();
		CAN_wrapper_updateStates();
		game_updateControllerInput();
		
		switch(FSM_getGlobalState())
		{
			case MENU:
				oled_clearScreen();
				
				joyPos = multiboardStates.joystickPositionX;
				shoot = multiboardStates.rightButtonPressed;
				
				if(multiboardStates.joystickPressed == 1)
				{
					menu_selectCurrentEntry();
				}
				
				switch(multiboardStates.joystickDirection)
				{
					case UP:
					menu_scrollEntry(SCROLL_UP);
					menu_incrementEntryValue(1);
					break;
					
					case DOWN:
					menu_scrollEntry(SCROLL_DOWN);
					menu_incrementEntryValue(0);
					break;
					
					case RIGHT:
					menu_navigateToCurrentEntry();
					break;
					
					case LEFT:
					menu_navigateToPreviusMenu();
					break;
				}

				menu_draw();
				
				oled_updateScreen();
				_delay_ms(100);
			break;

			case PLAYING:
			#warning There is something wrong here! Screen doesnt work when something in here is not uncommented
//				game_init(); //Transmits game data to Node2
				while (game_getLives() > 0) {
					game_transmitControllerInput();	
				}
// 		
//				// Retrieve score
//				// Draw game over screen
//				if (game_insertHighscore()){
//					//Save username and score to SRAM
//				}
 				//FSM_setGlobalState(MENU);
			break;
						
			case LOGGING:
				// Transmit data for start logging
				// Wait for the right amount of CAN messages with logging id
				//Save theese to buffer or SRAM or something
				
 				FSM_setGlobalState(MENU);
			break;
//			
			case TUNING:
				game_transmitParameters();
				FSM_setGlobalState(MENU);
			break;
		}
	}	
	return 0;
}
