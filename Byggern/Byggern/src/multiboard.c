/*
 * multiboard.c
 *
 * Created: 11/17/2017 7:09:12 PM
 *  Author: dinos
 */ 

#include "multiboard/joystick.h"
#include "multiboard/slider.h"
#include "multiboard/button.h"
#include "multiboard.h"

void multiboard_init()
{
	joystick_calib();

	multiboardInputs.joystickDirection = JOY_NEUTRAL;
	multiboardInputs.joystickPositionX = 0;
	multiboardInputs.joystickPositionY = 0;
	multiboardInputs.joystickPressed = 0;
	multiboardInputs.sliderLeftPosition = 0;
	multiboardInputs.sliderRightPosition = 0;
	multiboardInputs.buttonLeftPressed = 0;
	multiboardInputs.buttonRightPressed = 0;
}

void multiboard_updateInputs()
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