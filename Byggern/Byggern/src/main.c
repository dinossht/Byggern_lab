#include "settings.h"

#include <asf.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "hardware_init.h"
#include "FSM.h"
#include "CAN/CAN_messages.h"

#include "drivers/mcp2515.h"
#include "drivers/spi.h"
#include "drivers/CAN.h"

#include "multiboard/oled.h"
#include "multiboard/joystick.h"
#include "multiboard/slider.h"
#include "multiboard/button.h"

#include "CAN/CAN_wrapper.h"


int main (void)
{
	hardware_init();
	can_init();
	joystick_calib();
	
	while(1)
	{
		CAN_wrapper_updateStates();
		switch(FSM_getGlobalState())
		{
			case PLAYING:
				joystick_message.data.i8[0] = joystick_getPos(POS_X);
				joystick_message.data.i8[1] = joystick_getPos(POS_Y); 
				joystick_message.data.u8[2] = button_getStat(BUTTON_JOYSTICK);
				can_message_send(&joystick_message);
				
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
			break;
			
			case(GAMEOVER):
			#warning Automagically restarts game if you lose, shold be fixed
				FSM_setGlobalState(PLAYING);
			break;
			
			case(LOGGING):
				
			break;
			
			case (TUNING):
				
			break;
		}
		
	}	
	return 0;
}
