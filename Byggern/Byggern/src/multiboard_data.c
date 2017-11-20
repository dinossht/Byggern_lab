/*
 * multiboard_data.c
 *
 * Created: 11/17/2017 8:30:11 PM
 *  Author: dinos
 */ 

#include "multiboard/joystick.h"
#include "multiboard/slider.h"
#include "multiboard/button.h"
#include "multiboard_data.h"


static void mutliboard_data_updateJoystickDirection(void);

void multiboard_data_init()
{
	joystick_calib();

	multiboard_data.joystickDirection = JOY_NEUTRAL;
	multiboard_data.joystickPositionX = 0;
	multiboard_data.joystickPositionY = 0;
	multiboard_data.joystickPressed = 0;
	multiboard_data.sliderLeftPosition = 0;
	multiboard_data.sliderRightPosition = 0;
	multiboard_data.buttonLeftPressed = 0;
	multiboard_data.buttonRightPressed = 0;
}

static joystick_dir_t previousDirection;
static void mutliboard_data_updateJoystickDirection()
{
	if(previousDirection != JOY_NEUTRAL && joystick_getDir() == JOY_NEUTRAL)
		multiboard_data.joystickDirection = previousDirection;
	else
		multiboard_data.joystickDirection = JOY_NEUTRAL;
	
	previousDirection = joystick_getDir();	
}

void multiboard_data_updateInputs()
{
	
	mutliboard_data_updateJoystickDirection();
	multiboard_data.joystickPositionX = joystick_getPos(POS_X);
	multiboard_data.joystickPositionY = joystick_getPos(POS_Y);
	multiboard_data.buttonLeftPressed = button_getStat(BUTTON_LEFT);
	multiboard_data.buttonRightPressed = button_getStat(BUTTON_RIGHT);
	multiboard_data.joystickPressed = button_getStat(BUTTON_JOYSTICK);
	multiboard_data.sliderLeftPosition = slider_getPos(SLIDER_LEFT);
	multiboard_data.sliderRightPosition = slider_getPos(SLIDER_RIGHT);
}
