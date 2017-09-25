/*
 * button.c
 *
 * Created: 25.09.2017 10:25:50
 *  Author: dinossht
 */ 

#include <../drivers/pio.h>
#include "button.h"

btn_stat_t button_getStat(button_t btn)
{
	switch(btn)
	{
		case BUTTON_LEFT:
			return pio_read(&PIND, PIND3) ? PRESSED : RELEASED;
			
		case BUTTON_RIGHT:
			return pio_read(&PIND, PIND2) ? PRESSED : RELEASED;
			
		default:
			return UNDEFINED;	
	}
}
