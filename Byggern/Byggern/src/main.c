#include "settings.h"

#include <asf.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "hardware_init.h"
#include "FSM.h"
#include "game.h"

#include "drivers/mcp2515.h"
#include "drivers/spi.h"
#include "drivers/CAN.h"

#include "multiboard/oled.h"
#include "multiboard/joystick.h"
#include "multiboard/slider.h"
#include "multiboard/button.h"

#include "CAN/CAN_wrapper.h"
#include "CAN/CAN_messages.h"


int main (void)
{
	hardware_init();
	can_init();
	joystick_calib();
	
	while(1)
	{
		//Should create a function that does everything tied to updating states, both reading CAN and reading multiboard
		CAN_wrapper_updateStates();
		switch(FSM_getGlobalState())
		{
			case MENU:
				// Draw current menu
				// Read menu choices
				// if (choice == play){ FSM_setGlobalState(PLAYING) }
				// else if (choice == logging){ FSM_setGlobalState(PLAYING) }
				// else if (choice == tuning){ FSM_setGlobalState(TUNING) }
			break;

			case PLAYING:
			while (lives!=0){
				game_transmitControllerInput();
				
			}
 		
			// Retrieve score
			// Draw game over screen
			// Save username and score to SRAM
 			// FSM_setGlobalState(MENU);

			break;
						
			case LOGGING:
				// Read CAN to recieve logged data
				// Play logged data
				// FSM_setGlobalState(TUNING);
			break;
			
			case TUNING:
				// Draw tuning-menu
				// Transmit new tuning parameters to node2
				// FSM_setGlobalState(MENU);
			break;
		}
		
		_delay_ms(10);
		
		slider_message.data.u8[0] = slider_getPos(SLIDER_LEFT);
		slider_message.data.u8[1] = slider_getPos(SLIDER_RIGHT);
		can_message_send(&slider_message);
		printf("%d\n", slider_message.data.u8[1]);	
		
		_delay_ms(10);
		
		button_message.data.u8[0] = button_getStat(BUTTON_LEFT);
		button_message.data.u8[1] = button_getStat(BUTTON_RIGHT);
		can_message_send(&button_message);
		
		_delay_ms(10);
	}	
	return 0;
}
