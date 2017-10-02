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

static void joystick_test(void);
static void joystick_dirTest(void);
static void	slider_test(void);
static void button_test(void);

void ex03()
{
	joystick_calib();
	while(1)
	{
		//joystick_test();
		//joystick_dirTest();
		//slider_test();
		//button_test();	
	}	
}

static void joystick_test()
{	
	int16_t joystick_x = joystick_getPos(POS_X);
	printf("Joystick X value: %8d\n", joystick_x);
	
	int16_t joystick_y = joystick_getPos(POS_Y);
	printf("Joystick Y value: %8d\n", joystick_y);	
}

static void joystick_dirTest()
{
	int16_t joystick_dir = joystick_getDir();
	printf("Joystick direction: ");
	
	switch (joystick_dir)
	{
		case NEUTRAL:
			printf("NEUTRAL\n");
			break;
		case UP:
			printf("UP\n");
			break;
		case DOWN:
			printf("DOWN\n");
			break;
		case LEFT:
			printf("LEFT\n");
			break;
		case RIGHT:
			printf("RIGHT\n");
			break;
		default:
			printf("ERROR\n");
			break;	
	}
}

static void	slider_test()
{
	int16_t slider_r = slider_getPos(SLIDER_RIGHT);
	printf("Right slider value: %8d\n", slider_r );	
	
	int16_t slider_l = slider_getPos(SLIDER_LEFT);
	printf("Left slider value: %8d\n", slider_l );
}

static void button_test()
{
	if (button_getStat(BUTTON_LEFT) == PRESSED)
	{
		printf("Left button is pressed!\n");
	}
	
	if (button_getStat(BUTTON_RIGHT) == PRESSED)
	{
		printf("Right button is pressed!\n");
	}	
	
	if (button_getStat(BUTTON_JOYSTICK) == PRESSED)
	{
		printf("Joystick is pressed!\n");
	}
}