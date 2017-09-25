/*
 * ex03.c
 *
 * Created: 20.09.2017 10:59:43
 *  Author: hermansu
 */ 

#include <stdio.h>
#include "../multiboard/joystick.h"
#include "../multiboard/slider.h"
#include "../multiboard/button.h"
#include "ex03.h"

#define POS
//#define DIR
//#define BTN
//#define SLIDER


void ex03()
{
	//joystick_calib();
	while(1)
	{	
		#ifdef POS
		int16_t joystick_x = joystick_getPos(POS_X);
		int16_t joystick_y = joystick_getPos(POS_Y);
		printf("Joystick X value: %8d\n", joystick_x );
		printf("Joystick Y value: %8d\n", joystick_y );
		#endif //POS
		
		
		#ifdef DIR
		int16_t joystick_dir = joystick_getDir();
//		printf("Joystick direction: %8d\n",joystick_dir);
		switch (joystick_dir)
		{
			case NEUTRAL:
				printf("Joystick direction: NEUTRAL\n");
				break;
			case UP:
				printf("Joystick direction: UP\n");
				break;
			case DOWN:
				printf("Joystick direction: DOWN\n");
				break;
			case LEFT:
				printf("Joystick direction: LEFT\n");
				break;
			case RIGHT:
				printf("Joystick direction: RIGHT\n");
				break;
			default:
				printf("Joystick direction: ERROR\n");
				break;
			
		}
		
		#endif //DIR
		
		
		#ifdef BTN
		if (button_getStat(BUTTON_LEFT) == PRESSED)
		{
			printf("Left button is pressed!\n");
		}
		if (button_getStat(BUTTON_RIGHT) == PRESSED)
		{
			printf("Right button is pressed!\n");
		}
		#endif //BTN
		
		
		#ifdef SLIDER
		int16_t slider_r = slider_getPos(SLIDER_RIGHT);
		int16_t slider_l = slider_getPos(SLIDER_LEFT);
		printf("Left slider value: %8d\n", slider_l );
		printf("Right slider value: %8d\n", slider_r );
		#endif //SLIDER
	}
}