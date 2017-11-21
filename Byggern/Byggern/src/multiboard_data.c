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


static void multiboard_data_updateJoystickDirection(void);

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
static void multiboard_data_updateJoystickDirection()
{
	if(previousDirection != JOY_NEUTRAL && joystick_getDir() == JOY_NEUTRAL)
		multiboard_data.joystickDirection = previousDirection;
	else
		multiboard_data.joystickDirection = JOY_NEUTRAL;
	
	previousDirection = joystick_getDir();	
}

static uint8_t prevButtons[3] = {};
static void multiboard_data_updateButtons()
{
	if(prevButtons[0] == 1 &&  button_getStat(BUTTON_LEFT) == 0)
		multiboard_data.buttonLeftPressed = prevButtons[0];
	else
		multiboard_data.buttonLeftPressed = 0;
	if(prevButtons[1] == 1 &&  button_getStat(BUTTON_RIGHT) == 0)
		multiboard_data.buttonRightPressed = prevButtons[1];
	else
		multiboard_data.buttonRightPressed = 0;	
	if(prevButtons[2] == 1 &&  button_getStat(BUTTON_JOYSTICK) == 0)
		multiboard_data.joystickPressed = prevButtons[2];
	else
		multiboard_data.joystickPressed = 0;
		
	prevButtons[0] = button_getStat(BUTTON_LEFT);
	prevButtons[1] = button_getStat(BUTTON_RIGHT);
	prevButtons[2] = button_getStat(BUTTON_JOYSTICK);
}

void multiboard_data_updateInputs()
{
	multiboard_data_updateJoystickDirection();
	multiboard_data.joystickPositionX = joystick_getPos(POS_X);
	multiboard_data.joystickPositionY = joystick_getPos(POS_Y);
	multiboard_data_updateButtons();
	multiboard_data.sliderLeftPosition = slider_getPos(SLIDER_LEFT);
	multiboard_data.sliderRightPosition = slider_getPos(SLIDER_RIGHT);
}
